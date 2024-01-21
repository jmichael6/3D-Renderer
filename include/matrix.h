#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <tuple.h>

typedef struct matrix {
	float elt[4][4];
} matrix;

matrix make_matrix(float, float, float, float,
		           float, float, float, float,
				   float, float, float, float,
				   float, float, float, float);

bool equal_matrices(matrix a, matrix b);

matrix multiply(matrix a, matrix b);
tuple apply(matrix m, tuple t);
matrix transpose(matrix m);
float determinant(matrix m);
matrix inverse(matrix m);

matrix identity();

#endif
