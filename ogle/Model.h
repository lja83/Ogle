#pragma once
#include <string>
#include "OgleMath.h"
#include "OgleMatrix.h"
using namespace std;

struct Vertex {
	Vector3f normal;
	Vector3f vert;
};

//struct Face {
//	int a, b, c;
//	//Vector3f normal;
//};

class Model
{
private:
	int vertexCount;
	Vertex *vertexList;
	float *vertexNormalList;

	int faceCount;
	int *faceList;

	OgleMatrix transform;
public:
	Model(void);
	~Model(void);

	int GetFaceCount(void) { return faceCount; }
	int GetVertexCount(void) { return vertexCount; };
	const Vertex *GetVertexList(void) { return vertexList; };
	//const Vector3f *GetVertexNormalList(void) { return vertexNormalList; };
	const int *GetFaceList(void) { return faceList; };
	OgleMatrix GetTransform(void) { return transform; };

	void SetTransform(const float new_transform[16]);
	void SetTranslation3f(float x, float y, float z);
	void SetRotation3f(float x, float y, float z);

	void Load(const string &filename);
};