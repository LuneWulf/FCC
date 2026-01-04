//
// Created by simon on 28-12-2025.
//

#include "structs.h"

#ifndef VECTOR_BALLISTICS_ADJUSTQUADRANT_H
#define VECTOR_BALLISTICS_ADJUSTQUADRANT_H

void AdjustQuadrant(int *InitialSweep, double *_1Angle, double *_2Angle, double *Quadrant, double Deflection, double *RangeError, Missile *Projectile, FireData *ProjectileData, struct QuadrantUpdate qu);

#endif //VECTOR_BALLISTICS_ADJUSTQUADRANT_H