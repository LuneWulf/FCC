//
// Created by simon on 28-12-2025.
//

#include "structs.h"

#ifndef VECTOR_BALLISTICS_CHARGEFINDER_H
#define VECTOR_BALLISTICS_CHARGEFINDER_H

struct FireData ChargeFinder(struct Vector3D Tgt, struct Vector3D Gun, struct Ammo *Charges, struct Config *Cfg, struct Adjustments *Adjust, struct Context *Atmosphere);

#endif //VECTOR_BALLISTICS_CHARGEFINDER_H