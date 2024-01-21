#include <lighting.h>
#include <unit_test.h>

void test_reflection() {
	sub_test("Checking the reflection function");

	tuple v = vector(1, -1, 0);
	tuple n = vector(0, 1, 0);
	if(eqv(find_reflection(v, n), vector(1, 1, 0))) passed(); else failed();

	v = vector(0, -1, 0);
	n = vector(sqrt(2)/2, sqrt(2)/2, 0);
	if(eqv(find_reflection(v, n), vector(1, 0, 0))) passed(); else failed();
}

void test_point_lights() {
	sub_test("Checking creation of point lights");

	tuple intensity = color(1, 1, 1);
	tuple position = point(0, 0, 0);
	point_light light = make_point_light(position, intensity);
	if(eqv(light.position, position) &&
	   eqv(light.intensity, intensity))
		passed();
	else
		failed();
}

void test_material() {
	sub_test("Checking creation of materials");

	material_properties m = make_material();
	if(eqv(m.color, color(1, 1, 1)) &&
	   equal(m.ambient, 0.1) &&
	   equal(m.diffuse, 0.9) &&
	   equal(m.specular, 0.9) &&
	   equal(m.shininess, 200))
		passed();
	else
		failed();

	shape* sphere = make_sphere();
	m = sphere->material;
	if(eqv(m.color, color(1, 1, 1)) &&
	   equal(m.ambient, 0.1) &&
	   equal(m.diffuse, 0.9) &&
	   equal(m.specular, 0.9) &&
	   equal(m.shininess, 200))
		passed();
	else
		failed();
}

void test_lighting() {
	sub_test("Checking if shading behaves normally");

	material_properties m = make_material();
	shape* object = make_shape();
	tuple position = point(0, 0, 0);

	point_light light = make_point_light(point(0, 0, -10), color(1, 1, 1));
	tuple eyev = vector(0, 0, -1);
	tuple normal = vector(0, 0, -1);
	tuple result = lighting_color(object, m, light, position, eyev, normal, false);
	if(eqv(result, color(1.9, 1.9, 1.9))) passed(); else failed();

	eyev = vector(0, sqrt(2)/2, -sqrt(2)/2);
	result = lighting_color(object, m, light, position, eyev, normal, false);
	if(eqv(result, color(1.0, 1.0, 1.0))) passed(); else failed();

	eyev = vector(0, 0, -1);
	light.position = point(0, 10, -10);
	result = lighting_color(object, m, light, position, eyev, normal, false);
	if(eqv(result, color(0.7364, 0.7364, 0.7364))) passed(); else failed();

	eyev = vector(0, -sqrt(2)/2, -sqrt(2)/2);
	result = lighting_color(object, m, light, position, eyev, normal, false);
	if(eqv(result, color(1.6364, 1.6364, 1.6364))) passed(); else failed();

	eyev = vector(0, 0, -1);
	light.position = vector(0, 0, 10);
	result = lighting_color(object, m, light, position, eyev, normal, false);
	if(eqv(result, color(0.1, 0.1, 0.1))) passed(); else failed();
}

int main() {
	new_test("LIGHTING AND SHADING");
	test_reflection();
	test_point_lights();
	test_material();
	test_lighting();
	end_test();
}
