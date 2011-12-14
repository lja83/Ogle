#include "Model.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "OgleMath.h"
#include "OgleMatrix.h"
using namespace std;

Model::Model(void)
{
	vertexCount = 0;
	vertexList = NULL;

	vertexNormalList = NULL;

	faceCount = 0;
	faceList = NULL;

	transform.SetIdentity();
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

void Model::SetTransform(const float new_transform[16])
{
	transform.SetMatrix(new_transform);
}

void Model::SetTranslation3f(float x, float y, float z)
{
	transform.Set(3, 0, x);
	transform.Set(3, 1, y);
	transform.Set(3, 2, z);
}

void Model::SetRotation3f(float x, float y, float z)
{
	OgleMatrix tempMatrix(4, 4);
	OgleMatrix tempMatrix2(4, 4);

	float xMat[] = {
		1, 0, 0, 0,
		0, cos(x), sin(x), 0,
		0, -sin(x), cos(x), 0,
		0, 0, 0, 1
	};
	OgleMatrix xRot(4, 4);
	xRot.SetMatrix(xMat);

	float yMat[] = {
		cos(y), 0, -sin(y), 0,
		0, 1, 0, 0,
		sin(y), 0, cos(y), 0,
		0, 0, 0, 1
	};
	OgleMatrix yRot(4, 4);
	yRot.SetMatrix(yMat);

	float zMat[] = {
		cos(z), sin(z), 0, 0,
		-sin(z), cos(z), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	OgleMatrix zRot(4, 4);
	zRot.SetMatrix(zMat);

	tempMatrix = xRot.MultMatrix(yRot);
	tempMatrix = tempMatrix.MultMatrix(zRot);

	// Don't change translation when rotation changes.
	// Need a better way to do this...
	tempMatrix.Set(3, 0, transform.GetRawMatrix()[12 + 0]);
	tempMatrix.Set(3, 1, transform.GetRawMatrix()[12 + 1]);
	tempMatrix.Set(3, 2, transform.GetRawMatrix()[12 + 2]);
	transform = tempMatrix;

	//cout.precision(4);
	//for(int r = 0; r < 4; r++) {
	//	for(int c = 0; c < 4; c++) {
	//		cout << transform[(r*4) + c];
	//		cout << ", ";
	//	}
	//	cout << endl;
	//}
	//cout << endl << endl;
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
		for (int j = 0; j < 3; j++) {
			vertexNormalList[vertIndex[j]].x = (temp.x + vertexNormalList[vertIndex[j]].x);
			vertexNormalList[vertIndex[j]].y = (temp.y + vertexNormalList[vertIndex[j]].y);
			vertexNormalList[vertIndex[j]].z = (temp.z + vertexNormalList[vertIndex[j]].z);
		}
		temp = normalize(temp);
		faceList[i].normal = temp;
	}
	// normalize all vertex normals
	for (int i = 0; i < vertexCount; i ++) {
		vertexNormalList[i] = normalize(vertexNormalList[i]);
	}

	int face = 201;
	int faceVertex = faceList[face].verts[0];
	for(int i = 0; i < faceCount; i ++) {
		if((faceList[i].verts[0] == faceVertex) ||
			(faceList[i].verts[1] == faceVertex) ||
			(faceList[i].verts[2] == faceVertex)) {
				cout << i << endl;
		}
	}

	// fix normals(face)
	//   compare face to adjacent faces
	//   for each adjacent face
	//     if normal inverted
	//       invert adjacent face normal
	//     fix normals(adjacent face)
	cout << "   Done" << endl;
}