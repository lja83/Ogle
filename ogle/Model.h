#pragma once
#include <string>
#include "OgleMath.h"
using namespace std;

struct Face {
	int vertIndex0;
	int vertIndex1;
	int vertIndex2;
	Vector3f normal;
};

class Model
{
private:
	int vertexCount;
	Vector3f *vertexList;

	int faceCount;
	Face *faceList;
public:
	Model(void);
	~Model(void);

	int GetFaceCount(void);
	int GetVertexCount(void);
	const Vector3f *GetVertexList(void);
	const Face *GetFaceList(void);

	void Load(const string &filename);
};

