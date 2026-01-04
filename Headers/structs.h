#ifndef AMMO
#define AMMO

struct Ammo {
    double MuzzVel[20];
    double MaxRange[20];
    int ChargeAmount;
};

#endif

#ifndef MRs
#define MRs

struct MR {
    double Quadrant;
    double Range;
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
    double ErrorHigh;
    double ErrorLow;
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
