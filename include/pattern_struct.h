#ifndef __PATTERN_STRUCT_H__
#define __PATTERN_STRUCT_H__

#include <matrix.h>

//Remeber to add NONE in objects
typedef enum {NONE, STRIPE, RING} pattern_types;

typedef struct general_pattern {
	matrix transform;
	pattern_types type;
	void *details;
} general_pattern;

general_pattern make_pattern();

#endif
