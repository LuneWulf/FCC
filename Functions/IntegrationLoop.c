/*
 *  Created By Simon Bergmann
 *
 *  Last Edit: 28/12-2025
 *
 *  Arguments:
 *      dt - (simulation time step, <s>)
 *      CD - (drag coefficient, <m>)
 *      MuzzVel - (<m/s>)
 *      Quadrant - (angle from ground to line of fire, <radians>)
 *      Deflection - (compass angle, <radians>)
 *      Gun - (3D Vector, components in <m>)
 *      Tgt - (3D Vector, components in <m>)
 *      *Atmosphere:
 *          .Temperature - (<Degrees C>)
 *          .Pressure - (<hPa>)
 *          .Humidity - (Relative Humidity, <%>)
 *          .Wind - (2D Vector, components in <m/s>)
 *
 *  Returns (values at impact):
 *      Missile:
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
 *
 */

#include "../Headers/IntegrationLoop.h"
#include <math.h>
#include <stdio.h>
#include "structs.h"

#include "CusaTan.h"

Missile IntegrationLoop(double dt, double CD, double MuzzVel, double Quadrant, double Deflection, Vector3D Gun, Vector3D Tgt, struct Context *Atmosphere) {

    Missile Projectile;

    Projectile.Velocity = MuzzVel;
    Projectile.Vx = MuzzVel * cos(Quadrant) * sin(Deflection);
    Projectile.Vy = MuzzVel * cos(Quadrant) * cos(Deflection);
    Projectile.Vz = MuzzVel * sin(Quadrant);
    Projectile.x = Gun.x;
    Projectile.y = Gun.y;
    Projectile.z = Gun.z;
    Projectile.Summit = Gun.z;
    Projectile.SummitX = Gun.x;
    Projectile.SummitY = Gun.y;
    Projectile.DisEr = 0;
    Projectile.t = 0;

    for(Projectile.t = 0; Projectile.Vz > 0 || Projectile.z > Tgt.z; Projectile.t += dt) {

        double tVx = Projectile.Vx - Atmosphere->Wind.x;
        double tVy = Projectile.Vy - Atmosphere->Wind.y;

        Projectile.Velocity = sqrt( tVx*tVx + tVy*tVy + Projectile.Vz*Projectile.Vz);

        const double drag = dt * CD * Projectile.Velocity;

        Projectile.Vx -= drag * tVx;
        Projectile.Vy -= drag * tVy;
        Projectile.Vz -= drag * Projectile.Vz + dt * 9.81;

        Projectile.x += dt * Projectile.Vx;
        Projectile.y += dt * Projectile.Vy;
        Projectile.z += dt * Projectile.Vz;

        if (Projectile.Summit < Projectile.z) {
            Projectile.Summit = Projectile.z;
            Projectile.SummitX = Projectile.x;
            Projectile.SummitY = Projectile.y;
        }
    }

    double InterDef = CusaTan(Projectile.Vy, Projectile.Vx);

    Projectile.AOI = atan( Projectile.Vz / sqrt( Projectile.Vx*Projectile.Vx + Projectile.Vy*Projectile.Vy) );

    double InterDz = Tgt.z - Projectile.z;
    double InterDLat = InterDz * tan(M_PI / 2 + Projectile.AOI);
    double InterDx = sin(InterDef) * InterDLat;
    double InterDy = cos(InterDef) * InterDLat;

    Projectile.z = Tgt.z;
    Projectile.x -= InterDx;
    Projectile.y -= InterDy;

    double InterDt = InterDz / Projectile.Vz;

    Projectile.t -= InterDt;

    double SummitdX = Projectile.SummitX - Gun.x;
    double Summitdy = Projectile.SummitY - Gun.y;

    Projectile.SummitDis = sqrt(SummitdX*SummitdX + Summitdy*Summitdy);

    double errX = Projectile.x - Tgt.x;
    double errY = Projectile.y - Tgt.y;

    Projectile.DisEr = sqrt(errX*errX + errY*errY);

    return Projectile;
}
