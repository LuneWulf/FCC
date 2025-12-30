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

#ifndef VECTOR_BALLISTICS_VECTORDIR_H
#define VECTOR_BALLISTICS_VECTORDIR_H

double VectorDir(struct Vector3D VecFrom, struct Vector3D VecTo);

#endif //VECTOR_BALLISTICS_VECTORDIR_H