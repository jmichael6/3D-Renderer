#include <matrix.h>
#include <stdio.h>

typedef struct matrix3 {
	float elt[3][3];
} matrix3;

typedef struct matrix2 {
	float elt[2][2];
} matrix2;



matrix make_matrix(float a, float b, float c, float d,
		           float e, float f, float g, float h,
				   float i, float j, float k, float l,
				   float x, float y, float z, float w) {

	matrix m;
	m.elt[0][0] = a; m.elt[0][1] = b; m.elt[0][2] = c; m.elt[0][3] = d;
	m.elt[1][0] = e; m.elt[1][1] = f; m.elt[1][2] = g; m.elt[1][3] = h;
	m.elt[2][0] = i; m.elt[2][1] = j; m.elt[2][2] = k; m.elt[2][3] = l;
	m.elt[3][0] = x; m.elt[3][1] = y; m.elt[3][2] = z; m.elt[3][3] = w;
	return m;
}

bool equal_matrices(matrix a, matrix b) {
	bool result = true;
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			if(!equal(a.elt[i][j], b.elt[i][j])) {
				result = false;
				break;
			}	
		}
	}

	return result;
}

matrix multiply(matrix a, matrix b) {
	matrix c;

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			float sum = 0;
			for(int k = 0; k < 4; k++) 
				sum += a.elt[i][k] * b.elt[k][j];
			c.elt[i][j] = sum;
		}
	}

	return c;
}

tuple apply(matrix m, tuple t) {
	float values[4];
	for(int i = 0; i < 4; i++) {
		values[i] = m.elt[i][0] * t.x + 
			        m.elt[i][1] * t.y + 
					m.elt[i][2] * t.z + 
					m.elt[i][3] * t.w;
	}

	return make_tuple(values[0], values[1], values[2], values[3]);
}

matrix transpose(matrix m) {
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < i; j++) {
			float hold = m.elt[i][j];
			m.elt[i][j] = m.elt[j][i];
			m.elt[j][i] = hold;
		}
	}
	return m;
}

float det2(matrix2 m) {
	return m.elt[0][0] * m.elt[1][1] - m.elt[0][1] * m.elt[1][0];
}

matrix2 submatrix3(matrix3 m, int a, int b) {
	matrix2 n;
	
	int x = 0;
	for(int i = 0; i < 3; i++) {
		if(i == a)
			continue;

		int y = 0;
		for(int j = 0; j < 3; j++) {
			if(j == b)
				continue;

			n.elt[x][y] = m.elt[i][j];
		
			y++;
		}
		x++;
	}
	return n;
}

float minor3(matrix3 m, int i, int j) {
	return det2(submatrix3(m, i, j));
}


float cofactor3(matrix3 m, int i, int j) {
	int sign = (i + j) % 2 == 0 ? 1 : -1;
	return sign * minor3(m, i, j);
}

float det3(matrix3 m) {
	float det = 0;
	for(int j = 0; j < 3; j++) {
		det += m.elt[0][j] * cofactor3(m, 0, j);
	}

	return det;
}


matrix3 submatrix(matrix m, int a, int b) {
	matrix3 n;
	
	int x = 0;
	for(int i = 0; i < 4; i++) {
		if(i == a)
			continue;

		int y = 0;
		for(int j = 0; j < 4; j++) {
			if(j == b)
				continue;

			n.elt[x][y] = m.elt[i][j];
		
			y++;
		}
		x++;
	}
	return n;
}

float minor(matrix m, int i, int j) {
	return det3(submatrix(m, i, j));
}

float cofactor(matrix m, int i, int j) {
	int sign = (i + j) % 2 == 0 ? 1 : -1;
	return sign * minor(m, i, j);
}

float determinant(matrix m) {
	float res = 0;
	for(int j = 0; j < 4; j++) {
		res += m.elt[0][j] * cofactor(m, 0, j);
	}
	return res;
}

matrix identity() {
	matrix m = {{{1, 0, 0, 0},
		         {0, 1, 0, 0},
				 {0, 0, 1, 0},
				 {0, 0, 0, 1}}};
	return m; 
}

matrix inverse(matrix m) {
	float d = determinant(m);

	if(d == 0) {
		return identity();
	}

	matrix inv;

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			inv.elt[i][j] = cofactor(m, j, i) / d;
		}
	}

	return inv;
}

