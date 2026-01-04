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

#include "SheafSolver.h"
#include "SheafSolve_Open.h"
#include "SheafSolve_Linear.h"
#include "SheafSolve_Rectangular.h"
#include "SheafSolve_Irregular.h"
#include <stdlib.h>
#include <math.h>
#include "structs.h"

Aimpoints *SheafSolver(Bounds *bounds, struct GunStore *Gun) {

    Aimpoints *Aimpoint = calloc(1, sizeof(Aimpoints));

    Aimpoint->SheafType = bounds->SheafType;
    const int middle = Gun->amount / 2 + 1;

    switch (bounds->SheafType) {
        case 0: /* Parallel */
        case 1: /* Converged */ {

            Aimpoint->Aimpoint[0] = bounds->Grid[0];
            Aimpoint->amount = 1;

            break;
        }

        case 2: /* Open */ {

            SheafSolve_Open(Gun, Aimpoint, bounds, middle);
            break;
        }

        case 3: /* Linear */ {

            SheafSolve_Linear(Gun, Aimpoint, bounds);
            break;
        }

        case 4: /* Rectangular */ {

            SheafSolve_Rectangular(Gun, Aimpoint, bounds, middle);
            break;
        }

        case 5: /* Circular */ {

            Aimpoint->amount = Gun->amount;

            const double radius = bounds->radius / 2;
            const double dTheta = 2 * M_PI / (double) Gun->amount;

            for (int i = 0; i < Gun->amount; i++) {
                Aimpoint->Aimpoint[i].x = bounds->Grid[0].x + sin(dTheta * i) * radius;
                Aimpoint->Aimpoint[i].y = bounds->Grid[0].y + cos(dTheta * i) * radius;
                Aimpoint->Aimpoint[i].z = bounds->Grid[0].z;
            }

            break;
        }

        case 6: /* Irregular */ {

            SheafSolve_Irregular(Gun, Aimpoint, bounds);
            break;
        }

        default:
            break;
    }

    return Aimpoint;
}
