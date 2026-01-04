/*
 *  Created By Simon Bergmann
 *
 *  Last Edit: 28/12-2025
 *
 *  Arguments:
 *      i - (High or low angle, 1/0, <unitless>)
 *      *InitialSweep - (First time adjusting quadrant 1/0, <unitless>)
 *      *Projectile (Impact values):
 *          .Velocity - (Absolute velocity, <m/s>)
 *          .Vx - (Velocity x-component, <m/s>)
 *          .Vy - (Velocity y-component, <m/s>)
 *          .Vz - (Velocity z-component, <m/s>)
 *          .x - (X position, <m>)
 *          .y - (Y position, <m>)
 *          .z - (Z position, <m>)
 *          .Summit - (Maximum altitude reached, <m>)
 *          .t - (time, <s>)
 *          .DisEr - (Distance between target and impact site, <m>)
 *          .SummitX - (X position of summit, <m>)
 *          .SummitY - (Y position of summit, <m>)
 *          .SummitDis - (Distance between summit and Gun, <m>)
 *          .AOI - (Angle of Impact relative to horizon, <radians>)
 *      Gun - (3D Vector, components in <m>)
 *      *TempDeflection - (Placeholder deflection, <radians>)
 *      Deflection - (Compass angle, <radians>)
 *      *Quadrant - (angle from ground to line of fire, <radians>)
 *
 *  Returns:
 *      void
 *
 */

#include "../Headers/Conversions.h"
#include "../Headers/DeflectionUpdate.h"
#include "../Headers/VectorDir.h"
#include "structs.h"

void DeflectionUpdate(int i, int *InitialSweep, struct Missile Projectile, struct Vector3D Gun, double *TempDeflection, double *Deflection, double *Quadrant) {

    struct Vector3D Hit = {Projectile.x, Projectile.y, 0};

    double dAz = *TempDeflection - VectorDir(Gun, Hit);

    *Deflection += dAz;

    *InitialSweep = 1;

    if (i == 0) {
        *Quadrant = 90 * DEG_TO_RAD;
    } else {
        *Quadrant = 0;
    }
}
