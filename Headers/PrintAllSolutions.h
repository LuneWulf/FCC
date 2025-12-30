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

#ifndef VECTOR2D
#define VECTOR2D

struct Vector2D {
    double x;
    double y;
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

#ifndef AMMO
#define AMMO

struct Ammo {
    double MuzzVel[20];
    double MaxRange[20];
    int ChargeAmount;
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

#ifndef AIMPOINTS
#define AIMPOINTS

struct Aimpoints {
    struct Vector3D Aimpoint[30];
    int SheafType;
    int amount;
};

#endif

#ifndef GUNS
#define GUNS

struct Guns {
    struct Vector3D Gun[30];
    struct FireData Data[30];
    int amount;
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

#ifndef VECTOR_BALLISTICS_PRINTALLSOLUTIONS_H
#define VECTOR_BALLISTICS_PRINTALLSOLUTIONS_H

void PrintAllSolutions(struct Context *Atmosphere, struct Aimpoints *Tgts, struct Guns *Gun, struct Ammo *Charges, int Charge, struct Config *Cfg, struct Adjustments *Adjust);

#endif //VECTOR_BALLISTICS_PRINTALLSOLUTIONS_H