/*
 *  Created By Simon Bergmann
 *
 *  Last Edit: 28/12-2025
 *
 *  Arguments:
 *      VecFrom - (3D Vector, components in <m>)
 *      VecTo - (3D Vector, components in <m>)
 *
 *  Returns:
 *      Distance - (Between vectors, <m>)
 *
 */

#include "../Headers/VectorDistance.h"
#include <math.h>

double VectorDistance(struct Vector3D VecFrom, struct Vector3D VecTo) {

    const double dY = VecFrom.y - VecTo.y;
    const double dX = VecFrom.x - VecTo.x;

    const double Distance = sqrt( dX*dX + dY*dY);

    return Distance;
}