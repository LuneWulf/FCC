/*
 *  Created By Simon Bergmann
 *
 *  Last Edit: 28/12-2025
 *
 *  Arguments:
 *      *Atmosphere:
 *          .
 *      MuzzVel - (Muzzle velocity, <m/s>)
 *      *Cfg:
 *          .dt - (Simulation time step, <s>)
 *          .kFactor - (Drag factor, <m>)
 *          .MaxError - (Maximum distance error between Tgt and Gun in one dt, <m>)
 *
 *  Returns:
 *      MR:
 *          .Quadrant - (Quadrant to achieve maximum range, <radians>)
 *          .Range - (Maximum Range, <m>)
 *
 */

#include "../Headers/MaxRange.h"
#include "../Headers/airDensity.h"
#include "../Headers/CusaTan.h"
#include "../Headers/IntegrationLoop.h"
#include "../Headers/Conversions.h"
#include <math.h>
#include "structs.h"

struct MR MaxRange(struct Context *Atmosphere, double MuzzVel, struct Config *Cfg) {

    // Find max range

    double Quadrant = 1 * DEG_TO_RAD;
    double InitMRQ;
    double Angle1, Angle2;

    double MaxRange = 0;
    double Range = 0;
    double PrevRange;

    struct Vector3D Gun = {0,0,0};
    struct Vector3D Tgt = {0,0,0};

    struct Missile Projectile;

    double RD = airDensity(Atmosphere)/1.225;
    double CD = Cfg->kFactor*RD;

    double RevWindDir = CusaTan(-Atmosphere->Wind.y, -Atmosphere->Wind.x);

    do {

        PrevRange = Range;

        Projectile = IntegrationLoop(Cfg->dt, CD, MuzzVel, Quadrant, RevWindDir, Gun, Tgt, Atmosphere);

        Range = sqrt( Projectile.x*Projectile.x + Projectile.y*Projectile.y);

        if (Range > MaxRange) {

            MaxRange = Range;

            InitMRQ = Quadrant;

            Quadrant += 1 * DEG_TO_RAD;

        }

    } while (Range > PrevRange);

    Angle1 = InitMRQ - 1 * DEG_TO_RAD;
    Angle2 = InitMRQ + 1 * DEG_TO_RAD;

    double Quadrant1 = InitMRQ - 0.5 * DEG_TO_RAD;
    double Quadrant2 = InitMRQ + 0.5 * DEG_TO_RAD;
    double Range1, Range2;

    do {

        Projectile = IntegrationLoop(Cfg->dt, CD, MuzzVel, Quadrant1, RevWindDir, Gun, Tgt, Atmosphere);

        Range1 = sqrt( Projectile.x*Projectile.x + Projectile.y*Projectile.y);

        Projectile = IntegrationLoop(Cfg->dt, CD, MuzzVel, Quadrant2, RevWindDir, Gun, Tgt, Atmosphere);

        Range2 = sqrt( Projectile.x*Projectile.x + Projectile.y*Projectile.y);

        if (Range1 > Range2) {

            Angle2 = Quadrant2;

            double middle = (Angle1 + Angle2) / 2;

            Quadrant1 = (Angle1 + middle) / 2;
            Quadrant2 = (Angle2 + middle) / 2;

        } else {

            Angle1 = Quadrant1;

            double middle = (Angle1 + Angle2) / 2;

            Quadrant1 = (Angle1 + middle) / 2;
            Quadrant2 = (Angle2 + middle) / 2;

        }

    } while ((Angle1 - Angle2) > 0.0001 * DEG_TO_RAD || (Angle1 - Angle2) < -0.0001 * DEG_TO_RAD);

    Quadrant = (Angle1 + Angle2) / 2;
    MaxRange = (Range1 + Range2) / 2;


    struct MR Result;
    Result.Quadrant = Quadrant;
    Result.Range = MaxRange;

    return Result;
}
