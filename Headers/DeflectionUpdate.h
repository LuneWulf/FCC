//
// Created by simon on 28-12-2025.
//

#ifndef MISSILE
#define MISSILE

struct Missile {
    double Velocity;
    double Vx;
    double Vy;
    double Vz;
    double x;
    double y;
    double z;
    double Summit;
    double t;
    double DisEr;
    double SummitX;
    double SummitY;
    double SummitDis;
    double AOI;
};

#endif

#ifndef VECTOR3D
#define VECTOR3D

struct Vector3D {
    double x;
    double y;
    double z;
};

#endif

#ifndef VECTOR_BALLISTICS_DEFLECTIONUPDATE_H
#define VECTOR_BALLISTICS_DEFLECTIONUPDATE_H

void DeflectionUpdate(int i, int *InitialSweep, struct Missile Projectile, struct Vector3D Gun, double *VirDeflection, double *Deflection, double *Quadrant);

#endif //VECTOR_BALLISTICS_DEFLECTIONUPDATE_H