#include <math.h>
#include <GL/glut.h>

#define PI 3.14159f

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 1.0f);
	glLineWidth(3);
	glBegin(GL_LINES);
	{
		// x-axis
		glVertex3f(-100.0f, 0.0f, 0.0f);
		glVertex3f(100.0f, 0.0f, 0.0f);
		// x-axis arrow
		glVertex3f(100.0f, 0.0f, 0.0f);
		glVertex3f(93.0f, 3.0f, 0.0f);
		glVertex3f(100.0f, 0.0f, 0.0f);
		glVertex3f(93.0f, -3.0f, 0.0f);
		// y-axis
		glVertex3f(0.0f, -100.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
		glVertex3f(3.0f, 93.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
		glVertex3f(-3.0f, 93.0f, 0.0f);
	}
	glEnd();
	// 绘制一个点圆
	glScalef(30, 80, 1);
	glLineWidth(1);
	glColor3f(0.0f, 1.0f, 0.0f); // 指定点的颜色,绿色
	//
	GLfloat x = 0, y = 0, d = 0.0;
	glBegin(GL_LINE_STRIP);
	for (d = -PI; d <= PI; d += 0.01f)
	{
		x = d;
		y = sin(d);
		glVertex2f(x, y);
	}
	glEnd();
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
	GLfloat nRange = 100.0f;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//
	if (w <= h)
		gluOrtho2D(-nRange, nRange, -nRange * h / w, nRange * h / w);
	else
		gluOrtho2D(-nRange * w / h, nRange * w / h, -nRange, nRange);
	//
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(350, 120);
	glutCreateWindow("Draw Curve");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 1;
}