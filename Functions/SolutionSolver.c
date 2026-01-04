/*
 *  Created By Simon Bergmann
 *
 *  Last Edit: 28/12-2025
 *
 *  Arguments:
 *      Tgt - (3D Vector, components in <m>)
 *      Gun - (3D Vector, components in <m>)
 *      Charge - (Charge, starts at 0, <unitless>)
 *      *Charges:
 *          .MuzzVel[20] (Charge muzzle velocity, <m/s>)
 *      *Cfg:
 *          .dt - (Simulation time step, <s>)
 *          .kFactor - (Drag factor, <m>)
 *          .MaxError - (Maximum distance error between Tgt and Gun in one dt, <m>)
 *      *Adjust:
 *          .Range - (Adjustment along deflection, <m>)
 *          .Lat - (Adjustment perpendicular to deflection, <m>)
 *          .NS - (Adjustment North/South, positive/negative, <m>)
 *          .EW - (Adjustment East/West, positive/negative, <m>)
 *      *Atmosphere:
 *          .Temperature - (<Degrees C>)
 *          .Pressure - (<hPa>)
 *          .Humidity - (Relative Humidity <%>)
 *          .Wind - (2D Vector, components in <m/s>)
 *
 *  Returns:
 *      FireData:
 *          .Charge - (Charge, starts at 0, <unitless>)
 *          .DeflectionHigh - (Compass angle for high angle fire, <radians>)
 *          .DeflectionLow - (Compass angle for low angle fire, <radians>)
 *          .QuadrantHigh - (Quadrant angle for high angle fire, <radians>)
 *          .QuadrantLow - (Quadrant angle for low angle fire, <radians>)
 *          .ToFHigh - (High angle time of flight, <s>)
 *          .ToFLow - (Low angle time of flight, <s>)
 *          .AOIHigh - (High angle angle of impact, <radians>)
 *          .AOILow - (Low angle angle of impact, <radians>)
 *          .SummitHigh - (High angle summit, <m>)
 *          .SummitLow - (Low angle summit, <m>)
 *          .SummitDisHigh - (High angle summit distance, <m>)
 *          .SummitDisLow - (Low angle summit distance, <m>)
 *          .DisErHigh - (High angle difference between Tgt and Hit, <m>)
 *          .DisErLow - (Low angle difference between Tgt and Hit, <m>)
 *          .DistanceTravelled (Distance from Gun to Hit, <m>)
 *
 */

#include "../Headers/Conversions.h"
#include "../Headers/SolutionSolver.h"
#include "../Headers/QuadrantUpdate.h"
#include "../Headers/DeflectionUpdate.h"
#include "../Headers/VectorDir.h"
#include "../Headers/AdjustTgt.h"
#include "../Headers/airDensity.h"
#include "../Headers/IntegrationLoop.h"
#include <stdio.h>
#include "structs.h"
#include <math.h>

#include "CusaTan.h"

