#include <tuple.h>
#include "unit_test.h"

void basic_test() {
	new_test("TUPLE CREATION");
	tuple t;


	display("Creation of points\n");

	t = point(1, 2, 3);

	sub_test("Checking x coordinate");
	if (equal(t.x, 1)) passed(); else failed();

	sub_test("Checking y coordinate");
	if (equal(t.y, 2)) passed(); else failed();

	sub_test("Checking z coordinate");
	if (equal(t.z, 3)) passed(); else failed();

	sub_test("Checking if it is a point");
	if (is_point(t)) passed(); else failed();



	display("\nCreation of vectors\n");

	t = vector(1, 2, 3);

	sub_test("Checking x coordinate");
	if(equal(t.x, 1)) passed(); else failed();

	sub_test("Checking y coordinate");
	if(equal(t.y, 2)) passed(); else failed();

	sub_test("Checking z coordinate");
	if(equal(t.z, 3)) passed(); else failed();

	sub_test("Checking if it is a vector");
	if(is_vector(t)) passed(); else failed();


	end_test();
}


void testing_operations() {
	new_test("TUPLE OPERATIONS");

	tuple a, b, c, d;

	sub_test("Addition");
	a = point(3, -2, 5);
	b = vector(-2, 3, 1);
	c = add(a, b);
	d = point(1, 1, 6);
	if(eqv(c, d)) passed(); else failed();
	
	sub_test("Subtraction");
	a = point(3, 2, 1);
	b = point(5, 6, 7);
	c = sub(a, b);
	d = vector(-2, -4, -6);
	if(eqv(c, d)) passed(); else failed();

	sub_test("Negation");
	a = make_tuple(1, -2, 3, -4);
	c = neg(a);
	d = make_tuple(-1, 2, -3, 4);
	if(eqv(c, d)) passed(); else failed();
	

	sub_test("Scalar Multiplication");
	a = make_tuple(1, -2, 3, -4);
	c = mul(a, 3.5);
	d = make_tuple(3.5, -7, 10.5, -14);
	if(eqv(c, d)) passed(); else failed();

	sub_test("Scalar Division");
	a = make_tuple(1, -2, 3, -4);
	c = divide(a, 2);
	d = make_tuple(0.5, -1, 1.5, -2);
	if(eqv(c, d)) passed(); else failed();
	
	sub_test("Magnitude");
	a = vector(1, 0, 0);
	if(equal(magnitude(a), 1)) passed(); else failed();
	a = vector(0, 1, 0);
	if(equal(magnitude(a), 1)) passed(); else failed();
	a = vector(0, 0, 1);
	if(equal(magnitude(a), 1)) passed(); else failed();
	a = vector(1, 2, 3);
	if(equal(magnitude(a), sqrt(14))) passed(); else failed();
	a = vector(-1, -2, -3);
	if(equal(magnitude(a), sqrt(14))) passed(); else failed();



	sub_test("Normalization");

	a = vector(4, 0, 0);
	c = normalize(a);
	d = vector(1, 0, 0);
	if(eqv(c, d)) passed(); else failed();

	a = vector(1, 2, 3);
	c = normalize(a);
	d = vector(1/sqrt(14), 2/sqrt(14), 3/sqrt(14));
	if(eqv(c, d)) passed(); else failed();

	a = vector(1, 2, 3);
	c = normalize(a);
	if(equal(magnitude(c), 1)) passed(); else failed();


	sub_test("Dot Product");
	a = vector(1, 2, 3);
	b = vector(2, 3, 4);
	if(equal(dot(a, b), 20)) passed(); else failed();


	sub_test("Cross Product");
	a = vector(1, 2, 3);
	b = vector(2, 3, 4);
	c = cross(a, b);
	d = vector(-1, 2, -1);
	if(eqv(c, d)) passed(); else failed();

	end_test();

}

void testing_colors() {
	new_test("COLORS");

	tuple a, b, c, d;

	a = color(0.9, 0.6, 0.75);
	b = color(0.7, 0.1, 0.25);

	sub_test("Adding colors");
	c = add(a, b);
	d = color(1.6, 0.7, 1.0);
	if(eqv(c, d)) passed(); else failed();

	sub_test("Subtracting colors");
	c = sub(a, b);
	d = color(0.2, 0.5, 0.5);
	if(eqv(c, d)) passed(); else failed();

	sub_test("Scaling colors");
	a = color(0.2, 0.3, 0.4);
	c = mul(a, 2);
	d = color(0.4, 0.6, 0.8);
	if(eqv(c, d)) passed(); else failed();

	sub_test("Multiplying colors");
	a = color(1, 0.2, 0.4);
	b = color(0.9, 1, 0.1);
	c = hadamard(a, b);
	d = color(0.9, 0.2, 0.04);
	if(eqv(c, d)) passed(); else failed();

	end_test();
}

int main() {
	basic_test();
	testing_operations();
	testing_colors();
}
