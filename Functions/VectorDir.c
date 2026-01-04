/*
 *  Created By Simon Bergmann
 *
 *  Last Edit: 28/12-2025
 *
 *  Arguments:
 *      VecFrom - (3D vector, components in <m>)
 *      VecTo - (3D vector, components in <m>)
 *
 *  Returns:
 *      Direction - (Compass angle from VecFrom to VecTo, <radians>)
 *
 */

#include "../Headers/VectorDir.h"
#include "../Headers/CusaTan.h"
#include "structs.h"


double VectorDir(Vector3D VecFrom, Vector3D VecTo) {

    // In arma 3, direction is measured clockwise from the y-axis, hence rise becomes dX and run becomes dY.

    const double dX = VecTo.x - VecFrom.x;
    const double dY = VecTo.y - VecFrom.y;

    const double Dir = CusaTan(dY, dX);

    return Dir;
}