FireData SolutionSolver(Vector3D Tgt, Vector3D Gun, int Charge, Ammo *Charges, struct Config *Cfg, struct Adjustments *Adjust, struct Context *Atmosphere) {

    FireData ProjectileData;
    Missile Projectile;

    Tgt = AdjustTgt(Tgt, Gun, Adjust);

    double dX = Tgt.x - Gun.x;
    double dY = Tgt.y - Gun.y;

    double MuzzVel = Charges->MuzzVel[Charge];
    double NewMuzzVelCoef = ((Atmosphere->Temperature + 273.15) / 288.15 - 1) / 40 + 1;
    MuzzVel *= NewMuzzVelCoef;

    double RD = airDensity(Atmosphere)/1.225;
    double CD = Cfg->kFactor*RD;

    double Range = sqrt( dY*dY + dX*dX);
    double Quadrant = 90 * DEG_TO_RAD;
    double Deflection = VectorDir(Gun, Tgt);

    //printf("Deflection: %f\n\n", Deflection * RAD_TO_DEG);
    //printf("dX: %f,   dY: %f\n\n", dX, dY);

    double _1Angle = Quadrant, _2Angle;
    double TempDeflection = Deflection;

    struct QuadrantUpdate qu = {Range,CD,MuzzVel,Tgt,Gun,Atmosphere,Cfg};

    ProjectileData.MaxErrorHigh = Cfg->MaxError;
    ProjectileData.MaxErrorLow = Cfg->MaxError;

    for (int i = 0; i <= 1; i++){
        if (i == 1) {
            Quadrant = 0;
            _1Angle = Quadrant;
        }

        int MaxErrorChange = 0;

        Deflection = TempDeflection;
        int count = 0;
        int InitialSweep = 1;

        do {
            Projectile = IntegrationLoop(Cfg->dt, CD, MuzzVel, Quadrant, Deflection, Gun, Tgt, Atmosphere);

            count++;

            ProjectileData.DistanceTravelled = sqrt( (Projectile.y - Gun.y)*(Projectile.y - Gun.y) + (Projectile.x - Gun.x)*(Projectile.x - Gun.x));

            double RangeError = Range - ProjectileData.DistanceTravelled;

            if (RangeError >= (i == 0 ? ProjectileData.MaxErrorHigh : ProjectileData.MaxErrorLow) || RangeError <= -(i == 0 ? ProjectileData.MaxErrorHigh : ProjectileData.MaxErrorLow)) {

                QuadrantUpdate(i, &InitialSweep, &_1Angle, &_2Angle, &Quadrant, Deflection,&RangeError, &Projectile, &ProjectileData, qu);

            } else if (Projectile.DisEr > (i == 0 ? ProjectileData.MaxErrorHigh : ProjectileData.MaxErrorLow)) {

                DeflectionUpdate(i, &InitialSweep, Projectile, Gun, &TempDeflection, &Deflection, &Quadrant);

            }
            if (count >= 100 && MaxErrorChange < 10) {

                count = 0;
                MaxErrorChange++;

                switch (i) {
                    case 0: ProjectileData.MaxErrorHigh *= sqrt(10);
                        break;
                    case 1: ProjectileData.MaxErrorLow *= sqrt(10);
                        break;
                    default:
                        break;
                }
            }

        } while (Projectile.DisEr > (i == 0 ? ProjectileData.MaxErrorHigh : ProjectileData.MaxErrorLow) && count < 100);

        switch (i) {
            case 0:
                ProjectileData.DeflectionHigh = Deflection;
                ProjectileData.QuadrantHigh = Quadrant;
                ProjectileData.SummitHigh = Projectile.Summit;
                ProjectileData.ToFHigh = Projectile.t;
                ProjectileData.DisErHigh = Projectile.DisEr;
                ProjectileData.SummitDisHigh = Projectile.SummitDis;
                ProjectileData.AOIHigh = Projectile.AOI;
                ProjectileData.ErrorHigh = IntegrationLoop(Cfg->dt, CD, MuzzVel, Quadrant + 0.5 * MILLS_TO_RAD, Deflection + 0.5 * MILLS_TO_RAD, Gun, Tgt, Atmosphere).DisEr;
                break;
            case 1:
                ProjectileData.DeflectionLow = Deflection;
                ProjectileData.QuadrantLow = Quadrant;
                ProjectileData.SummitLow = Projectile.Summit;
                ProjectileData.ToFLow = Projectile.t;
                ProjectileData.DisErLow = Projectile.DisEr;
                ProjectileData.SummitDisLow = Projectile.SummitDis;
                ProjectileData.AOILow = Projectile.AOI;
                ProjectileData.ErrorLow = IntegrationLoop(Cfg->dt, CD, MuzzVel, Quadrant + 0.5 * MILLS_TO_RAD, Deflection + 0.5 * MILLS_TO_RAD, Gun, Tgt, Atmosphere).DisEr;
                break;
            default:
                break;
        }
    }

    ProjectileData.Charge = Charge;

    return ProjectileData;
}
