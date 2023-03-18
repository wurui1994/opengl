#include <GL/glut.h>
int i, j, n = 10;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1);
	//
	glPointSize(9);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	//
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	for (i = -n / 2; i < n / 2; i++)
	{
		for (j = -n / 2; j < n / 2; j++)
		{
			glVertex2i(i, j);
			glVertex2i(i, j + 1);
			glVertex2i(i, j);
			glVertex2i(i + 1, j);
		}
	}
	glVertex2i(-n / 2, n / 2);
	glVertex2i(n / 2, n / 2);
	glVertex2i(n / 2, -n / 2);
	glVertex2i(n / 2, n / 2);
	glEnd();
	//
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 120);
	glutCreateWindow("grid");
	glutDisplayFunc(display);
	gluOrtho2D(-n, n, n, -n);
	glutMainLoop();
	return 1;
}