#ifndef __LIGHTING_H__
#define __LIGHTING_H__

#include <tuple.h>
#include <shape.h>
#include <pattern.h>

typedef struct point_light {
	tuple position;
	tuple intensity;
} point_light;

point_light make_point_light(tuple position, tuple intensity);

tuple find_reflection(tuple in, tuple normal);

tuple lighting_color(shape* object, material_properties mat, point_light light, tuple pt, tuple eyev, tuple normal, bool in_shadow);

#endif
