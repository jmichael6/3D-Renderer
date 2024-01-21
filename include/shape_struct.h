#ifndef __SHAPE_STRUCT_H__
#define __SHAPE_STRUCT_H__

#include <matrix.h>
#include <pattern_struct.h>

typedef struct material_properties {
	tuple color;
	float ambient;
	float diffuse;
	float specular;
	float shininess;
} material_properties;


typedef enum {SPHERE, PLANE} shape_type;

typedef struct shape {
	shape_type type;	
	void* properties;

	matrix transform;

	material_properties material; 

	bool has_pattern;
	general_pattern pattern;
} shape;

#endif
