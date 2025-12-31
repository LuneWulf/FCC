//
// Created by simon on 31-12-2025.
//

#include "SheafSolve_Irregular.h"
#include "VectorDir.h"
#include "VectorDistance.h"
#include <stdlib.h>
#include <math.h>

void SheafSolve_Irregular (struct Guns *Gun, struct Aimpoints *Aimpoint, struct BoundingGrids *Bounds) {

    int EqualGunAndBounds = (Gun->amount == Bounds->GridAmount) ? 1 : 0;

    switch (EqualGunAndBounds) {
        case 0: {

            double distance = 0;

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

                int NewInterval = 0;

                double adjustXY = DistanceInterval;

                Length[interval] -= DistanceInterval;

                while (Length[interval] < 0) {
                    interval++;
                    NewInterval++;
                    Length[interval] += Length[interval - 1];
                    adjustXY = -Length[interval - 1];
                }

                double dz = Bounds->Grid[interval].z - Bounds->Grid[interval + 1].x;
                double theta = dz / Length[interval];
                double adjustZ = adjustXY * theta;

                if (NewInterval > 0) {
                    Aimpoint->Aimpoint[i].x = Bounds->Grid[interval + NewInterval - 1].x + sin(Direction[interval]) * adjustXY;
                    Aimpoint->Aimpoint[i].y = Bounds->Grid[interval + NewInterval - 1].y + cos(Direction[interval]) * adjustXY;
                    Aimpoint->Aimpoint[i].z = Bounds->Grid[interval + NewInterval - 1].z + adjustZ;
                }

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

        case 1: {

            for (int i = 0; i < Gun->amount; i++) {

                Aimpoint->Aimpoint[i] = Bounds->Grid[i];

            }

            break;
        }
    }

}