#include "Model.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
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
}

//static void processFaceLine(const string &line, vector<int> &face)
//{
//	face.clear();
//	int last_pos = 1;
//	int new_pos = 0;
//	string substr;
//
//	while((new_pos = line.find_first_of(' ', last_pos+1)) != string::npos) {
//		substr = line.substr(last_pos, new_pos - last_pos);
//		face.push_back(atoi(substr.c_str()));
//		last_pos = new_pos;
//	}
//	substr = line.substr(last_pos);
//	face.push_back(atoi(substr.c_str()));
//}

//static void processVertexLine(const string &line, vector<float> &vert)
//{
//	vert.clear();
//	int last_pos = 1;
//	int new_pos = 0;
//	string substr;
//
//	while((new_pos = line.find_first_of(' ', last_pos+1)) != string::npos) {
//		substr = line.substr(last_pos, new_pos - last_pos);
//		vert.push_back(atof(substr.c_str()));
//		last_pos = new_pos;
//	}
//	substr = line.substr(last_pos);
//	vert.push_back(atof(substr.c_str()));
//}

void Model::Load(const string &filename)
{
	cout << "Loading " << filename << endl;
	fstream file;
	string line;

	vertexCount = 0;
	faceCount = 0;

	int vertexIndex = 0;
	int faceIndex = 0;

	file.open(filename, ios::in);
	while(file) {
		getline(file, line);
		if (line.length() > 0) {
			switch (line[0]) {
			case 'v':
				vertexCount ++;
				break;
			case 'f':
				faceCount ++;
				break;
			};
		}
	}
	file.close();

	cout << "   Attempting to load " << vertexCount << " vertices." << endl;
	cout << "   Attempting to load " << faceCount << " faces." << endl;
	vertexList = new Vertex[vertexCount];
	Vertex temp;
	istringstream streamLine;

	file.open(filename, ios::in);
	while(file) {
		getline(file, line);
		if (line.length() > 0) {
			if (line[0] == 'v') {
				streamLine = istringstream(line[1]);
				streamLine >> temp.x >> temp.y >> temp.z;
				vertexList[vertexIndex] = temp;
				vertexIndex ++;
			}
		}
	}
	file.close();

	cout << "   Loaded " << vertexIndex << " vertices." << endl;
	cout << "   Loaded " << faceIndex << " faces." << endl;
}