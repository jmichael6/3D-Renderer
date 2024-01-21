#include <tuple.h>
#include <stdio.h>

float absl(float x) {
	if(x > 0)
		return x;
	else
		return -x;
}

bool equal(float x, float y) {
	if(absl(x - y) < EPS)
		return true;
	else 
		return false;
}

tuple make_tuple(float x, float y, float z, float w) {
	tuple t = {x, y, z, w};
	return t;
}

tuple point(float x, float y, float z) {
	return make_tuple(x, y, z, 1);
}

tuple vector(float x, float y, float z) {
	return make_tuple(x, y, z, 0);
}

tuple color(float r, float g, float b) {
	return make_tuple(r, g, b, 0);
}


bool is_point(tuple t) {
	return equal(t.w, 1);
}

bool is_vector(tuple t) {
	return equal(t.w, 0);
}

bool eqv(tuple t1, tuple t2) {
	if(equal(t1.x, t2.x) && equal(t1.y, t2.y) && equal(t1.z, t2.z) && equal(t1.w, t2.w))
		return true;
	else
		return false;
}


tuple add(tuple a, tuple b) {
	return make_tuple(a.x + b.x, 
			          a.y + b.y,
					  a.z + b.z,
					  a.w + b.w);
}


tuple sub(tuple a, tuple b) {
	return make_tuple(a.x - b.x,
			          a.y - b.y,
					  a.z - b.z,
					  a.w - b.w);
}

tuple neg(tuple a) {
	return make_tuple(-a.x, -a.y, -a.z, -a.w);
}

tuple mul(tuple a, float f) {
	return make_tuple(a.x * f,
			          a.y * f,
					  a.z * f,
					  a.w * f);
}


tuple divide(tuple a, float f) {
	if(f == 0) {
		printf("Tuple-division: Division by zero");
		return make_tuple(0, 0, 0, 0);
	} else
		return mul(a, (1/f));
}

float magnitude(tuple a) {
	return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
}

tuple normalize(tuple a) {
	float mag = magnitude(a);

	if(mag == 0) {
		printf("Tuple-Normalize: Division by zero");
		return make_tuple(0, 0, 0, 0);
	} else
		return divide(a, mag);
}

float dot(tuple a, tuple b) {
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

tuple cross(tuple a, tuple b) {
	return vector(  a.y * b.z - b.y * a.z,
	     	      - a.x * b.z + b.x * a.z,
	   	            a.x * b.y - b.x * a.y);
}

tuple hadamard(tuple a, tuple b) {
	return color(a.x * b.x,
			     a.y * b.y,
			     a.z * b.z);
} 
