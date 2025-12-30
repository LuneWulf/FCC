#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Headers/mainInclude.h"



int main(void) {

    clock_t start = clock();

    /* Fire distribution sheafs:
     *  0 Parallel          (Same deflection and quadrant)
     *  1 Converged         (Same aimpoint)
     *  2 Open              (Aimpoint seperated by 1 effective burst radius)
     *  - Special
     *     3 Linear         (Line between two grids or designated by length and attitude,
     *                       Aimpoints evenly distributed)
     * 
     *     4 Rectangular    (Rectangle with length, width and attitude,
     *                       Aimpoints are distributed evenly along the two lines parallel to the attiude)
     * 
     *     5 Circular       (Circle with center designated by grid and radius,
     *                       Aimpoints are distributed evenly along a concentric circle with half radius)
     * 
     *     6 Irregular      (Series of grids,
     *                       Aimpoints are distributed evenly along the lines connecting the grids)
     */

    struct Ammo *Charges = calloc(1, sizeof(struct Ammo));
    struct Guns *Gun = calloc(1, sizeof(struct Guns));
    struct BoundingGrids *Bounds = calloc(1, sizeof(struct BoundingGrids));
    struct Context *Atmosphere = calloc(1, sizeof(struct Context));
    struct Adjustments *Adjust = calloc(1, sizeof(struct Adjustments));
    struct Config *Cfg = calloc(1, sizeof(struct Config));


    // METEOROLOGICAL DATA

    Atmosphere->Temperature = 15;
    Atmosphere->Pressure = 1012.6;
    Atmosphere->Humidity = 0;

    const double WindSpeed = 0.6;
    double WindDir = 360;

        WindDir *= DEG_TO_RAD;

        Atmosphere->Wind.x = WindSpeed * sin(WindDir);
        Atmosphere->Wind.y = WindSpeed * cos(WindDir);


    // GUN DATA

    Gun->amount = 3;
    Gun->Gun[0].x = 3978;
    Gun->Gun[0].y = 4004;
    Gun->Gun[0].z = 5;
    Gun->Gun[1].x = 3996;
    Gun->Gun[1].y = 3994;
    Gun->Gun[1].z = 5;
    Gun->Gun[2].x = 4016;
    Gun->Gun[2].y = 4000;
    Gun->Gun[2].z = 5;


    // AMMUNITION DATA

    Charges->MuzzVel[0] = 153.9;
    Charges->MuzzVel[1] = 243;
    Charges->MuzzVel[2] = 388.8;
    Charges->MuzzVel[3] = 526.5;
    Charges->ChargeAmount = 4;
    int Charge = 0;
    Cfg->FindCharge = 1;
    Cfg->kFactor = 0.00006;


    // TARGET SHEAF DATA

    Bounds->SheafType = 2; // 0: Parallel, 1: Converged, 2: Open, 3: Linear, 4: Rectangular, 5: Circular, 6: Irregular
    Bounds->allowMultipleAimpoints = 0;

    Bounds->GridAmount = 1;
    Bounds->Grid[0].x = 3000;
    Bounds->Grid[0].y = 2000;
    Bounds->Grid[0].z = 5;
    Bounds->Grid[1].x = 25800;
    Bounds->Grid[1].y = 21475;
    Bounds->Grid[1].z = 21;

    Bounds->length = 100;
    Bounds->width = 30;
    Bounds->attitude = 92 * DEG_TO_RAD;

    Bounds->EBR = 25;

    Bounds->radius = 60;


    // ADJUSTMENTS

    Adjust->Range = 0; // Adjustment along target Deflection
    Adjust->Lat = 0; // Adjustment perpendicular to target Deflection

    Adjust->NS= 0; // North: positive, South: Negative
    Adjust->EW = 0; // East: positive, West: Negative


    // FIRE SOLUTION SETTINGS

    Cfg->FullInfo = 1;
    Cfg->dt = 0.001;


    // COMPUTATION

    if (!Cfg->FindCharge) {

        double tVel = sqrt( (double) 9.81 / Cfg->kFactor);

        Cfg->MaxError = Cfg->dt * fmax(Charges->MuzzVel[Charge], tVel);
    }

    for (int i = 0; i < Charges->ChargeAmount; i++) {
        const struct MR Test = MaxRange(Atmosphere, Charges->MuzzVel[i], Cfg);
        Charges->MaxRange[i] = Test.Range;
    }

    struct Aimpoints *Tgts = SheafSolver(Bounds, Gun);

    PrintAllSolutions(Atmosphere, Tgts, Gun, Charges, Charge, Cfg, Adjust);

    clock_t stop = clock();

    double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("Time elapsed: %.3f s\n", elapsed);

    free(Charges);
    Charges = NULL;
    free(Gun);
    Gun = NULL;
    free(Bounds);
    Bounds = NULL;
    free(Atmosphere);
    Atmosphere = NULL;
    free(Adjust);
    Adjust = NULL;
    free(Cfg);
    Cfg = NULL;
    free(Tgts);
    Tgts = NULL;

    return 0;
}
