#pragma once
#include <string>
#include "OgleMath.h"
using namespace std;

struct Face {
	int verts[3];
};

class Model
{
private:
	int vertexCount;
	Vector3f *vertexList;
	Vector3f *vertexNormalList;

	int faceCount;
	Face *faceList;
public:
	Model(void);
	~Model(void);

	int GetFaceCount(void);
	int GetVertexCount(void);
	const Vector3f *GetVertexList(void);
	const Vector3f *GetVertexNormalList(void);
	const Face *GetFaceList(void);
	const float *GetTransformMatrix(void);
	void SetTransform(const float new_transform[16]);
	void SetTranslation3f(float x, float y, float z);
	void SetRotation3f(float x, float y, float z);
	float *transform;

	void Load(const string &filename);
};