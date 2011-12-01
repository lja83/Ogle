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

Vertex normalize(Vertex vector)
{
	Vertex result;
	float mag = vector.x*vector.x + vector.y*vector.y + vector.z*vector.z;
	mag = (float)sqrt((double)mag);
	result.x = vector.x / mag;
	result.y = vector.y / mag;
	result.z = vector.z / mag;
	return result;
}

Vertex cross(const Vertex &vector1, const Vertex &vector2)
{
	Vertex result;
	result.x = (vector1.y*vector2.z) - (vector1.z*vector2.y);
	result.y = (vector1.x*vector2.z) - (vector1.z*vector2.x);
	result.z = (vector1.x*vector2.y) - (vector1.y*vector2.x);
	return result;
}

Vertex get_normal(Vertex a, Vertex b, Vertex c)
{
	Vertex u;
	u.x = b.x - a.x;
	u.y = b.y - a.y;
	u.z = b.z - a.z;

	Vertex v;
	v.x = c.x - a.x;
	v.y = c.y - a.y;
	v.z = c.z - a.z;

	return normalize(cross(u, v));
}

void Model::OGLDraw(void)
{
	for(int face = 0; face < faceCount; face ++) {
		glBegin(GL_TRIANGLES);
		Vertex normal = get_normal(vertexList[faceList[face].f1], vertexList[faceList[face].f2], vertexList[faceList[face].f3]);
		glNormal3f(normal.x, normal.y, normal.z);
		glVertex3f(vertexList[faceList[face].f1].x, vertexList[faceList[face].f1].y, vertexList[faceList[face].f1].z);
		glVertex3f(vertexList[faceList[face].f2].x, vertexList[faceList[face].f2].y, vertexList[faceList[face].f2].z);
		glVertex3f(vertexList[faceList[face].f3].x, vertexList[faceList[face].f3].y, vertexList[faceList[face].f3].z);
		glVertex3f(vertexList[faceList[face].f1].x, vertexList[faceList[face].f1].y, vertexList[faceList[face].f1].z);
		glEnd();
	}
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

	Vertex temp;
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
	vertexList = new Vertex[vertexCount];
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
				streamLine >> tempFace.f1 >> tempFace.f2 >> tempFace.f3;
				tempFace.f1 --;
				tempFace.f2 --;
				tempFace.f3 --;
				faceList[faceIndex] = tempFace;
				faceIndex ++;
			}
		}
	}
	file.close();

	cout << "   Loaded " << vertexIndex << " vertices." << endl;
	cout << "   Loaded " << faceIndex << " faces." << endl;
}