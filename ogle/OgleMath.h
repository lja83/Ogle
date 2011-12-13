#pragma once

struct Vector3f {
	float x;
	float y;
	float z;
};

const float identityMatrix[] = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

void setIdentity(float*);
float magnitude(Vector3f vector);
Vector3f normalize(Vector3f vector);
Vector3f cross(const Vector3f &vector1, const Vector3f &vector2);
Vector3f get_normal(Vector3f a, Vector3f b, Vector3f c);
void multMatrix(const float *m1, const float *m2, float *ret);
void multScalarMatrix(const float &scalar, const float *matrix, float *ret);
void multVectorMatrix(const float *vector, const float *matrix, float *ret);
float dotf(const float *a, const float *b, int order);