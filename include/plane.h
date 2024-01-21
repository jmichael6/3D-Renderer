#ifndef __PLANE_H__
#define __PLANE_H__

#include <shape.h>
#include <ray_casting.h>

shape* make_plane();

tuple plane_normal_at(shape* plane, tuple pt);
intersection_list intersect_plane(shape* plane, ray beam);

#endif
