#include <world.h>
#include <ray_casting.h>
#include <unit_test.h>
#include <transform.h>

void test_default_world() {
	sub_test("Intersections and shading in the world");

	world *wld = make_default_world();
	ray r = make_ray(point(0, 0, -5), vector(0, 0, 1));
	intersection_list xs = intersect_world(wld, r);
	
	if(xs.size == 4 &&
	   xs.elt[0].t == 4 &&
	   xs.elt[1].t == 4.5 &&
	   xs.elt[2].t == 5.5 &&
	   xs.elt[3].t == 6)
		passed();
	else
		failed();


	r = make_ray(point(0, 0, -5), vector(0, 0, 1));
	shape* sph = make_sphere();
	intersection I = make_intersection(4, sph);
	intersection_state state = prepare_computations(I, r);
	if(state.t == 4 &&
	   state.object == sph &&
	   eqv(state.pt, point(0, 0, -1)) &&
	   eqv(state.eyev, vector(0, 0, -1)) &&
	   eqv(state.normalv, vector(0, 0, -1)) &&
	   state.inside == false)
		passed();
	else
		failed();

	r = make_ray(point(0, 0, 0), vector(0, 0, 1));
	I = make_intersection(1, sph);
	state = prepare_computations(I, r);
	if(eqv(state.pt, point(0, 0, 1))  &&
       eqv(state.eyev, vector(0, 0, -1)) &&
	   state.inside == true  &&
	   eqv(state.normalv, vector(0, 0, -1)) )
		passed();
	else
		failed();

	r = make_ray(point(0, 0, -5), vector(0, 0, 1));
	tuple c = color_at(wld, r);
	if(eqv(c, color(0.38066, 0.47583, 0.28549)))
		passed();
	else
		failed();

	r = make_ray(point(0, 0, -5), vector(0, 1, 0));
	c = color_at(wld, r);
	if(eqv(c, color(0, 0, 0)))
		passed();
	else
		failed();


	r = make_ray(point(0, 0, 0.75), vector(0, 0, -1));
	c = color_at(wld, r);
	if(eqv(c, color(0.1, 0.1, 0.1)))
		passed();
	else
		failed();


	wld = make_world();
	set_light(wld, make_point_light(point(0, 0.25, 0), color(1, 1, 1)));
	r = make_ray(point(0, 0, 0), vector(0, 0, 1));

	sph = make_sphere();
	sph->transform = scaling(0.5, 0.5, 0.5);
	add_object(wld, sph);
	
	c = color_at(wld, r);
	if(eqv(c, color(0.90498, 0.90498, 0.90498)))
		passed();
	else
		failed();
}


void test_camera() {
	sub_test("Testing the camera mapping");
	
	camera* cam = make_camera(201, 101, PI/2);
	ray r = ray_for_pixel(cam, 100, 50);
	if(eqv(r.origin, point(0, 0, 0)) &&
	   eqv(r.direction, vector(0, 0, -1)))
		passed();
	else
		failed();

	r = ray_for_pixel(cam, 0, 0);
	if(eqv(r.origin, point(0, 0, 0)) &&
	   eqv(r.direction, vector(0.66519, 0.33259, -0.66851)))
		passed();
	else
		failed();

	cam->transform = multiply(rotation_y(PI/4), translation(0, -2, 5));
	r = ray_for_pixel(cam, 100, 50);
	if(eqv(r.origin, point(0, 2, -5)) &&
	  eqv(r.direction, vector(sqrt(2)/2, 0, -sqrt(2)/2)))
		passed();
	else
		failed();


}


int main() {
	new_test("WORLDS AND SCENES");
	test_default_world();
	test_camera();
	end_test();
}
