//
// Created by simon on 31-12-2025.
//

#include "SheafSolve_Linear.h"
#include "VectorDir.h"
#include "VectorDistance.h"
#include <math.h>
#include "structs.h"

void SheafSolve_Linear (struct GunStore *Gun, Aimpoints *Aimpoint, Bounds *bounds) {

    double dX, dY;

    Aimpoint->amount = Gun->amount;

    if (bounds->length != 0) {

        dX = sin(bounds->attitude) * bounds->length / (Gun->amount - 1);
        dY = cos(bounds->attitude) * bounds->length / (Gun->amount - 1);

    } else {

        const double length = VectorDistance(bounds->Grid[0], bounds->Grid[1]);
        const double attitude = VectorDir(bounds->Grid[0], bounds->Grid[1]);

        dX = sin(attitude) * length / (Gun->amount - 1);
        dY = cos(attitude) * length / (Gun->amount - 1);

    }

    Aimpoint->Aimpoint[0] = bounds->Grid[0];

    for (int i = 1; i < Gun->amount; i++) {
        Aimpoint->Aimpoint[i].x = bounds->Grid[0].x + i * dX;
        Aimpoint->Aimpoint[i].y = bounds->Grid[0].y + i * dY;
        Aimpoint->Aimpoint[i].z = bounds->Grid[0].z;
    }
}