//
// Created by simon on 31-12-2025.
//

#include "SheafSolve_Open.h"
#include <VectorDir.h>
#include <math.h>

void SheafSolve_Open (struct Guns *Gun, struct Aimpoints *Aimpoint, struct BoundingGrids *Bounds, int middle) {

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
}

