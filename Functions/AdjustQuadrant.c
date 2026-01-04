/*
 *  Created By Simon Bergmann
 *
 *  Last Edit: 28/12-2025
 *
 *  Arguments:
 *      *InitialSweep - (First time adjusting quadrant 1/0, <unitless>)
 *      *_1Angle - (Quadrant bracket extrema, <radians>)
 *      *_2Angle - (Quadrant bracket extrema, <radians>)
 *      *Quadrant - (angle from ground to line of fire, <radians>)
 *      Deflection - (Compass angle, <radians>)
 *      *RangeError - (Difference between Tgt range and Projectile range, <m>)
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
 *      *ProjectileData:
 *          .DistanceTravelled - (Distance from Gun to Projectile Hit, <m>)
 *      *qu:
 *          .Range - (Distance from Gun to Tgt, <m>)
 *          .CD - (Drag Coefficient, <m>)
 *          .MuzzVel - (Muzzle Velocity, <m/s>)
 *          .Tgt - (3D Vector, components in <m>)
 *          .Gun - (3D Vector, components in <m>)
 *          .*Atmosphere:
 *              .Temperature - (<Degrees C>)
 *              .Pressure - (<hPa>)
 *              .Humidity - (Relative Humidity <%>)
 *              .Wind - (2D Vector, components in <m/s>)
 *          .*Cfg:
 *              .dt - (simulation time step, <s>)
 *
 *  Returns:
 *      void
 *
 *
 */

#include "../Headers/AdjustQuadrant.h"
#include "../Headers/IntegrationLoop.h"
#include <math.h>
#include "structs.h"

void AdjustQuadrant(int *InitialSweep, double *_1Angle, double *_2Angle, double *Quadrant, double Deflection, double *RangeError, struct Missile *Projectile, struct FireData *ProjectileData, struct QuadrantUpdate qu) {
    if (*RangeError < 0) {

        *InitialSweep = 0;

        *Quadrant = (*_1Angle + *_2Angle) / 2;

        *Projectile = IntegrationLoop(qu.Cfg->dt, qu.CD, qu.MuzzVel, *Quadrant, Deflection, qu.Gun, qu.Tgt, qu.Atmosphere);

        ProjectileData->DistanceTravelled = sqrt( (Projectile->y - qu.Gun.y)*(Projectile->y - qu.Gun.y) + (Projectile->x - qu.Gun.x)*(Projectile->x - qu.Gun.x));

        *RangeError = qu.Range - ProjectileData->DistanceTravelled;

        if (*RangeError < 0) *_2Angle = *Quadrant;
        if (*RangeError > 0) *_1Angle = *Quadrant;
        *Quadrant = (*_1Angle + *_2Angle) / 2;

    } else if (*RangeError > 0) {
        *_1Angle = *Quadrant;
        *Quadrant = (*_1Angle + *_2Angle) / 2;
    }
}
