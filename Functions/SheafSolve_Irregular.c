//
// Created by simon on 31-12-2025.
//

#include "SheafSolve_Irregular.h"
#include "VectorDir.h"
#include "VectorDistance.h"
#include <stdlib.h>
#include <math.h>
#include "structs.h"

void SheafSolve_Irregular (struct GunStore *Gun, Aimpoints *Aimpoint, Bounds *bounds) {

    Aimpoint->amount = Gun->amount;

    int EqualGunAndBounds = (Gun->amount == bounds->GridAmount) ? 1 : 0;

    switch (EqualGunAndBounds) {
        case 0: {

            double distance = 0;

            double *Length = calloc(bounds->GridAmount - 1, sizeof(double));
            double *Direction = calloc(bounds->GridAmount - 1, sizeof(double));

            for (int i = 0; i < bounds->GridAmount - 1; i++) {

                Direction[i] = VectorDir(bounds->Grid[i], bounds->Grid[i + 1]);

                double tempDistance = VectorDistance(bounds->Grid[i], bounds->Grid[i + 1]);

                Length[i] = tempDistance;
                distance += tempDistance;

            }

            double DistanceInterval = distance / (Gun->amount - 1);

            int interval = 0;

            Aimpoint->Aimpoint[0].x = bounds->Grid[0].x;
            Aimpoint->Aimpoint[0].y = bounds->Grid[0].y;
            Aimpoint->Aimpoint[0].z = bounds->Grid[0].z;

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

                double dz = bounds->Grid[interval].z - bounds->Grid[interval + 1].x;
                double theta = dz / Length[interval];
                double adjustZ = adjustXY * theta;

                if (NewInterval > 0) {
                    Aimpoint->Aimpoint[i].x = bounds->Grid[interval + NewInterval - 1].x + sin(Direction[interval]) * adjustXY;
                    Aimpoint->Aimpoint[i].y = bounds->Grid[interval + NewInterval - 1].y + cos(Direction[interval]) * adjustXY;
                    Aimpoint->Aimpoint[i].z = bounds->Grid[interval + NewInterval - 1].z + adjustZ;
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

                Aimpoint->Aimpoint[i] = bounds->Grid[i];

            }

            break;
        }
    }

}