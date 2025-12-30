//
// Created by simon on 28-12-2025.
//

#ifndef AMMO
#define AMMO

struct Ammo {
    double MuzzVel[20];
    double MaxRange[20];
    int ChargeAmount;
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

#ifndef VECTOR2D
#define VECTOR2D

struct Vector2D {
    double x;
    double y;
};

#endif

#ifndef ADJUSTMENTS
#define ADJUSTMENTS

struct Adjustments {
    double Range;
    double Lat;
    double NS;
    double EW;
};

#endif

#ifndef CONFIG
#define CONFIG

struct Config {
    double dt;
    double kFactor;
    double MaxError;
    int FullInfo;
    int FindCharge;
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

#ifndef CONTEXT
#define CONTEXT

struct Context {
    double Temperature;
    double Pressure;
    double Humidity;
    struct Vector2D Wind;
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

#ifndef VECTOR_BALLISTICS_SOLUTIONSOLVER_H
#define VECTOR_BALLISTICS_SOLUTIONSOLVER_H

struct FireData SolutionSolver(struct Vector3D Tgt, struct Vector3D Gun, int Charge, struct Ammo *Charges, struct Config *Cfg, struct Adjustments *Adjust, struct Context *Atmosphere);

#endif //VECTOR_BALLISTICS_SOLUTIONSOLVER_H