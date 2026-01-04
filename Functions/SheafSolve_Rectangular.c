//
// Created by simon on 31-12-2025.
//

#include "SheafSolve_Rectangular.h"
#include <math.h>
#include "structs.h"


void SheafSolve_Rectangular (struct GunStore *Gun, Aimpoints *Aimpoint, Bounds *Bounds, int middle) {

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
}