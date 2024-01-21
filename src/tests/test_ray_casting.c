#include <unit_test.h>
#include <ray_casting.h>
#include <sphere.h>
#include <transform.h>

void test_ray_creation() {
	sub_test("Creating rays");

	ray beam = make_ray(point(1, 2, 3), vector(4, 5, 6));

	if(eqv(beam.origin, point(1, 2, 3))) passed(); else failed();
	if(eqv(beam.direction, vector(4, 5, 6))) passed(); else failed();	
}


void test_ray_position() {
	sub_test("Finding positions along a ray");

	ray beam = make_ray(point(2, 3, 4), vector(1, 0, 0));

	if(eqv(ray_position(beam, 0), point(2, 3, 4))) passed(); else failed();
	if(eqv(ray_position(beam, 1), point(3, 3, 4))) passed(); else failed();
	if(eqv(ray_position(beam, -1), point(1, 3, 4))) passed(); else failed();
	if(eqv(ray_position(beam, 2.5), point(4.5, 3, 4))) passed(); else failed();
}

void test_intersection() {
	sub_test("Testing the intersection data structure");

	shape* sph = make_sphere();
	float t = 1;

	intersection intsct = make_intersection(t, sph);
	if(equal(t, intsct.t) && (sph == intsct.object))
		passed();
	else
		failed();

	intersection i1, i2, i3, i4, hit;

	i1 = make_intersection(1, sph);
	i2 = make_intersection(2, sph);
	intersection_list list = make_intersection_list();
	add_intersection(&list, i1);
	add_intersection(&list, i2);

	if(list.size == 2 &&
	   equal_intersection(i1, list.elt[0]) &&
	   equal_intersection(i2, list.elt[1]))
		passed();
	else
		failed();
	   
	clear_intersection_list(&list);
	i1 = make_intersection(1, sph);
	i2 = make_intersection(2, sph);
	add_intersection(&list, i1);
	add_intersection(&list, i2);
	bool exists;
	hit = identify_hit(list, &exists);
	if(exists && equal_intersection(i1, hit)) passed(); else failed();

	clear_intersection_list(&list);
	i1 = make_intersection(-1, sph);
	i2 = make_intersection(1, sph);
	add_intersection(&list, i1);
	add_intersection(&list, i2);
	hit = identify_hit(list, &exists);
	if(exists && equal_intersection(i2, hit)) passed(); else failed();

	clear_intersection_list(&list);
	i1 = make_intersection(-2, sph);
	i2 = make_intersection(-1, sph);
	add_intersection(&list, i1);
	add_intersection(&list, i2);
	hit = identify_hit(list, &exists);
	if(!exists) passed(); else failed();

	clear_intersection_list(&list);
	i1 = make_intersection(5, sph);
	i2 = make_intersection(7, sph);
	i3 = make_intersection(-3, sph);
	i4 = make_intersection(2, sph);
	add_intersection(&list, i1);
	add_intersection(&list, i2);
	add_intersection(&list, i3);
	add_intersection(&list, i4);
    hit = identify_hit(list, &exists);
	if(exists && equal_intersection(i4, hit)) passed(); else failed();

    clear_intersection_list(&list);
	intersection_list sublist = make_intersection_list();
	add_intersection(&list, i1);
	add_intersection(&list, i2);
	add_intersection(&sublist, i3);
	add_intersection(&sublist, i4);
	add_intersection_list(&list, &sublist);

	if(list.size == 4 &&
	   equal_intersection(list.elt[0], i3) &&
	   equal_intersection(list.elt[1], i4) &&
	   equal_intersection(list.elt[2], i1) &&
	   equal_intersection(list.elt[3], i2))
		passed();
	else 
		failed();
}

void test_sphere_intersection() {
	sub_test("Testing the intercept values for spheres");

	intersection_list list;
	shape* sph = make_sphere();

	ray beam = make_ray(point(0, 0, -5), vector(0, 0, 1));
	list = intersect_object(sph, beam);
	if(list.size == 2 &&
	   equal(list.elt[0].t, 4) &&
	   equal(list.elt[1].t, 6))
		passed();
	else
		failed();


	beam = make_ray(point(0, 1, -5), vector(0, 0, 1));
	list = intersect_object(sph, beam);
	if(list.size == 2 &&
	   equal(list.elt[0].t, 5) &&
	   equal(list.elt[1].t, 5))
		passed();
	else
		failed();

	beam = make_ray(point(0, 2, -5), vector(0, 0, 1));
	list = intersect_object(sph, beam);
	if(list.size == 0)
		passed();
	else
		failed();

	beam = make_ray(point(0, 0, 0), vector(0, 0, 1));
	list = intersect_object(sph, beam);
	if(list.size == 2 &&
	   equal(list.elt[0].t, -1) &&
	   equal(list.elt[1].t, 1))
		passed();
	else
		failed();

	beam = make_ray(point(0, 0, 5), vector(0, 0, 1));
	list = intersect_object(sph, beam);
	if(list.size == 2 &&
	   equal(list.elt[0].t, -6) &&
	   equal(list.elt[1].t, -4))
		passed();
	else
		failed();

}

void test_sphere_transform() {
	sub_test("Testing sphere transformations");
	
	shape* sph;
	sph = make_sphere();
	if(equal_matrices(sph->transform, identity()))
		passed();
	else
		failed();

	sph->transform = translation(2, 3, 4);
	if(equal_matrices(sph->transform, translation(2, 3, 4)))
		passed();
	else
		failed();

	ray beam = make_ray(point(0, 0, -5), vector(0, 0, 1));
	sph->transform = scaling(2, 2, 2);
	intersection_list list = intersect_object(sph, beam);
	if(list.size == 2 &&
	   list.elt[0].t == 3 &&
	   list.elt[1].t == 7)
		passed();
	else
		failed();

	beam = make_ray(point(0, 0, -5), vector(0, 0, 1));
	sph->transform = translation(0, 0, 5);
	list = intersect_object(sph, beam);
	if(list.size == 2 &&
	   list.elt[0].t == 9 &&
	   list.elt[1].t == 11)
		passed();
	else
		failed();

}

int main() {
	test_ray_creation();
	test_ray_position();
	test_intersection();
	test_sphere_intersection();
	test_sphere_transform();
}



