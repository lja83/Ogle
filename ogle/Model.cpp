#include "Model.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <cmath>

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
using namespace std;

Model::Model(void)
{
	vertexCount = 0;
	vertexList = NULL;

	faceCount = 0;
	faceList = NULL;
}

Model::~Model(void)
{
	delete[] vertexList;
	vertexList = NULL;
	vertexCount = 0;

	delete[] faceList;
	faceList = NULL;
	faceCount = 0;
}

const Vector3f *Model::GetVertexList(void)
{
	return vertexList;
}

const Face *Model::GetFaceList(void)
{
	return faceList;
}

int Model::GetFaceCount(void)
{
	return faceCount;
}

int Model::GetVertexCount(void)
{
	return vertexCount;
}

void Model::Load(const string &filename)
{
	cout << "Loading " << filename << endl;
	fstream file;
	string line;
	istringstream streamLine;
	string buf;

	vertexCount = 0;
	faceCount = 0;

	int vertexIndex = 0;
	int faceIndex = 0;

	Vector3f temp;
	Face tempFace;

	file.open(filename, ios::in);
	// Run through file once to figure out how many verts and faces exist
	while(file) {
		getline(file, line);
		if (line.length() > 0) {
			streamLine = istringstream(line);
			streamLine >> buf;
			if (buf == "vt") {
			} else if (buf == "v") {
				vertexCount ++;
			} else if (buf == "f") {
				faceCount ++;
			};
		}
	}
	// clear and rewind file stream
	file.clear();
	file.seekg(0);
	
	cout << "   Attempting to load " << vertexCount << " vertices." << endl;
	cout << "   Attempting to load " << faceCount << " faces." << endl;

	// Allocate memory for vertices and faces
	vertexList = new Vector3f[vertexCount];
	faceList = new Face[faceCount];

	// Run through file again to load vertex and face data
	while(file) {
		getline(file, line);
		if (line.length() > 0) {
			streamLine = istringstream(line);
			streamLine >> buf;
			if (buf == "v") {
				streamLine >> temp.x >> temp.y >> temp.z;
				vertexList[vertexIndex] = temp;
				vertexIndex ++;
			}else if (buf == "f") {
				streamLine >> tempFace.vertIndex0 >> tempFace.vertIndex1 >> tempFace.vertIndex2;
				tempFace.vertIndex0 --;
				tempFace.vertIndex1 --;
				tempFace.vertIndex2 --;
				faceList[faceIndex] = tempFace;
				faceIndex ++;
			}
		}
	}
	file.close();

	cout << "   Loaded " << vertexIndex << " vertices." << endl;
	cout << "   Loaded " << faceIndex << " faces." << endl;

	// Calculate normals
	cout << "   Calculating " << faceIndex << " normals." << endl;
	for (int i = 0; i < faceCount; i ++) {
		temp = get_normal(vertexList[faceList[i].vertIndex0], vertexList[faceList[i].vertIndex1], vertexList[faceList[i].vertIndex2]);
		faceList[i].normal = temp;
	}
	cout << "   Done" << endl;
}