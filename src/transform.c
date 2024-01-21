#include <transform.h>

matrix translation(float x, float y, float z) {
	return make_matrix(
			1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1);
}


matrix scaling(float x, float y, float z) {
	return make_matrix(
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1);
}

matrix rotation_x(float a) {
	return make_matrix(
			1, 0,       0,      0,
			0, cos(a), -sin(a), 0,
			0, sin(a),  cos(a), 0,
			0, 0,       0,      1);
}

matrix rotation_y(float a) {
	return make_matrix(
			cos(a),  0, sin(a), 0,
			0,       1, 0,      0,
			-sin(a), 0, cos(a), 0,
			0,       0, 0,      1);
}

matrix rotation_z(float a) {
	return make_matrix(
			cos(a), -sin(a), 0, 0,
			sin(a),  cos(a), 0, 0,
			0,       0,      1, 0,
			0,       0,      0, 1);
}


matrix shearing(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y){
	return make_matrix(
			1,   x_y, x_z, 0,
			y_x, 1,   y_z, 0,
			z_x, z_y, 1,   0,
			0,   0,   0,   1);
}

matrix chain_transforms(matrix transforms[], int n) {
	matrix m = identity();

	for(int i = 0; i < n; i++) 
		m = multiply(transforms[i], m);

	return m;
}

