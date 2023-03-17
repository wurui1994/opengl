#include <GL/glut.h>
//
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	glFlush();
}
//
int main()
{
	int argc = 1;
	char *argv[] = {"OpenGL  Application"};
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	int cx = glutGet(GLUT_SCREEN_WIDTH);
	int cy = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowPosition((cx - 400) / 2, (cy - 400) / 2);
	// glutInitWindowPosition(768/2,  1368/2);
	// glutInitWindowSize(600,  400);
	glutCreateWindow("OpenGL");
	glutDisplayFunc(&myDisplay);
	glutMainLoop();
	return 0;
}