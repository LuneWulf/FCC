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

#ifndef ADJUSTMENTS
#define ADJUSTMENTS

struct Adjustments {
    double Range;
    double Lat;
    double NS;
    double EW;
};

#endif

#ifndef VECTOR_BALLISTICS_ADJUSTTGT_H
#define VECTOR_BALLISTICS_ADJUSTTGT_H

struct Vector3D AdjustTgt(struct Vector3D Tgt, struct Vector3D Gun, struct Adjustments *Adjust);

#endif //VECTOR_BALLISTICS_ADJUSTTGT_H