#include <GL/glut.h>
//
void RenderScene()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(9);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	{
		glVertex3f(0.0f, 0.0f, 0.0f);
	}
	glEnd(); //
	glutSwapBuffers();
}
//
void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat nRange = 200.0f;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w, -nRange, nRange);
	else
		glOrtho(-nRange * w / h, nRange * w / h, -nRange, nRange, -nRange, nRange);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(200, 200);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Point examples");
	glutDisplayFunc(RenderScene);
	glClearColor(0.0f, 0.0f, 0.0f, 1);
	glutMainLoop();
	return 0;
}