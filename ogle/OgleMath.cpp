#include "OgleMath.h"
#include <cmath>
#include <iostream>

float magnitude(Vector3f vector)
{
	float mag = vector.x*vector.x + vector.y*vector.y + vector.z*vector.z;
	return (float)sqrt((double)mag);
}

void setIdentity(float *mat) {
	memcpy((void*)mat, (void*)identityMatrix, sizeof(float)*16);
}

float dotf(const float *a, const float *b, int order)
{
	float total = 0.0f;
	while(order--) {
		total += (a[order]*b[order]);
	}
	return total;
}

void multMatrix(const float *m1, const float *m2, float *ret)
{
	float tempCol[4];
	float tempRow[4];
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			for(int i = 0; i < 4; i++) {
				tempRow[i] = m1[(row*4) + i];
				tempCol[i] = m2[(i*4) + col];
			}
			ret[(row*4) + col] = dotf(tempRow, tempCol, 4);
		}
	}
}

void multScalarMatrix(const float &scalar, const float *matrix, float *ret)
{
	// Matrix assumed to be 4x4
	for(int i=0; i < 16; i++) {
		ret[i] = matrix[i] * scalar;
		std::cout << i << ' ' << ret[i] << std::endl;
	}
}

void multVectorMatrix(const float *vector, const float *matrix, float *ret)
{
	// Vector assumed to be first argument
	float tempCol[4];
	for(int row = 0; row < 4; row++) {
		for(int col = 0; col < 4; col++) {
			for(int i = 0; i < 4; i++) {
				tempCol[i] = matrix[(i*4) + col];
			}
			ret[(row*4) + col] = dotf(vector, tempCol, 4);
		}
	}
}

Vector3f normalize(Vector3f vector)
{
	Vector3f result;
	float mag = vector.x*vector.x + vector.y*vector.y + vector.z*vector.z;
	mag = (float)sqrt((double)mag);
	result.x = vector.x / mag;
	result.y = vector.y / mag;
	result.z = vector.z / mag;
	return result;
}

Vector3f cross(const Vector3f &vector1, const Vector3f &vector2)
{
	Vector3f result;
	result.x = (vector1.y*vector2.z) - (vector1.z*vector2.y);
	result.y = (vector1.z*vector2.x) - (vector1.x*vector2.z);
	result.z = (vector1.x*vector2.y) - (vector1.y*vector2.x);
	return result;
}

Vector3f get_normal(Vector3f a, Vector3f b, Vector3f c)
{
	Vector3f u;
	u.x = b.x - a.x;
	u.y = b.y - a.y;
	u.z = b.z - a.z;

	Vector3f v;
	v.x = c.x - a.x;
	v.y = c.y - a.y;
	v.z = c.z - a.z;

	return cross(u, v);
}
