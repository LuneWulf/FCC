//
// Created by simon on 28-12-2025.
//

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

#ifndef VECTOR_BALLISTICS_AIRDENSITY_H
#define VECTOR_BALLISTICS_AIRDENSITY_H

double airDensity(struct Context *Atmosphere);

#endif //VECTOR_BALLISTICS_AIRDENSITY_H