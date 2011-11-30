#pragma once
#include <string>
#include <vector>
using namespace std;

struct Vertex {
	float x;
	float y;
	float z;
};

struct Face {
	int f1;
	int f2;
	int f3;
};

class Model
{
private:
	int vertexCount;
	Vertex *vertexList;

	int faceCount;
	Face *faceList;

	void AddVertex(const vector<float> &vert);
public:
	Model(void);
	~Model(void);

	void Load(const string &filename);
	void OGLDraw(void);
};

