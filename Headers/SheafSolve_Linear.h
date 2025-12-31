//
// Created by simon on 31-12-2025.
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

#ifndef AIMPOINTS
#define AIMPOINTS

struct Aimpoints {
    struct Vector3D Aimpoint[30];
    int SheafType;
    int amount;
};

#endif

#ifndef BOUNDINGGRIDS
#define BOUNDINGGRIDS

struct BoundingGrids {
    struct Vector3D Grid[10];
    int GridAmount;
    double length;
    double width;
    double attitude;
    double radius;
    int SheafType;
    int allowMultipleAimpoints;
    double EBR;
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

#ifndef FCC_SHEAFSOLVE_LINEAR_H
#define FCC_SHEAFSOLVE_LINEAR_H

void SheafSolve_Linear (struct Guns *Gun, struct Aimpoints *Aimpoint, struct BoundingGrids *Bounds, int middle);

#endif //FCC_SHEAFSOLVE_LINEAR_H