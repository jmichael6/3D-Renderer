#include <transform.h>
#include <tuple.h>
#include <unit_test.h>

void test_translation(void) {
	sub_test("Translation");

	matrix m = translation(5, -3, 2);
	tuple a = point(-3, 4, 5);
	a = apply(m, a);
	tuple b = point(2, 1, 7);
	if(eqv(a, b)) passed(); else failed();

	m = inverse(m);
	a = apply(m, a);
	b = point(-3, 4, 5);
	if(eqv(a, b)) passed(); else failed();

	m = translation(5, -3, 2);
	a = vector(-3, 4, 5);
	if(eqv(a, apply(m, a))) passed(); else failed();
}

void test_scaling() {
	sub_test("Scaling");

	matrix m;
	tuple a, b;

	m = scaling(2, 3, 4);
	a = point(-4, 6, 8);
	b = point(-8, 18, 32);
	if(eqv(apply(m, a), b)) passed(); else failed();

	m = inverse(m);
	if(eqv(apply(m, b), a)) passed(); else failed();

	m = scaling(2, 3, 4);
	a = vector(-4, 6, 8);
	b = vector(-8, 18, 32);
	if(eqv(apply(m, a), b)) passed(); else failed();

	m = scaling(-1, 1, 1);
	a = point(2, 3, 4);
	b = point(-2, 3, 4);
	if(eqv(apply(m, a), b)) passed(); else failed();
	
}

void test_rotation() {
	sub_test("Rotation");

	matrix full = rotation_x(PI/2);
	matrix half = rotation_x(PI/4);
	tuple p = point(0, 1, 0);

	if(eqv(apply(full, p), point(0, 0, 1)))
		passed();
	else 
		failed();
	if(eqv(apply(half, p), point(0, sqrt(2)/2, sqrt(2)/2)))
		passed();
	else
		failed();

	p = point(0, 0, 1);
	half = inverse(half);
	if(eqv(apply(half, p), point(0, sqrt(2)/2, sqrt(2)/2)))
		passed();
	else 
		failed();


	full = rotation_y(PI/2);
	half = rotation_y(PI/4);
	p = point(0, 0, 1);

	if(eqv(apply(full, p), point(1, 0, 0)))
		passed();
	else 
		failed();

	if(eqv(apply(half, p), point(sqrt(2)/2, 0, sqrt(2)/2)))
		passed();
	else
		failed();

	full = rotation_z(PI/2);
	half = rotation_z(PI/4);
	p = point(0, 1, 0);

	if(eqv(apply(full, p), point(-1, 0, 0)))
		passed();
	else 
		failed();
	if(eqv(apply(half, p), point(-sqrt(2)/2, sqrt(2)/2, 0)))
		passed();
	else
		failed();
}

void test_shearing() {
	sub_test("Shearing");

	matrix m = shearing(1, 0, 0, 0, 0, 0);
	tuple p = point(2, 3, 4);
	if(eqv(apply(m, p), point(5, 3, 4))) passed(); else failed();

	m = shearing(0, 1, 0, 0, 0, 0);
	if(eqv(apply(m, p), point(6, 3, 4))) passed(); else failed();

	m = shearing(0, 0, 1, 0, 0, 0);
	if(eqv(apply(m, p), point(2, 5, 4))) passed(); else failed();

	m = shearing(0, 0, 0, 1, 0, 0);
	if(eqv(apply(m, p), point(2, 7, 4))) passed(); else failed();

	m = shearing(0, 0, 0, 0, 1, 0);
	if(eqv(apply(m, p), point(2, 3, 6))) passed(); else failed();

	m = shearing(0, 0, 0, 0, 0, 1);
	if(eqv(apply(m, p), point(2, 3, 7))) passed(); else failed();
}

void test_chaining() {
	sub_test("Chaining");

	matrix a = rotation_x(PI/2);
	matrix b = scaling(5, 5, 5);
	matrix c = translation(10, 5, 7);

	matrix transforms[] = {a, b, c};
	matrix m = chain_transforms(transforms, 3);

	tuple x = point(1, 0, 1);
	
	tuple y = apply(a, x);
	y = apply(b, y);
	y = apply(c, y);

	tuple z = apply(m, x);

	if(eqv(y, z)) passed(); else failed();
}

int main() {
	new_test("TRANSFORMS");
	test_translation();
	test_scaling();
	test_rotation();
	test_shearing();
	test_chaining();
	end_test();
}
