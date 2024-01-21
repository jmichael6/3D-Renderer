#include <sphere.h>
#include <ray_casting.h>
#include <stdlib.h>
#include <stdio.h>
#include <transform.h>

shape* make_sphere() {
	shape* sphere = make_shape();
	sphere->type = SPHERE;

	return sphere;
}

tuple sphere_normal_at(shape* sphere, tuple object_pt) {
	sphere = sphere;
	return sub(object_pt, point(0, 0, 0));
}


intersection_list intersect_sphere(shape* sphere, ray beam) {
	tuple sphere_to_ray = sub(beam.origin, point(0, 0, 0));

	float a = dot(beam.direction, beam.direction);
	float b = 2 * dot(sphere_to_ray, beam.direction);
	float c = dot(sphere_to_ray, sphere_to_ray) - 1;
	float D = b * b - 4 * a * c;

	intersection_list list = make_intersection_list();
	if(D >= 0) {
		float t1 = (-b + sqrt(D)) / (2 * a);
		float t2 = (-b - sqrt(D)) / (2 * a);

		intersection i1 = make_intersection(t1, sphere);
		intersection i2 = make_intersection(t2, sphere);

		add_intersection(&list, i1);
		add_intersection(&list, i2);
	}	
	return list;
}
