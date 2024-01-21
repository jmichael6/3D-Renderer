#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <shape_struct.h>
#include <plane.h>
#include <sphere.h>
#include <ray_casting.h>

shape* make_shape();
material_properties make_material();
void set_pattern(shape* object, general_pattern pattern);

tuple normal_at(shape* object, tuple world_pt);
intersection_list intersect_object(shape* object, ray beam);

#endif
