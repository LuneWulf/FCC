//
// Created by simon on 28-12-2025.
//

#include "structs.h"

#ifndef VECTOR_BALLISTICS_INTEGRATIONLOOP_H
#define VECTOR_BALLISTICS_INTEGRATIONLOOP_H

struct Missile IntegrationLoop(double dt, double CD, double MuzzVel, double Quadrant, double Deflection, struct Vector3D Gun, struct Vector3D Tgt, struct Context *Atmosphere);

#endif //VECTOR_BALLISTICS_INTEGRATIONLOOP_H