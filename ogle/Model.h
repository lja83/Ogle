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
	float *transform;

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

	void Load(const string &filename);
};

