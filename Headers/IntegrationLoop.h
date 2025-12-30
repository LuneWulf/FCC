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

#ifndef VECTOR_BALLISTICS_INTEGRATIONLOOP_H
#define VECTOR_BALLISTICS_INTEGRATIONLOOP_H

struct Missile IntegrationLoop(double dt, double CD, double MuzzVel, double Quadrant, double Deflection, struct Vector3D Gun, struct Vector3D Tgt, struct Context *Atmosphere);

#endif //VECTOR_BALLISTICS_INTEGRATIONLOOP_H