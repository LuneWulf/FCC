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

struct Aimpoints *SheafSolver(struct BoundingGrids *Bounds, struct Guns *Gun) {

    struct Aimpoints *Aimpoint = calloc(1, sizeof(struct Aimpoints));

    Aimpoint->SheafType = Bounds->SheafType;
    const int middle = Gun->amount / 2 + 1;

    switch (Bounds->SheafType) {
        case 0: /* Parallel */
        case 1: /* Converged */ {

            Aimpoint->Aimpoint[0] = Bounds->Grid[0];
            Aimpoint->amount = 1;

            break;
        }

        case 2: /* Open */ {

            SheafSolve_Open(Gun, Aimpoint, Bounds, middle);
            break;
        }

        case 3: /* Linear */ {

            SheafSolve_Linear(Gun, Aimpoint, Bounds, middle);
            break;
        }

        case 4: /* Rectangular */ {

            SheafSolve_Rectangular(Gun, Aimpoint, Bounds, middle);
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

            SheafSolve_Irregular(Gun, Aimpoint, Bounds);
            break;
        }

        default:
            break;
    }

    return Aimpoint;
}
