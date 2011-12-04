#include "Model.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "OgleMath.h"
using namespace std;

Model::Model(void)
{
	vertexCount = 0;
	vertexList = NULL;

	vertexNormalList = NULL;

	faceCount = 0;
	faceList = NULL;

	//setIdentity(transform);
}

Model::~Model(void)
{
	delete[] vertexList;
	vertexList = NULL;
	vertexCount = 0;

	delete[] vertexNormalList;
	vertexNormalList = NULL;

	delete[] faceList;
	faceList = NULL;
	faceCount = 0;
}

const Vector3f *Model::GetVertexList(void)
{
	return vertexList;
}

const Vector3f *Model::GetVertexNormalList(void)
{
	return vertexNormalList;
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
	vertexNormalList = new Vector3f[vertexCount];
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
				streamLine >> tempFace.verts[0] >> tempFace.verts[1] >> tempFace.verts[2];
				tempFace.verts[0] --;
				tempFace.verts[1] --;
				tempFace.verts[2] --;
				faceList[faceIndex] = tempFace;
				faceIndex ++;
			}
		}
	}
	file.close();

	cout << "   Loaded " << vertexIndex << " vertices." << endl;
	cout << "   Loaded " << faceIndex << " faces." << endl;

	// Calculate normals
	temp.x = 0;
	temp.y = 0;
	temp.z = 0;
	for (int i = 0; i < vertexCount; i ++) {
		vertexNormalList[i] = temp;
	}

	int vertIndex[3];
	cout << "   Calculating " << faceIndex << " normals." << endl;
	// For each vertex on each face, calculate the vertex's normal based on the new face.
	// If a previous normal has been calculated, average this one with the old one without normalizing.
	for (int i = 0; i < faceCount; i ++) {
		vertIndex[0] = faceList[i].verts[0];
		vertIndex[1] = faceList[i].verts[1];
		vertIndex[2] = faceList[i].verts[2];
		temp = get_normal(vertexList[vertIndex[0]], vertexList[vertIndex[1]], vertexList[vertIndex[2]]);
		temp = normalize(temp);
		for (int j = 0; j < 3; j++) {
			vertexNormalList[vertIndex[j]].x = (temp.x + vertexNormalList[vertIndex[j]].x);
			vertexNormalList[vertIndex[j]].y = (temp.y + vertexNormalList[vertIndex[j]].y);
			vertexNormalList[vertIndex[j]].z = (temp.z + vertexNormalList[vertIndex[j]].z);
		}
	}
	// normalize all vertex normals
	for (int i = 0; i < vertexCount; i ++) {
		vertexNormalList[i] = normalize(vertexNormalList[i]);
	}
	cout << "   Done" << endl;
}