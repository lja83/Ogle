#pragma once

struct Vector3f {
	float x;
	float y;
	float z;
};

Vector3f normalize(Vector3f vector);
Vector3f cross(const Vector3f &vector1, const Vector3f &vector2);
Vector3f get_normal(Vector3f a, Vector3f b, Vector3f c);

