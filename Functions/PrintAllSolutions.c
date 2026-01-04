/*
 *  Created By Simon Bergmann
 *
 *  Last Edit: 28/12-2025
 *
 *  Arguments:
 *      *Atmosphere:
 *          .Temperature - (<Degrees C>)
 *          .Pressure - (<hPa>)
 *          .Humidity - (Relative Humidity, <%>)
 *          .Wind - (2D Vector, components in <m/s>)
 *      *Tgts:
 *          .Aimpoint[30] - (3D Vector, components in <m>)
 *          .SheafType - (Sheaf type, 0-6, <unitless>)
 *          .amount - (Amount of Tgts, <unitless>)
 *      *Gun:
 *          .Gun[30] - (3D Vector, components in <m>)
 *          .Data[30]:
 *              Charge - (Charge, starts at 0, <unitless>)
 *              DeflectionHigh - (Compass angle for high angle fire, <radians>)
 *              DeflectionLow - (Compass angle for low angle fire, <radians>)
 *              QuadrantHigh - (Quadrant angle for high angle fire, <radians>)
 *              QuadrantLow - (Quadrant angle for high angle fire, <radians>)
 *              ToFHigh - (High angle time of flight, <s>)
 *              ToFLow - (Low angle time of flight, <s>)
 *              AOIHigh - (High angle angle of impact, <radians>)
 *              AOILow - (Low angle angle of impact, <radians>)
 *              SummitHigh - (High angle summit, <m>)
 *              SummitLow - (Low angle summit, <m>)
 *              SummitDisHigh - (High angle summit distance, <m>)
 *              SummitDisLow - (Low angle summit distance, <m>)
 *              DisErHigh - (High angle difference between Tgt and Hit, <m>)
 *              DisErLow - (Low angle difference between Tgt and Hit, <m>)
 *              DistanceTravelled (Distance from Gun to Hit, <m>)
 *      *Charges:
 *          .MuzzVel[20] - (Charge muzzle velocity, <m/s>)
 *          .MaxRange[20] - (Charge max range, <m>)
 *          .ChargeAmount - (Amount of charges, <unitless>)
 *      Charge - (Charge, from 0, <unitless>)
 *      *Cfg
 *          .dt - (Simulation time step, <s>)
 *          .kFactor - (Drag factor, <m>)
 *          .MaxError - (Maximum distance error between Tgt and Gun in one dt, <m>)
 *          .FullInfo - (1/0, print minimal or maximal info, <unitless>)
 *          .FindCharge - (1/0, automatic/manual charge selection, <unitless>)
 *      *Adjust
 *          .Range - (Adjustment along deflection, <m>)
 *          .Lat - (Adjustment perpendicular to deflection, <m>)
 *          .NS - (Adjustment North/South, positive/negative, <m>)
 *          .EW - (Adjustment East/West, positive/negative, <m>)
 *
 *  Returns:
 *      void
 *
 */

#include "../Headers/PrintAllSolutions.h"
#include "../Headers/SolutionSolver.h"
#include "../Headers/PrintSolutions.h"
#include "../Headers/ChargeFinder.h"
#include <stdio.h>

void PrintAllSolutions(struct Context *Atmosphere, struct Aimpoints *Tgts, struct Guns *Gun, struct Ammo *Charges, int Charge, struct Config *Cfg, struct Adjustments *Adjust) {

    const int middle = Gun->amount / 2 + 1;

    char *SheafType;

    switch (Tgts->SheafType) {
        case 0:
            SheafType = "Parallel";
            break;
        case 1:
            SheafType = "Converged";
            break;
        case 2:
            SheafType = "Open";
            break;
        case 3:
            SheafType = "Linear";
            break;
        case 4:
            SheafType = "Rectangular";
            break;
        case 5:
            SheafType = "Circular";
            break;
        case 6:
            SheafType = "Irregular";
            break;
        default:
            SheafType = "Invalid";
            break;
    }

    printf("\n-|-|-|-|-|-|-|- FIRE SOLUTIONS -|-|-|-|-|-|-|-\n");
    printf("Sheaf type: %s\n\n", SheafType);

    switch (Tgts->SheafType) {
        case 0:

            if (Cfg->FindCharge == 1) {
                Gun->Data[middle - 1] = ChargeFinder(Tgts->Aimpoint[0], Gun->Gun[middle - 1], Charges, Cfg, Adjust, Atmosphere);
            } else {
                Gun->Data[middle - 1] = SolutionSolver(Tgts->Aimpoint[0], Gun->Gun[middle - 1], Charge, Charges, Cfg, Adjust, Atmosphere);
            }

            for (int i = 0; i < Gun->amount; i++) {
                Gun->Data[i] = Gun->Data[middle - 1];
            }

            PrintSolutions(0, Gun, Tgts, Charges, Cfg);

            break;

        case 1:
            for (int i = 0; i < Gun->amount; i++) {

                if (Cfg->FindCharge == 1) {
                    Gun->Data[i] = ChargeFinder(Tgts->Aimpoint[0], Gun->Gun[i], Charges, Cfg, Adjust, Atmosphere);
                } else {
                    Gun->Data[i] = SolutionSolver(Tgts->Aimpoint[0], Gun->Gun[i], Charge, Charges, Cfg, Adjust, Atmosphere);
                }

                PrintSolutions(i, Gun, Tgts, Charges, Cfg);
            }

            break;

        case 2:
        case 3:
        case 4:
        case 5:
        case 6:

            for (int i = 0; i < Gun->amount; i++) {

                if (Cfg->FindCharge == 1) {
                    Gun->Data[i] = ChargeFinder(Tgts->Aimpoint[i], Gun->Gun[i], Charges, Cfg, Adjust, Atmosphere);
                } else {
                    Gun->Data[i] = SolutionSolver(Tgts->Aimpoint[i], Gun->Gun[i], Charge, Charges, Cfg, Adjust, Atmosphere);
                }

                PrintSolutions(i, Gun, Tgts, Charges, Cfg);
            }

            break;

        default:
            break;
    }
}
