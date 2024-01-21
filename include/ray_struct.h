#ifndef __RAY_STRUCT_H__
#define __RAY_STRUCT_H__

#include <shape_struct.h>

typedef struct ray {
	tuple origin;
	tuple direction;
} ray;


typedef struct intersection {
	float t;
	shape* object;
} intersection;


typedef struct intersection_list {
	int size;
	intersection elt[MAX_INTERSECTIONS];
} intersection_list;




#endif
