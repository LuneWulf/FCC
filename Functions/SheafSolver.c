/*
 *  Created By Simon Bergmann
 *
 *  Last Edit: 28/12-2025
 *
 *  Arguments:
 *      *Bounds:
 *          Grid[10] - (Sheaf bounding grids, 3D Vectors, Components in <m>)
 *          GridAmount - (Amount of grids, <unitless>)
 *          length - (Sheaf length, applies to linear and rectangular, <m>)
 *          width - (Sheaf width, applies to linear and rectangular, <m>)
 *          attitude - (Sheaf compass direction, applies to linear and rectangular, <m>)
 *          radius - (Sheaf radius, applies to circular, <m>)
 *          SheafType (Type of sheaf, 0-6, <unitless>)
 *      *Gun:
 *          Gun[30] - (3D Vector collection of stored guns, components in <m>)
 *          amount - (Amount of guns, <unitless>)
 *
 *  Returns:
 *      Aimpoints - (3D Vectors of aimpoints matching sheaf type, components in <m>)
 *
 */

#include "../Headers/SheafSolver.h"
#include "../Headers/VectorDir.h"
#include "../Headers/VectorDistance.h"
#include <stdlib.h>
#include <math.h>

struct Aimpoints *SheafSolver(struct BoundingGrids *Bounds, struct Guns *Gun) {

    struct Aimpoints *Aimpoint = calloc(1, sizeof(struct Aimpoints));

    Aimpoint->SheafType = Bounds->SheafType;
    const int middle = Gun->amount / 2 + 1;

    double dX, dY, distance;

