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

	float *transform;
public:
	Model(void);
	~Model(void);

	int GetFaceCount(void) { return faceCount; }
	int GetVertexCount(void) { return vertexCount; };
	const Vector3f *GetVertexList(void) { return vertexList; };
	const Vector3f *GetVertexNormalList(void) { return vertexNormalList; };
	const Face *GetFaceList(void) { return faceList; };
	const float *GetTransform(void) { return transform; };

	void SetTransform(const float new_transform[16]);
	void SetTranslation3f(float x, float y, float z);
	void SetRotation3f(float x, float y, float z);

	void Load(const string &filename);
};