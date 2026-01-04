/*
 *  Created By Simon Bergmann
 *
 *  Last Edit: 28/12-2025
 *
 *  Arguments:
 *      i - (High or low angle, 1/0, <unitless>)
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
 *          .amount - (Amount of Guns, <unitless>)
 *      *Aimpoint
 *          .Aimpoint[30] - (3D Vectors, components in <m>)
 *          .SheafType - (Sheaf type, 0-6, <unitless>)
 *          .amount - (Amount of Aimpoints, <unitless>)
 *      *Charges:
 *          .MuzzVel[20] - (Charge muzzle velocity, <m/s>)
 *          .MaxRange[20] - (Charge max range, <m>)
 *          .ChargeAmount - (Amount of charges, <unitless>)
 *      *Cfg:
 *          .MaxError - (Maximum distance error between Tgt and Hit, <m>)
 *          .FullInfo - (1/0, print minimal or maximal info, <unitless>)
 *
 *  Returns:
 *      void
 *
 */

#include "../Headers/Conversions.h"
#include "../Headers/PrintSolutions.h"
#include "../Headers/VectorDir.h"
#include "structs.h"
#include <stdio.h>
#include <math.h>

#include "IntegrationLoop.h"

void PrintSolutions(int i, struct Guns *Gun, struct Aimpoints *Aimpoint, struct Ammo *Charges, struct Config *Cfg) {

    int Invalid = 0;

    const int Charge = Gun->Data[i].Charge;

    if (Gun->Data[i].DisErHigh > Gun->Data[i].MaxErrorHigh || Gun->Data[i].DisErLow > Gun->Data[i].MaxErrorLow || Gun->Data[i].Charge == -1) {
        Invalid = 1;
    }

    double Dir, dX, dY;

    switch (Aimpoint->SheafType) {
        case 0:

            Dir = VectorDir(Gun->Gun[0], Aimpoint->Aimpoint[0]);

            dX = Gun->Gun[0].x - Aimpoint->Aimpoint[0].x;
            dY = Gun->Gun[0].y - Aimpoint->Aimpoint[0].y;

            break;

        case 1:

            Dir = VectorDir(Gun->Gun[i], Aimpoint->Aimpoint[0]);

            dX = Gun->Gun[i].x - Aimpoint->Aimpoint[0].x;
            dY = Gun->Gun[i].y - Aimpoint->Aimpoint[0].y;

            break;

        default:

            Dir = VectorDir(Gun->Gun[i], Aimpoint->Aimpoint[i]);

            dX = Gun->Gun[i].x - Aimpoint->Aimpoint[i].x;
            dY = Gun->Gun[i].y - Aimpoint->Aimpoint[i].y;

            break;
    }

    const double Range = sqrt( dX*dX + dY*dY);

    printf("----------- Gun #%d Fire Solutions -----------\n\n", i + 1);

    if (Invalid == 1) {

        printf("Charge: Not Found!\n");
        printf("Target Range: %.f m\n\n", Range);

        printf("        !!! GUN #%d SOLUTION INVALID !!!\n", i + 1);
        printf("         ATTEMPT WITH DIFFERENT CHARGE,\n");
        printf("          ELSE TARGET IS OUT OF RANGE\n\n");

    } else {

        printf("Charge: %d\n", Charge);
        printf("Target Range: %.f m\n", Range);
        printf("Charge Max Range: %.f m\n\n", Charges->MaxRange[Charge]);

        if ((Charges->MaxRange[Charge] - Gun->Data[i].DistanceTravelled) < 500) {
            printf("WARNING: TARGET IS WITHIN 500 METERS OF MAX RANGE!\n\n");
        }

        if (Cfg->FullInfo == 1) {

            const double HighDefDiff = Gun->Data[i].DeflectionHigh - Dir;
            const double LowDefDiff = Gun->Data[i].DeflectionLow - Dir;

            printf("High Angle:\n");
            printf("|    Deflection:  %.2f deg  /  %.1f mills,\n", Gun->Data[i].DeflectionHigh * RAD_TO_DEG, Gun->Data[i].DeflectionHigh * RAD_TO_MILLS);
            printf("|   dDeflection:  %.2f deg  /  %.1f mills,\n", HighDefDiff * RAD_TO_DEG, HighDefDiff * RAD_TO_MILLS);
            printf("|      Quadrant:  %.2f deg  /  %.1f mills,\n", Gun->Data[i].QuadrantHigh * RAD_TO_DEG, Gun->Data[i].QuadrantHigh * RAD_TO_MILLS);
            printf("|           ToF:  %.2f s,\n", Gun->Data[i].ToFHigh);
            printf("|           AOI:  %.2f deg,\n", Gun->Data[i].AOIHigh * RAD_TO_DEG);
            printf("|        Summit:  %.f m,\n", Gun->Data[i].SummitHigh);
            printf("|  Summit Range:  %.f m,\n", Gun->Data[i].SummitDisHigh);
            printf("|     Hit Error:  %.2f m +/- %.2f m/mill,\n", Gun->Data[i].DisErHigh, Gun->Data[i].ErrorHigh);
            printf("|     Max Error:  %.2f m\n\n", Gun->Data[i].MaxErrorHigh);

            printf("Low Angle:\n");
            printf("|    Deflection:  %.2f deg  /  %.1f mills,\n", Gun->Data[i].DeflectionLow * RAD_TO_DEG, Gun->Data[i].DeflectionLow * RAD_TO_MILLS);
            printf("|   dDeflection:  %.2f deg  /  %.1f mills,\n", LowDefDiff * RAD_TO_DEG, LowDefDiff * RAD_TO_MILLS);
            printf("|      Quadrant:  %.2f deg  /  %.1f mills,\n", Gun->Data[i].QuadrantLow * RAD_TO_DEG, Gun->Data[i].QuadrantLow * RAD_TO_MILLS);
            printf("|           ToF:  %.2f s,\n", Gun->Data[i].ToFLow);
            printf("|           AOI:  %.2f deg,\n", Gun->Data[i].AOILow * RAD_TO_DEG);
            printf("|        Summit:  %.f m,\n", Gun->Data[i].SummitLow);
            printf("|  Summit Range:  %.f m,\n", Gun->Data[i].SummitDisLow);
            printf("|     Hit Error:  %.2f m +/- %.2f m/mill,\n", Gun->Data[i].DisErLow, Gun->Data[i].ErrorLow);
            printf("|     Max Error:  %.2f m\n\n", Gun->Data[i].MaxErrorLow);

        } else {

            printf("High Angle:\n");
            printf("|    Deflection:  %.2f deg  / %.1f mills,\n", Gun->Data[i].DeflectionHigh * RAD_TO_DEG, Gun->Data[i].DeflectionHigh * RAD_TO_MILLS);
            printf("|      Quadrant:  %.2f deg  /  %.1f mills,\n", Gun->Data[i].QuadrantHigh * RAD_TO_DEG, Gun->Data[i].QuadrantHigh * RAD_TO_MILLS);
            printf("|           ToF:  %.2f s\n\n", Gun->Data[i].ToFHigh);

            printf("Low Angle:\n");
            printf("|    Deflection:  %.2f deg  / %.1f mills,\n", Gun->Data[i].DeflectionLow * RAD_TO_DEG, Gun->Data[i].DeflectionLow * RAD_TO_MILLS);
            printf("|      Quadrant:  %.2f deg  /  %.1f mills,\n", Gun->Data[i].QuadrantLow * RAD_TO_DEG, Gun->Data[i].QuadrantLow * RAD_TO_MILLS);
            printf("|           ToF:  %.2f s\n\n", Gun->Data[i].ToFLow);
        }
    }
}

