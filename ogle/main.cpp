#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <iostream>
#include "Model.h"
#include "OgleMath.h"
#include "OgleMatrix.h"
using namespace std;

int modelsCount = 0;
Model *modelsList;
float rot = 0;

float cameraMatrix[16] = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

static void draw_normal(Vector3f vertex, Vector3f normal)
{
	float normalLen = .2;

	normal.x *= normalLen;
	normal.y *= normalLen;
	normal.z *= normalLen;

	normal.x += vertex.x;
	normal.y += vertex.y;
	normal.z += vertex.z;

	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);

	glVertex3f(vertex.x, vertex.y, vertex.z);
	glVertex3f(normal.x, normal.y, normal.z);

	glEnd();
	glEnable(GL_LIGHTING);
}

static void render(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float light_pos[4] = {0, 0, 1, 0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	const Vector3f *verts = NULL;
	const Vector3f *vertNormals = NULL;
	const Face *faces = NULL;
	int vertIndex;
	//float tempMatrix[16];

	bool DRAW_NORMALS = FALSE;

	//multScalarMatrix(-1.0f, cameraMatrix, tempMatrix);
	//glMultMatrixf(tempMatrix);

	for (int i = 0; i < modelsCount; i++) {
		glPushMatrix();
		// Set model's matrix
		glMultMatrixf(modelsList[i].GetTransform().GetRawMatrix());
		verts = modelsList[i].GetVertexList();
		vertNormals = modelsList[i].GetVertexNormalList();
		faces = modelsList[i].GetFaceList();
		for(int face = 0; face < modelsList[i].GetFaceCount(); face ++) {
			glBegin(GL_TRIANGLES);
			for(int j = 0; j < 3; j ++) {
				vertIndex = faces[face].verts[j];
				glNormal3f(vertNormals[vertIndex].x, vertNormals[vertIndex].y, vertNormals[vertIndex].z);
				//glNormal3f(faces[face].normal.x, faces[face].normal.y, faces[face].normal.z);
				glVertex3f(verts[vertIndex].x, verts[vertIndex].y, verts[vertIndex].z);
			}
			glEnd();
		}
		if (DRAW_NORMALS) {
			for(int j = 0; j < modelsList[i].GetVertexCount(); j++) {
				draw_normal(verts[j], vertNormals[j]);
			}
		}
		glPopMatrix();
	}
	glutSwapBuffers();
}

static void idle(void)
{
	rot += 1;
	//rot = fmod(rot, 360);
	float thisRot = rot * (3.1415926 / 180.0f);
	modelsList[0].SetRotation3f(0.0f, thisRot, 0.0f);
	modelsList[1].SetRotation3f(thisRot, 0.0f, 0.0f);
	modelsList[2].SetRotation3f(0.0f, 0.0f, thisRot);
	glutPostRedisplay();
}

static void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char **argv)
{
	HWND hWnd = GetConsoleWindow();
	//ShowWindow(hWnd, SW_HIDE);

	int width = 800;
	int height = 600;

	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Ogle");
	glutDisplayFunc(&render);
	glutIdleFunc(&idle);
	glutReshapeFunc(&reshape);

	modelsCount = 3;
	modelsList = new Model[modelsCount];
	//modelsList[0].Load("../bunny.obj");
	modelsList[0].Load("../teapot2.obj");
	modelsList[1].Load("../teapot2.obj");
	modelsList[2].Load("../teapot2.obj");
	//modelsList[1].Load("../dragon.obj");

	modelsList[0].SetTranslation3f(-4.0f, -5.0f, -20.0f);
	modelsList[1].SetTranslation3f(4.0f, -4.0f, -20.0f);
	modelsList[2].SetTranslation3f(0.0f, 3.0f, -20.0f);
	//modelsList[1].SetTranslation3f(0.0f, 0.0f, -10.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	OgleMatrix a(4, 4);
	a.SetIdentity();

	glutMainLoop();
	return 0;
}