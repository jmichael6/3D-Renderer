#include <world.h>
#include <stdlib.h>
#include <ray_casting.h>
#include <transform.h>
#include <canvas.h>
#include <stdio.h>

#define OVER_EPS 0.01

object_list_node*  make_object_list_node(shape *object) {
	object_list_node* node = malloc(sizeof(object_list_node));
	node->object = object;
	node->next = NULL;
	return node;
}


object_list make_object_list() {
	object_list list;
	list.head = NULL;
	return list;
}


world* make_world() {
	world* wld = malloc(sizeof(world));
	wld->objects = make_object_list();
	wld->light_source = make_point_light(point(0, 0, 0), color(0, 0, 0));
	return wld;
}

void add_object(world* wld, shape* object) {
	object_list_node* node = make_object_list_node(object);
	node->next = wld->objects.head;

	wld->objects.head = node;
}

void set_light(world* wld, point_light light) {
	wld->light_source = light;
}

world* make_default_world() {
	world* wld = make_world();


	shape* sph1 = make_sphere();
	sph1->material.color = color(0.8, 1.0, 0.6);
	sph1->material.diffuse = 0.7;
	sph1->material.specular = 0.2;

	shape* sph2 = make_sphere();
	sph2->transform = scaling(0.5, 0.5, 0.5);
	
	point_light light = make_point_light(point(-10, 10, -10), color(1, 1, 1));

	add_object(wld, sph1);
	add_object(wld, sph2);
	set_light(wld, light);

	return wld;
}

intersection_list intersect_world(world* wld, ray beam) {
	intersection_list all_found = make_intersection_list();

	object_list_node* node = wld->objects.head;
	while(node != NULL) {
		intersection_list list = intersect_object(node->object, beam);
		add_intersection_list(&all_found, &list);
		
		node = node->next;
	}

	return all_found;
}


intersection_state prepare_computations(intersection I, ray beam) {
	intersection_state S;

	S.object = I.object;

	S.t = I.t;
	S.pt = ray_position(beam, S.t);
	S.eyev = neg(normalize(beam.direction));	
	S.normalv = normal_at(S.object, S.pt);
	
	if(dot(S.normalv, S.eyev) < 0) {
		S.inside = true;
		S.normalv = neg(S.normalv);
	} else
		S.inside = false;

	S.over_pt = add(S.pt, mul(S.normalv, OVER_EPS));
	
	return S;
}


bool is_shadowed(world* wld, tuple pt) {
	tuple lightv = sub(wld->light_source.position, pt);
	float distance = magnitude(lightv);
	tuple dir = normalize(lightv);

	ray r = make_ray(pt, dir);
	intersection_list shadowers = intersect_world(wld, r);
	
	bool exists;
	intersection hit = identify_hit(shadowers, &exists);

	if(exists == true && hit.t < distance)
		return true;
	else
		return false;
}

tuple shade_hit(world* wld, intersection_state state) {
	return lighting_color(state.object,
						  state.object->material,
						  wld->light_source,
				          state.over_pt,
					      state.eyev,
				          state.normalv,
						  is_shadowed(wld, state.over_pt));
}


tuple color_at(world* wld, ray beam) {
	intersection_list matches = intersect_world(wld, beam);

	bool exists;
	intersection hit = identify_hit(matches, &exists);

	if(!exists)  {
		return color(0, 0, 0);
	} else {
		intersection_state state = prepare_computations(hit, beam);
		return shade_hit(wld, state);
	}
}


matrix view_transformation(tuple from, tuple to, tuple up) {
	tuple forward = normalize(sub(to, from));
	up = normalize(up);
	tuple left = cross(forward, up);
	tuple true_up = cross(left, forward);	

	matrix view_transform = make_matrix(
			left.x,      left.y,     left.z,    0,
			true_up.x,   true_up.y,  true_up.z, 0,
			-forward.x, -forward.y, -forward.z, 0,
			0,           0,          0,         1);

	view_transform = multiply(view_transform, translation(-from.x, -from.y, -from.z));
	return view_transform;
}


camera* make_camera(int hsize, int vsize, float field_of_view) {
	camera* cam = malloc(sizeof(camera));
	cam->hsize = hsize;
	cam->vsize = vsize;
	cam->field_of_view = field_of_view;
	cam->transform = identity();
	cam->aspect = (hsize * 1.0) / vsize;

	float half_view = tan(field_of_view / 2);
	 
	if(cam->aspect >= 1) {
		cam->half_width = half_view;
		cam->half_height = half_view / cam->aspect;
	} else {
		cam->half_height = half_view;
		cam->half_width = half_view * cam->aspect;
	}

	cam->pixel_size = (2 * cam->half_width) / hsize;

	return cam;
}

ray ray_for_pixel(camera* cam, int px, int py) {
	float xoffset = (px + 0.5) * cam->pixel_size;
	float yoffset = (py + 0.5) * cam->pixel_size;

	float world_x = -(xoffset - cam->half_width);
	float world_y = -(yoffset - cam->half_height);

	tuple pixel = apply(inverse(cam->transform), point(world_x, world_y, -1));
	tuple origin = apply(inverse(cam->transform), point(0, 0, 0));
	tuple direction = normalize(sub(pixel, origin));

	return make_ray(origin, direction);
}


canvas* render(camera* cam, world* wld) {
	canvas* image = make_canvas(cam->hsize, cam->vsize);

	for(int x = 0; x < cam->hsize; x++) {
		for(int y = 0; y < cam->vsize; y++) {
			ray beam = ray_for_pixel(cam, x, y);
			write_pixel(image, x, y, color_at(wld, beam));
		}
	}

	return image;
}
