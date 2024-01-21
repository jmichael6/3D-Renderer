#ifndef __RAY_H__
#define __RAY_H__

#define MAX_INTERSECTIONS 20

#include <tuple.h>
#include <matrix.h>
#include <ray_struct.h>
#include <stddef.h>


ray make_ray(tuple origin, tuple direction);

tuple ray_position(ray r, float t);
ray transform_ray(matrix m, ray beam);

intersection make_intersection(float t, shape* object);
bool equal_intersection(intersection i1, intersection i2);


intersection_list make_intersection_list();
void add_intersection(intersection_list* list, intersection intsct);
void add_intersection_list(intersection_list* list, 
	       	              intersection_list* sublist);
void clear_intersection_list(intersection_list* list);

intersection identify_hit(intersection_list list, bool* exists);

#endif
