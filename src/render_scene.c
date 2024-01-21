#include <world.h>
#include <transform.h>

int main() {
	world *wld = make_world();

	//FLOOR
	shape* floor = make_plane();
	floor->material.color = color(1, 0.9, 0.9);
	floor->material.specular = 0;

	//set_pattern(floor, make_stripe_pattern(color(1, 0.9, 0.9), color(0, 0, 0)));
	add_object(wld, floor);

	//LEFT_WALL
	shape* left_wall = make_plane();
	left_wall->transform = multiply( translation(0, 0, 5), 
									 multiply(rotation_y(-PI/4), rotation_x(PI/2)));
	left_wall->material = floor->material;
	add_object(wld, left_wall);


	//RIGHT_WALL
	shape* right_wall = make_plane();
	right_wall->transform = multiply(translation(0, 0, 5), 
									 multiply(rotation_y(PI/4), rotation_x(PI/2)));
	right_wall->material = floor->material;
	add_object(wld, right_wall);

	//MIDDLE_shape
	shape* middle = make_sphere();
	middle->transform = translation(-0.8, 1, 0.8);
	middle->material.color = color(0.1, 1, 0.5);
	middle->material.diffuse = 0.7;
	middle->material.specular = 0.3;
	//middle->material.reflective = 0.2;
	add_object(wld, middle);

	//RIGHT_shape
	shape* right = make_sphere();
	right->transform = multiply(translation(-0.5, 0.2, -1.0), scaling(0.2, 0.2, 0.2));
	right->material.color = color(0.5, 1, 0.1);
	right->material.diffuse = 0.7;
	right->material.specular = 0.3;
	add_object(wld, right);


	//LEFT_shape
	shape* left = make_sphere();
	left->transform = multiply(translation(0.2, 0.33, -0.75), scaling(0.33, 0.33, 0.33));
	left->material.color = color(1, 0.8, 0.1);
	left->material.diffuse = 0.7;
	left->material.specular = 0.3;
	add_object(wld, left);

	point_light light_source = make_point_light(point(-10, 10, -10), color(1, 1, 1));
	set_light(wld, light_source);

	camera *cam = make_camera(600, 400, PI/2.5);
	cam->transform = view_transformation(point(0, 1.5, -5),
			                             point(0, 1, 0),
										 vector(0, 1, 0));

	FILE *F = fopen("scene_img.pph", "w");
	canvas_to_ppm(render(cam, wld), F);
	fclose(F);
}
