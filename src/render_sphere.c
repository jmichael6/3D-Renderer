#include <canvas.h>
#include <ray_casting.h>
#include <shape.h>
#include <stdio.h>
#include <transform.h>
#include <lighting.h>

#define HEIGHT 1000
#define WIDTH 1000

#define WALL_HEIGHT 10
#define WALL_WIDTH 10
#define WALL_DEPTH 6

tuple canvas_to_wall(float x, float y) {
	float a = (x / WIDTH) * WALL_WIDTH - (WALL_WIDTH / 2.0);
	float b = (y / HEIGHT) * WALL_HEIGHT - (WALL_HEIGHT / 2.0);
	float c = -WALL_DEPTH;
	return point(a, b, c);
}

int main() {
	//CREATING THE CANVAS
	canvas* cnv = make_canvas(WIDTH, HEIGHT);
	
	//CREATING THE SPHERE
	shape* sph = make_sphere();
	float r = 1.5;
	//sph->transform = scaling(r, r, r);
 	sph->transform = multiply(rotation_z(-PI/6), multiply(shearing(0, 0, 1, 0, 0, 0), scaling(1.5 * r, 2 * r, 1 * r)));
	sph->material.color = color(1, 0.2, 1);

	//CREATING THE LIGHT
	point_light light = make_point_light(point(-10, -10, 10), color(1, 1, 1));

	//CREATING THE POV
	tuple pov = point(0, 0, 20);

	tuple black = color(0, 0, 0);
	for(int i = 0; i < WIDTH; i++) {
		for(int j = 0; j < HEIGHT; j++) {
			tuple pixel_color;

			tuple wall_point = canvas_to_wall(i, j);
			tuple ray_dir = normalize(sub(wall_point, pov));
			ray beam = make_ray(pov, ray_dir);
			intersection_list list = intersect_object(sph, beam);

			bool exists;
			intersection hit = identify_hit(list, &exists);
			if(exists) {
				tuple pt = ray_position(beam, hit.t);
				tuple normal = normal_at(sph, pt);
				tuple eyev = neg(ray_dir);

				pixel_color = lighting_color(sph, sph->material, light, pt, eyev, normal, false);
			} else 
				pixel_color = black;

			write_pixel(cnv, i, j, pixel_color);
		}
	}

	FILE *F = fopen("sphere_img.ppm", "w");
	canvas_to_ppm(cnv, F);
	fclose(F);	

}



