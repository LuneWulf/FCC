#ifndef AMMO
#define AMMO

typedef struct {
    double MuzzVel[20];
    double MaxRange[20];
    int ChargeAmount;
} Ammo;

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

typedef struct {
    double x;
    double y;
    double z;
} Vector3D;

#endif

#ifndef VECTOR2D
#define VECTOR2D

typedef struct {
    double x;
    double y;
} Vector2D;

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

typedef struct {
    Vector3D Aimpoint[30];
    int SheafType;
    int amount;
} Aimpoints;

#endif

#ifndef BOUNDINGGRIDS
#define BOUNDINGGRIDS

typedef struct {
    Vector3D Grid[10];
    int GridAmount;
    double length;
    double width;
    double attitude;
    double radius;
    int SheafType;
    int allowMultipleAimpoints;
    double EBR;
} Bounds;

#endif

#ifndef FIREDATA
#define FIREDATA

typedef struct {
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
    double MaxErrorHigh;
    double MaxErrorLow;
} FireData;

#endif

#ifndef GUNS
#define GUNS

struct GunStore {
    Vector3D Gun[30];
    FireData Data[30];
    int amount;
};

#endif

#ifndef CONTEXT
#define CONTEXT

struct Context {
    double Temperature;
    double Pressure;
    double Humidity;
    Vector2D Wind;
};

#endif

#ifndef MISSILE
#define MISSILE

typedef struct {
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
} Missile;

#endif

#ifndef QUADRANTUPDATE
#define QUADRANTUPDATE

struct QuadrantUpdate {
    double Range;
    double CD;
    double MuzzVel;
    Vector3D Tgt;
    Vector3D Gun;
    struct Context *Atmosphere;
    struct Config *Cfg;
};

#endif
