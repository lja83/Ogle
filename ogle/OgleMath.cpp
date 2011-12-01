#include "OgleMath.h"
#include <cmath>
#include <iostream>

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
	result.y = (vector1.x*vector2.z) - (vector1.z*vector2.x);
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

	return normalize(cross(u, v));
}