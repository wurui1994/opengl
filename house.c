#include <GL/glut.h>
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	//
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.5, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glEnd();
	//
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, 0.0, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(0.5, -0.75, 0.0);
	glVertex3f(-0.5, -0.75, 0.0);
	glEnd();
	//
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.0, -0.25, 0.0);
	glVertex3f(0.25, -0.25, 0.0);
	glVertex3f(0.25, -0.75, 0.0);
	glVertex3f(0.0, -0.75, 0.0);
	glEnd();
	//
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("hello");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
