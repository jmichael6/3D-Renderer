#include <plane.h>

shape* make_plane() {
	shape* plane = make_shape();

	plane->type = PLANE;
	return plane;
}

tuple plane_normal_at(shape* plane, tuple pt) {
	plane = plane; pt = pt;
	return vector(0, 1, 0);
}

intersection_list intersect_plane(shape* plane, ray beam) {
	intersection_list list = make_intersection_list();

	if(equal(beam.direction.y, 0))
		return list;

	float t = -beam.origin.y / beam.direction.y;
	intersection I = make_intersection(t, plane);
	add_intersection(&list, I);

	return list;
}
