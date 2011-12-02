#pragma once

struct Vector3f {
	float x;
	float y;
	float z;
};

typedef float Matrix[16];
const Matrix identityMatrix = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

void setIdentity(Matrix);
float magnitude(Vector3f vector);
Vector3f normalize(Vector3f vector);
Vector3f cross(const Vector3f &vector1, const Vector3f &vector2);
Vector3f get_normal(Vector3f a, Vector3f b, Vector3f c);
void multMatrix(Matrix m1, Matrix m2, Matrix ret);
float dotf(float *a, float *b, int order);