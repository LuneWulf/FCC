/*
 *  Created By Simon Bergmann
 *
 *  Last Edit: 28/12-2025
 *
 *  Arguments:
 *      dx - (<unitless>)
 *      dy - (<unitless>)
 *
 *  Returns:
 *      Compass angle - (<radians>)
 *
 */

#include "../Headers/CusaTan.h"
#include <math.h>

double CusaTan (double dX, double dY) {

    double Dir = atan2(dY, dX);
    if (Dir < 0) {
        Dir += 2* M_PI;
    }

    return Dir;
}
