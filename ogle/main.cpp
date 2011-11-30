#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <iostream>
#include "Model.h"
using namespace std;

int modelsCount = 1;
Model modelsList[] = {Model()};
float rot = 0;

static void render(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, -5.0f, -20.0f);
	glRotatef(rot, 0.0f, 1.0f, 0.0f);
	for (int i = 0; i < modelsCount; i++) {
		glPushMatrix();
		//glutWireTeapot(1.0f);
		modelsList[i].OGLDraw();
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

	//modelsList[0].Load("../bunny.obj");
	modelsList[0].Load("../dragon.obj");
	//modelsList[0].Load("../teapot2.obj");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glutMainLoop();
	return 0;
}