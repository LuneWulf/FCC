//
// Created by simon on 31-12-2025.
//

#include "SheafSolve_Linear.h"
#include "VectorDir.h"
#include "VectorDistance.h"
#include <math.h>
#include "structs.h"

void SheafSolve_Linear (struct Guns *Gun, struct Aimpoints *Aimpoint, struct BoundingGrids *Bounds, int middle) {

    double dX, dY;

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
}