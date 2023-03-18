#if 0
#include <windows.h>
#include <gl\gl.h>
#include <gl\glaux.h>
#include <gl\glu.h>
#endif

#include <GL/glut.h>

#if 0
void KeepTheWindowOnScreenForAWhile()
{	
	_sleep(2000);
}
#endif

void CALLBACK display(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glEnd();
	glFlush();
}

int main(int argc, char *argv[])
{
#if 0
	auxInitDisplayMode(AUX_SINGLE|AUX_RGBA);
	auxInitPosition(0,0,500,400);
	auxInitWindow("Create Your Own Program");
#endif
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(500, 500);
	glutCreateWindow("element");
	glutDisplayFunc(&display);
#if 0
	KeepTheWindowOnScreenForAWhile();
#endif
	glutMainLoop();
}
