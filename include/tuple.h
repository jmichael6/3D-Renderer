#ifndef __TUPLE_H__
#define __TUPLE_H__

#include <math.h>

#define EPS 0.0001

typedef enum {false, true} bool;

typedef struct tuple {
    float x;
    float y;
    float z;
    float w;
} tuple;

float absl(float x);
bool equal(float x, float y);

tuple make_tuple(float x, float y, float z, float w);
tuple point(float x, float y, float z);
tuple vector(float x, float y, float z);
tuple color(float r, float g, float b);
bool is_point(tuple t);
bool is_vector(tuple t);

bool eqv(tuple t1, tuple t2);
tuple add(tuple a, tuple b);
tuple sub(tuple a, tuple b);
tuple neg(tuple a);
tuple mul(tuple a, float f);
tuple divide(tuple a, float f);
float magnitude(tuple a);
tuple normalize(tuple a);
float dot(tuple a, tuple b);
tuple cross(tuple a, tuple b);
tuple hadamard(tuple a, tuple b);

#endif
