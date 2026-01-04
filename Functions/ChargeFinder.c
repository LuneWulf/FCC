/*
 *  Created By Simon Bergmann
 *
 *  Last Edit: 28/12-2025
 *
 *  Arguments:
 *      Tgt - (3D Vector, components in <m>)
 *      Gun - (3D Vector, components in <m>)
 *      *Charges:
 *          .MuzzVel[20] - (Charge muzzle velocity, <m/s>)
 *          .MaxRange[20] - (Charge max range, <m>)
 *          .ChargeAmount - (Amount of charges, <unitless>)
 *      *Cfg
 *          .dt - (Simulation time step, <s>)
 *          .kFactor - (Drag factor, <m>)
 *          .MaxError - (Maximum distance error between Tgt and Gun in one dt, <m>)
 *          .FullInfo - (1/0, print minimal or maximal info, <unitless>)
 *      *Adjust
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
 *          .QuadrantLow - (Quadrant angle for high angle fire, <radians>)
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

#include "../Headers/ChargeFinder.h"
#include "../Headers/VectorDistance.h"
#include "../Headers/SolutionSolver.h"
#include "structs.h"

FireData ChargeFinder(Vector3D Tgt, Vector3D Gun, Ammo *Charges, struct Config *Cfg, struct Adjustments *Adjust, struct Context *Atmosphere) {

    FireData Charge;

    Charge.Charge = -1;

    const double Distance = VectorDistance(Gun, Tgt);

    for (int i = 0; i < Charges->ChargeAmount; i++) {

        if (Distance < Charges->MaxRange[i]) {

            Charge = SolutionSolver(Tgt, Gun, i, Charges, Cfg, Adjust, Atmosphere);

            if (Charge.DisErHigh <= Cfg->MaxError && Charge.DisErLow <= Cfg->MaxError) {

                Charge.Charge = i;

                if (i == Charges->ChargeAmount - 1 || Charges->MaxRange[i] - Charge.DistanceTravelled > 500) {
                    break;
                }
            }
        }
    }

    return Charge;
}

