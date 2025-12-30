//
// Created by simon on 28-12-2025.
//

#ifndef VECTOR3D
#define VECTOR3D

struct Vector3D {
    double x;
    double y;
    double z;
};

#endif

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

#ifndef FIREDATA
#define FIREDATA

struct FireData {
    int Charge;
    double DeflectionHigh;
    double DeflectionLow;
    double QuadrantHigh;
    double QuadrantLow;
    double ToFHigh;
    double ToFLow;
    double AOIHigh;
    double AOILow;
    double SummitHigh;
    double SummitLow;
    double SummitDisHigh;
    double SummitDisLow;
    double DisErHigh;
    double DisErLow;
    double DistanceTravelled;
};

#endif

#ifndef QUADRANTUPDATE
#define QUADRANTUPDATE

struct QuadrantUpdate {
    double Range;
    double CD;
    double MuzzVel;
    struct Vector3D Tgt;
    struct Vector3D Gun;
    struct Context *Atmosphere;
    struct Config *Cfg;
};

#endif

#ifndef VECTOR_BALLISTICS_QUADRANTUPDATE_H
#define VECTOR_BALLISTICS_QUADRANTUPDATE_H

void QuadrantUpdate(int i, int *InitialSweep, double *_1Angle, double *_2Angle, double *Quadrant, double Deflection, double *RangeError, struct Missile *Projectile, struct FireData *ProjectileData, struct QuadrantUpdate qu);

#endif //VECTOR_BALLISTICS_QUADRANTUPDATE_H

