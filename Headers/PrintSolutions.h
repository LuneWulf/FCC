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

#ifndef GUNS
#define GUNS

struct Guns {
    struct Vector3D Gun[30];
    struct FireData Data[30];
    int amount;
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

#ifndef AMMO
#define AMMO

struct Ammo {
    double MuzzVel[20];
    double MaxRange[20];
    int ChargeAmount;
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

#ifndef VECTOR_BALLISTICS_PRINTSOLUTIONS_H
#define VECTOR_BALLISTICS_PRINTSOLUTIONS_H

void PrintSolutions(int i, struct Guns *Gun, struct Aimpoints *Aimpoint, struct Ammo *Charges, struct Config *Cfg);

#endif //VECTOR_BALLISTICS_PRINTSOLUTIONS_H