#ifndef __WORLD_H__
#define __WORLD_H__

#include <shape.h>
#include <lighting.h>
#include <canvas.h>

typedef struct object_list_node {
	shape* object;
	struct object_list_node* next;
} object_list_node;

typedef struct object_list {
	struct object_list_node* head;
} object_list;


typedef struct world {
	object_list objects;
	point_light light_source;
} world;

typedef struct intersection_state {
	shape* object;
	float t;
	tuple pt;
	tuple over_pt;
	tuple eyev;
	tuple normalv;
	bool inside;
} intersection_state;

typedef struct camera {
	int hsize;
	int vsize;
	float field_of_view;
	matrix transform;
	float aspect;
	float half_width;
	float half_height;
	float pixel_size;
} camera;

//Modify intersection

world* make_world();
void add_object(world* wld, shape* object);
void set_light(world* wld, point_light light);
world* make_default_world();

camera* make_camera(int hsize, int vsize, float field_of_view);
matrix view_transformation(tuple from, tuple to, tuple up);
canvas* render(camera* cam, world* wld);


intersection_list intersect_world(world* wld, ray beam);
intersection_state prepare_computations(intersection I, ray beam);
tuple shade_hit(world* wld, intersection_state state);
tuple color_at(world* wld, ray beam);
ray ray_for_pixel(camera* cam, int px, int py);
#endif
