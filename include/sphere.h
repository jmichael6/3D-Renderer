#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <shape.h>
#include <ray_casting.h>

shape* make_sphere();

tuple sphere_normal_at(shape* prop, tuple object_pt);
intersection_list intersect_sphere(shape *sphere, ray beam);
#endif
