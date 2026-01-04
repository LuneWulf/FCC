//
// Created by simon on 28-12-2025.
//

#include "structs.h"

#ifndef VECTOR_BALLISTICS_DEFLECTIONUPDATE_H
#define VECTOR_BALLISTICS_DEFLECTIONUPDATE_H

void DeflectionUpdate(int i, int *InitialSweep, struct Missile Projectile, struct Vector3D Gun, double *VirDeflection, double *Deflection, double *Quadrant);

#endif //VECTOR_BALLISTICS_DEFLECTIONUPDATE_H