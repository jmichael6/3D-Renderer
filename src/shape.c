#include <shape.h>
#include <ray_casting.h>
#include <stdio.h>
#include <stdlib.h>

material_properties make_material() {
	material_properties m;
	m.color = color(1, 1, 1);
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200;
	return m;
}

shape* make_shape() {
	shape* object = malloc(sizeof(shape));
	
	object->properties = NULL;
	object->transform = identity();
	object->material = make_material();
	object->has_pattern = false;
	object->pattern = make_pattern();

	return object;
}

void set_pattern(shape* object, general_pattern pattern) {
	object->has_pattern = true;
	object->pattern = pattern;
}

tuple normal_at(shape* object, tuple world_pt) {
	tuple object_pt = apply(inverse(object->transform), world_pt);

	tuple object_normal;
	if(object->type == SPHERE)
		object_normal = sphere_normal_at(object, object_pt);
	else if (object->type == PLANE) 
		object_normal = plane_normal_at(object, object_pt);
	else {
		printf("ERROR: Shape of unknown type");
		exit(0);
	}

	tuple world_normal = apply(transpose(inverse(object->transform)), object_normal);
	world_normal.w = 0;
	world_normal = normalize(world_normal);

	return world_normal;
}


intersection_list intersect_object(shape* object, ray beam) {
	beam = transform_ray(inverse(object->transform), beam);

	if(object->type == SPHERE)
		return intersect_sphere(object, beam);
	else if(object->type == PLANE)
		return intersect_plane(object, beam);
	else {
		printf("ERROR: Shape of unknown type");
		exit(0);
	}

	return make_intersection_list();
}
