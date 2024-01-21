#include <matrix.h>
#include <unit_test.h>

void test_creation() {
	sub_test("Testing creation of matrices");

	matrix m = {{{1, 2, 3, 4},
		         {5.5, 6.5, 7.5, 8.5},
				 {9, 10, 11, 12},
				 {13.5, 14.5, 15.5, 16.5}}};

	if(equal(m.elt[0][0], 1)) passed(); else failed();
	if(equal(m.elt[0][3], 4)) passed(); else failed();
	if(equal(m.elt[1][0], 5.5)) passed(); else failed();
	if(equal(m.elt[1][2], 7.5)) passed(); else failed();
	if(equal(m.elt[2][2], 11)) passed(); else failed();
	if(equal(m.elt[3][0], 13.5)) passed(); else failed();
	if(equal(m.elt[3][2], 15.5)) passed(); else failed();
}

void test_equality() {
	sub_test("Matrix equality");

	matrix a = {{{1, 2, 3, 4},
		         {5, 6, 7, 8},
				 {1, 2, 3, 4},
				 {5, 6, 7, 8}}};

	matrix b = {{{1, 2, 3, 4},
		         {5, 6, 7, 8},
				 {1, 2, 3, 4},
				 {5, 6, 7, 8}}};

	matrix c = {{{1, 2, 3, 4},
		         {5, 6, 7, 8},
				 {1, 2, 4, 4},
				 {5, 6, 7, 8}}};

	if(equal_matrices(a, b)) passed(); else failed();
	if(!equal_matrices(a, c)) passed(); else failed();

}

void test_multiply() {
	sub_test("Matrix multiplication");

	matrix a = {{{1, 2, 3, 4},
		         {5, 6, 7, 8},
				 {9, 8, 7, 6},
				 {5, 4, 3, 2}}};

    matrix b = {{{-2, 1, 2, 3},
		         {3, 2, 1, -1},
				 {4, 3, 6, 5},
				 {1, 2, 7, 8}}};

	matrix d = {{{20, 22, 50, 48},
		         {44, 54, 114, 108},
				 {40, 58, 110, 102},
				 {16, 26, 46, 42}}};


	matrix c = multiply(a, b);
	if(equal_matrices(c, d)) passed(); else failed();


	a = make_matrix(0, 1, 2, 4,
			        1, 2, 4, 8,
					2, 4, 8, 16,
					4, 8, 16, 32);

	b = make_matrix(1, 0, 0, 0, 
			        0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1);
	
	c = multiply(a, b);
	if(equal_matrices(c, a)) passed(); else failed();

	a = make_matrix(1, 2, 3, 4,
			        2, 4, 4, 2,
					8, 6, 4, 1,
					0, 0, 0, 1);
	tuple t = make_tuple(1, 2, 3, 1);
	t = apply(a, t);
	if(eqv(t, make_tuple(18, 24, 33, 1))) passed(); else failed();

	
	a = make_matrix(1, 0, 0, 0,
			        0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1);
	t = make_tuple(1, 2, 3, 4);
	t = apply(a, t);
	if(eqv(t, make_tuple(1, 2, 3, 4))) passed(); else failed();
}

void test_transpose() {
	sub_test("Matrix Transpose");

	matrix a = make_matrix(0, 9, 3, 0,
			               9, 8, 0, 8,
						   1, 8, 5, 3,
						   0, 0, 5, 8);
	matrix b = transpose(a);
	matrix c = make_matrix(0, 9, 1, 0,
			               9, 8, 8, 0,
						   3, 0, 5, 5,
						   0, 8, 3, 8);
		
	if(equal_matrices(b, c)) passed(); else failed();


	matrix id = make_matrix(1, 0, 0, 0,
			               0, 1, 0, 0,
						   0, 0, 1, 0,
						   0, 0, 0, 1);
	if(equal_matrices(id, transpose(id))) passed(); else failed();
}


void test_determinant() {
	sub_test("Determinants");

	matrix m = make_matrix(-5, 2, 6,-8,
			                1,-5, 1, 8,
							7, 7,-6,-7,
							1,-3, 7, 4);
	if(equal(determinant(m), 532)) passed(); else failed();


	m = make_matrix(6, 4, 4, 4,
			        5, 5, 7, 6,
					4, -9, 3, -7,
					9, 1, 7, -6);
	if(equal(determinant(m), -2120)) passed(); else failed();
	
	m = make_matrix(1, 0, 0, 0,
			        0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1);
	if(equal(determinant(m), 1)) passed(); else failed();

	m = make_matrix(-4, 2, -2, -3,
			         9, 6,  2,  6,
					 0, -5, 1, -5,
					 0,  0, 0,  0);
	if(equal(determinant(m), 0)) passed(); else failed();
}

void test_inverse() {
	sub_test("Inverses");

	matrix a = make_matrix(-5, 2, 6, -8,
			                1, -5, 1, 8,
							7, 7, -6, -7,
							1, -3, 7, 4);

	matrix b = make_matrix( \
	   0.21805,  0.45113,  0.24060,  -0.04511,
	  -0.80827, -1.45677, -0.44361,   0.52068,
	  -0.07895, -0.22368, -0.05263,   0.19737,
	  -0.52256, -0.81391, -0.30075,   0.30639);

	if(equal_matrices(inverse(a), b)) passed(); else failed();


	a = make_matrix(
			  8, -5,  9,  2,
			  7,  5,  6,  1,
			 -6,  0,  9,  6,
			 -3,  0, -9, -4);
	b = make_matrix(
			 -0.15385, -0.15385, -0.28205, -0.53846,
             -0.07692,  0.12308,  0.02564,  0.03077,
              0.35897,  0.35897,  0.43590,  0.92308,
             -0.69231, -0.69231, -0.76923, -1.92308);
	if(equal_matrices(inverse(a), b)) passed(); else failed();


	a = make_matrix(
			9, 3, 0, 9,
			-5, -2, -6, -3,
			-4, 9, 6, 4,
			-7, 6, 6, 2);
	b = make_matrix(
           -0.04074, -0.07778,  0.14444, -0.22222,
           -0.07778,  0.03333,  0.36667, -0.33333,
           -0.02901, -0.14630, -0.10926,  0.12963,
            0.17778,  0.06667, -0.26667,  0.33333);
	if(equal_matrices(inverse(a), b)) passed(); else failed();
	

	a = make_matrix(
			3, -9, 7,  3,
			3, -8, 2, -9,
		   -4,  4, 4,  1,
		   -6,  5, -1, 1);
	b = make_matrix(
			8, 2, 2, 2,
			3, -1, 7, 0,
			7, 0, 5, 4,
			6, -2, 0, 5);

	matrix c = multiply(multiply(a, b), inverse(b));
	if(equal_matrices(c, a)) passed(); else failed();
}


int main() {
	new_test("MATRICES");
	test_creation();
	test_equality();
	test_multiply();
	test_transpose();
	test_determinant();
	test_inverse();
	end_test();
}
