#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <iostream>
#include "Model.h"
#include "OgleMath.h"
using namespace std;

int modelsCount = 0;
Model *modelsList;
float rot = 0;

static void render(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, -5.0f, -20.0f);
	glRotatef(rot, 0.0f, 1.0f, 0.0f);

	const Vector3f *verts = NULL;
	const Face *faces = NULL;

	for (int i = 0; i < modelsCount; i++) {
		glPushMatrix();
		verts = modelsList[i].GetVertexList();
		faces = modelsList[i].GetFaceList();
		for(int face = 0; face < modelsList[i].GetFaceCount(); face ++) {
			glBegin(GL_TRIANGLES);
			glNormal3f(faces[face].normal.x, faces[face].normal.y, faces[face].normal.z);
			glVertex3f(verts[faces[face].vertIndex0].x, verts[faces[face].vertIndex0].y, verts[faces[face].vertIndex0].z);
			glVertex3f(verts[faces[face].vertIndex1].x, verts[faces[face].vertIndex1].y, verts[faces[face].vertIndex1].z);
			glVertex3f(verts[faces[face].vertIndex2].x, verts[faces[face].vertIndex2].y, verts[faces[face].vertIndex2].z);
			glVertex3f(verts[faces[face].vertIndex0].x, verts[faces[face].vertIndex0].y, verts[faces[face].vertIndex0].z);
			glEnd();
		}
		glPopMatrix();
	}

	glutSwapBuffers();
}

static void idle(void)
{
	rot += 1;
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

	modelsCount = 2;
	modelsList = new Model[modelsCount];
	modelsList[0].Load("../bunny.obj");
	modelsList[1].Load("../dragon.obj");
	//modelsList[1].Load("../teapot2.obj");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glutMainLoop();
	return 0;
}