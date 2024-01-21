#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include <matrix.h>
#define PI M_PI

matrix translation(float x, float y, float z);
matrix scaling(float x, float y, float z);
matrix rotation_x(float a);
matrix rotation_y(float a);
matrix rotation_z(float a);
matrix shearing(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y);

matrix chain_transforms(matrix transforms[], int n);

#endif
