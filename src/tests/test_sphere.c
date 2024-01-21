#include <shape.h>
#include <unit_test.h>
#include <transform.h>

void test_normal() {
		sub_test("Checking if normals are correctly computed");

		shape *sph = make_sphere();
		tuple t;

		t = vector(1, 0, 0);
		if(eqv(t, normal_at(sph, point(1, 0, 0)))) passed(); else failed();

		t = vector(0, 1, 0);
		if(eqv(t, normal_at(sph, point(0, 1, 0)))) passed(); else failed();

		t = vector(0, 0, 1);
		if(eqv(t, normal_at(sph, point(0, 0, 1)))) passed(); else failed();

		float x = sqrt(3)/3;
		t = vector(x, x, x);
		if(eqv(t, normal_at(sph, point(x, x, x)))) passed(); else failed();
		
		t = normal_at(sph, point(x, x, x));
		if(eqv(t, normalize(t))) passed(); else failed();

		sph->transform = translation(0, 1, 0);
		tuple a = point(0, 1.70711, -0.70711);
		t = vector(0, 0.70711, -0.70711);
		if(eqv(t, normal_at(sph, a))) passed(); else failed();

		sph->transform = multiply(scaling(1, 0.5, 1), rotation_z(PI/5.0));
		a = point(0, sqrt(2)/2, -sqrt(2)/2);
		t = vector(0, 0.97014, -0.24254);
		if(eqv(t, normal_at(sph, a))) passed(); else failed();
}

int main() {
	new_test("SPHERE");
	test_normal();
	end_test();
}
