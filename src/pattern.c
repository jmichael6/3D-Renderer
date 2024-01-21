#include <pattern.h>

typedef struct stripe_pattern {
	tuple even_color;
	tuple odd_color;
} stripe_pattern;


stripe_pattern* make_stripe_details(tuple even, tuple odd) {
	stripe_pattern* stripe = malloc(sizeof(stripe_pattern));

	stripe->even_color = even;
	stripe->odd_color = odd;

	return stripe;
}


tuple stripe_at(stripe_pattern* stripe, tuple pt) {
	int x = (int) pt.x;

	if(x % 2 == 0)
		return stripe->even_color;
	else
		return stripe->odd_color;
}



general_pattern make_pattern() {
	general_pattern pattern;

	pattern.transform = identity();
	pattern.type = NONE;
	pattern.details = NULL;

	return pattern;
}

tuple pattern_at_object(general_pattern pattern, shape* object, tuple world_pt) {
	tuple object_pt = apply(inverse(object->transform), world_pt);
	tuple pattern_pt = apply(inverse(pattern.transform), object_pt);

	if(pattern.type == NONE) {
		printf("ERROR: Pattern with no type\n");
		exit(0);
	} else if (pattern.type == STRIPE)
		return stripe_at(pattern.details, pattern_pt);
	else {
		printf("ERROR: Pattern of unknown type\n");
		exit(0);
	}
}



general_pattern make_stripe_pattern(tuple even, tuple odd) {
	general_pattern stripe = make_pattern();
	stripe.type = STRIPE;
	stripe.details = make_stripe_details(even, odd);

	return stripe;
}
