#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>

static void render(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
}

static void idle(void)
{
}


int main(int argc, char **argv)
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	int width = 800;
	int height = 600;

	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Ogle");
	glutDisplayFunc(&render);
	glutIdleFunc(&idle);

	glutMainLoop();
	return 0;
}