/*
 *  Created By Simon Bergmann
 *
 *  Last Edit: 28/12-2025
 *
 *  Arguments:
 *      *InitialSweep - (First time adjusting quadrant 1/0, <unitless>)
 *      *_1Angle - (Quadrant bracket extrema #1, <radians>)
 *      *_2Angle - (Quadrant bracket extrema #2, <radians>)
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
 */

#include "../Headers/Conversions.h"
#include "../Headers/QuadrantUpdate.h"
#include "../Headers/AdjustQuadrant.h"
#include "structs.h"

void QuadrantUpdate(int i, int *InitialSweep, double *_1Angle, double *_2Angle, double *Quadrant, double Deflection, double *RangeError, Missile *Projectile, FireData *ProjectileData, struct QuadrantUpdate qu) {
    switch (i) {
        case 0:
            if (*InitialSweep == 1 && *RangeError > 0) {
                *_1Angle = *Quadrant;
                *Quadrant -= 1 * DEG_TO_RAD;
                *_2Angle = *Quadrant;
            } else {
                AdjustQuadrant(InitialSweep,_1Angle,_2Angle,Quadrant,Deflection,RangeError,Projectile,ProjectileData,qu);
            }

            break;
        case 1:
            if (*InitialSweep == 1 && *RangeError > 0) {
                *_1Angle = *Quadrant;
                *Quadrant += 1 * DEG_TO_RAD;
                *_2Angle = *Quadrant;

            } else {
                AdjustQuadrant(InitialSweep,_1Angle,_2Angle,Quadrant,Deflection,RangeError,Projectile,ProjectileData,qu);
            }

            break;
        default:
            break;
    }
}

