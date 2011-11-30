#pragma once
#include <string>
#include <vector>
using namespace std;

struct Vertex {
	float x;
	float y;
	float z;
};

class Model
{
private:
	int vertexCount;
	Vertex *vertexList;

	int faceCount;
	int **faceList;

	void AddVertex(const vector<float> &vert);
public:
	Model(void);
	~Model(void);

	void Load(const string &filename);
};