    switch (Bounds->SheafType) {
        case 0: /* Parallel */
        case 1: /* Converged */ {

            Aimpoint->Aimpoint[0] = Bounds->Grid[0];
            Aimpoint->amount = 1;

            break;
        }

        case 2: /* Open */ {

            Aimpoint->amount = Gun->amount;

            Aimpoint->Aimpoint[middle - 1] = Bounds->Grid[0];


            const double Dir = VectorDir(Gun->Gun[middle - 1], Aimpoint->Aimpoint[middle - 1]);

            const double LatXAdj = cos(Dir) * Bounds->EBR * 2;
            const double LatYAdj = sin(Dir) * Bounds->EBR * 2;

            // Left side aimpoints
            for (int i = 0; i <= middle - 2; i++) {
                const int k = (middle - 1 - i);
                Aimpoint->Aimpoint[i].x = Aimpoint->Aimpoint[middle - 1].x - k * LatXAdj;
                Aimpoint->Aimpoint[i].y = Aimpoint->Aimpoint[middle - 1].y + k * LatYAdj;
                Aimpoint->Aimpoint[i].z = Aimpoint->Aimpoint[middle - 1].z;
            }

            // Right side aimpoints
            for (int i = middle; i < Gun->amount; i++) {
                const int k = (i - middle + 1);
                Aimpoint->Aimpoint[i].x = Aimpoint->Aimpoint[middle - 1].x + k * LatXAdj;
                Aimpoint->Aimpoint[i].y = Aimpoint->Aimpoint[middle - 1].y - k * LatYAdj;
                Aimpoint->Aimpoint[i].z = Aimpoint->Aimpoint[middle - 1].z;
            }

            break;

        }



        case 3: /* Linear */ {

            Aimpoint->amount = Gun->amount;

            if (Bounds->length != 0) {

                dX = sin(Bounds->attitude) * Bounds->length / (Gun->amount - 1);
                dY = cos(Bounds->attitude) * Bounds->length / (Gun->amount - 1);

            } else {

                const double length = VectorDistance(Bounds->Grid[0], Bounds->Grid[1]);
                const double attitude = VectorDir(Bounds->Grid[0], Bounds->Grid[1]);

                dX = sin(attitude) * length / (Gun->amount - 1);
                dY = cos(attitude) * length / (Gun->amount - 1);

            }

            Aimpoint->Aimpoint[0] = Bounds->Grid[0];

            for (int i = 1; i < Gun->amount; i++) {
                Aimpoint->Aimpoint[i].x = Bounds->Grid[0].x + i * dX;
                Aimpoint->Aimpoint[i].y = Bounds->Grid[0].y + i * dY;
                Aimpoint->Aimpoint[i].z = Bounds->Grid[0].z;
            }

            break;

        }

        case 4: /* Rectangular */ {

            Aimpoint->amount = Gun->amount;

            const int nTop = middle;
            const int nBot = Gun->amount - middle;

            const double PerpdX = cos(Bounds->attitude - M_PI/2) * Bounds->width / 2;
            const double PerpdY = sin(Bounds->attitude - M_PI/2) * Bounds->width / 2;

            double TdY, TdX;

            if (Gun->amount == 2) {

                TdY = cos(M_PI/2 - Bounds->attitude) * Bounds->length / 2;
                TdX = sin(M_PI/2 - Bounds->attitude) * Bounds->length / 2;

                Aimpoint->Aimpoint[0].x = Bounds->Grid[0].x + PerpdX + TdX;
                Aimpoint->Aimpoint[0].y = Bounds->Grid[0].y + PerpdY + TdY;
                Aimpoint->Aimpoint[0].z = Bounds->Grid[0].z;

                Aimpoint->Aimpoint[1].x = Bounds->Grid[0].x - PerpdX + TdX;
                Aimpoint->Aimpoint[1].y = Bounds->Grid[0].y - PerpdY + TdY;
                Aimpoint->Aimpoint[1].z = Bounds->Grid[0].z;

            } else if (Gun->amount % 2 == 0) {

                const double Ke = Bounds->length / (nTop - 1);

                TdY = cos(M_PI/2 - Bounds->attitude) * Ke;
                TdX = sin(M_PI/2 - Bounds->attitude) * Ke;

                for (int i = middle; i < Gun->amount; i++) {

                    Aimpoint->Aimpoint[i].x = Bounds->Grid[0].x - PerpdX + TdX * (i - middle);
                    Aimpoint->Aimpoint[i].y = Bounds->Grid[0].y - PerpdY + TdY * (i - middle);
                    Aimpoint->Aimpoint[i].z = Bounds->Grid[0].z;

                }

            } else {

                const double Kt = Bounds->length / (nTop - 1);
                const double Kb = Bounds->length / (nBot + 1); // could be rewritten using (nTop) instead of (nBot + 1);

                TdY = cos(M_PI/2 - Bounds->attitude) * Kt;
                TdX = sin(M_PI/2 - Bounds->attitude) * Kt;
                const double BdY = cos(M_PI/2 - Bounds->attitude) * Kb;
                const double BdX = sin(M_PI/2 - Bounds->attitude) * Kb;

                for (int i = middle; i < Gun->amount; i++) {

                    Aimpoint->Aimpoint[i].x = Bounds->Grid[0].x - PerpdX + BdX * (i - middle + 1);
                    Aimpoint->Aimpoint[i].y = Bounds->Grid[0].y - PerpdY + BdY * (i - middle + 1);
                    Aimpoint->Aimpoint[i].z = Bounds->Grid[0].z;

                }

            }

            if (Gun->amount > 2) {
                for (int i = 0; i < middle; i++) {

                    Aimpoint->Aimpoint[i].x = Bounds->Grid[0].x + PerpdX + TdX * i;
                    Aimpoint->Aimpoint[i].y = Bounds->Grid[0].y + PerpdY + TdY * i;
                    Aimpoint->Aimpoint[i].z = Bounds->Grid[0].z;

                }
            }

            break;

        }



        case 5: /* Circular */ {

            Aimpoint->amount = Gun->amount;

            const double radius = Bounds->radius / 2;
            const double dTheta = 2 * M_PI / (double) Gun->amount;

            for (int i = 0; i < Gun->amount; i++) {
                Aimpoint->Aimpoint[i].x = Bounds->Grid[0].x + sin(dTheta * i) * radius;
                Aimpoint->Aimpoint[i].y = Bounds->Grid[0].y + cos(dTheta * i) * radius;
                Aimpoint->Aimpoint[i].z = Bounds->Grid[0].z;
            }

            break;

        }



        case 6: /* Irregular */ {

            distance = 0;

            double *Length = calloc(Bounds->GridAmount - 1, sizeof(double));
            double *Direction = calloc(Bounds->GridAmount - 1, sizeof(double));

            for (int i = 0; i < Bounds->GridAmount - 1; i++) {

                Direction[i] = VectorDir(Bounds->Grid[i], Bounds->Grid[i + 1]);

                double tempDistance = VectorDistance(Bounds->Grid[i], Bounds->Grid[i + 1]);

                Length[i] = tempDistance;
                distance += tempDistance;

            }

            double DistanceInterval = distance / (Gun->amount - 1);

            int interval = 0;

            Aimpoint->Aimpoint[0].x = Bounds->Grid[0].x;
            Aimpoint->Aimpoint[0].y = Bounds->Grid[0].y;
            Aimpoint->Aimpoint[0].z = Bounds->Grid[0].z;

            for (int i = 1; i < Gun->amount; i++) {

                double adjustXY = DistanceInterval;

                Length[interval] -= DistanceInterval;

                while (Length[interval] < 0) {
                    interval++;
                    Length[interval] += Length[interval - 1];
                    adjustXY = -Length[interval - 1];
                }

                double dz = Bounds->Grid[interval].z - Bounds->Grid[interval + 1].x;
                double theta = dz / Length[interval];
                double adjustZ = adjustXY * theta;

                Aimpoint->Aimpoint[i].x = Aimpoint->Aimpoint[i - 1].x + sin(Direction[interval]) * adjustXY;
                Aimpoint->Aimpoint[i].y = Aimpoint->Aimpoint[i - 1].y + cos(Direction[interval]) * adjustXY;
                Aimpoint->Aimpoint[i].z = Aimpoint->Aimpoint[i - 1].z + adjustZ;
            }

            free(Length);
            Length = NULL;
            free(Direction);
            Direction = NULL;

            break;

        }

        default:
            break;
    }

    return Aimpoint;

}
