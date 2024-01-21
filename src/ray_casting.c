#include <ray_casting.h>

ray make_ray(tuple origin, tuple direction) {
	ray beam;
	beam.origin = origin;
	beam.direction = direction;
	return beam;
}

tuple ray_position(ray beam, float t) {
	return add(beam.origin, mul(beam.direction, t));
}

ray transform_ray(matrix m, ray beam) {
	beam.origin = apply(m, beam.origin);
	beam.direction = apply(m, beam.direction);

	return beam;
}



intersection make_intersection(float t, shape* object) {	
	intersection intsct;
	intsct.t = t;
	intsct.object = object;
	return intsct;
}

bool equal_intersection(intersection i1, intersection i2) {
	if(equal(i1.t, i2.t) && (i1.object == i2.object))
		return true;
	else 
		return false;
}

intersection_list make_intersection_list() {
	intersection_list list;
	list.size = 0;
	return list;
}


void clear_intersection_list(intersection_list* list) {
	list->size = 0;
}

void add_intersection(intersection_list* list, intersection intsct) {
	if(list->size < MAX_INTERSECTIONS) {
		int i;
		for(i = list->size; i > 0; i--) {
			if(list->elt[i - 1].t < intsct.t)
				break;

			list->elt[i] = list->elt[i - 1];
		}
		list->elt[i] = intsct;

		list->size++;
	}
}

void add_intersection_list(intersection_list* list, intersection_list *sublist) {
	for(int i = 0; i < sublist->size; i++) 
		add_intersection(list, sublist->elt[i]);

}

intersection identify_hit(intersection_list list, bool* exists) {
	int i;
	for(i = 0; i < list.size; i++) 
		if(list.elt[i].t >= 0)
			break;

	if(i == list.size) {
		*exists = false;
		intersection I = {0, NULL};
		return I;
	} else {
		*exists = true;
		return list.elt[i];
	}
}
