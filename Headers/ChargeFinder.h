//
// Created by simon on 28-12-2025.
//

#include "structs.h"

#ifndef VECTOR_BALLISTICS_CHARGEFINDER_H
#define VECTOR_BALLISTICS_CHARGEFINDER_H

FireData ChargeFinder(Vector3D Tgt, Vector3D Gun, Ammo *Charges, struct Config *Cfg, struct Adjustments *Adjust, struct Context *Atmosphere);

#endif //VECTOR_BALLISTICS_CHARGEFINDER_H