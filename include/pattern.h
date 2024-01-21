#ifndef __PATTERN_H__
#define __PATTERN_H__

#include <pattern_struct.h>

#include <stdlib.h>
#include <shape.h>
#include <stdio.h>


general_pattern make_pattern();
tuple pattern_at_object(general_pattern pattern, shape* object, tuple world_pt);
general_pattern make_stripe_pattern(tuple even, tuple odd);

#endif
