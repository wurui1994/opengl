// Purpose: To show how to draw points and lines in a windows

// Author: zieckey

// Date: 2009/10/7

#include "GL/glut.h"
#include <math.h>

void RenderScene()
{
	// �����ɫ��������������ɫ�� glClearColor( 0, 0.0, 0.0, 1 ); ָ��Ϊ��ɫ

	glClear(GL_COLOR_BUFFER_BIT);

	// ����һ����

	{
		glColor3f(1.0f, 0.0f, 0.0f); // ָ�������ɫ,��ɫ

		glPointSize(9); // ָ����Ĵ�С��9�����ص�λ

		glBegin(GL_POINTS); // ��ʼ����

		{
			glVertex3f(0.0f, 0.0f, 0.0f); // ������Ϊ(0,0,0)�ĵط�������һ����
		}
		glEnd(); // ��������
	}

	// ����һ����Բ

	{
		glColor3f(0.0f, 1.0f, 0.0f); // ָ�������ɫ,��ɫ

		glPointSize(3); // ָ����Ĵ�С��3�����ص�λ

		glBegin(GL_POINTS);
		{
#define PI 3.14159f
#define RADIUS 50.f
			GLfloat x = 0, y = 0, angle = 0.0;
			for (angle = 0; angle <= 2.0f * PI; angle += 0.1f)
			{
				x = RADIUS * sin(angle);
				y = RADIUS * cos(angle);
				glVertex3f(x, y, 0);
			}
		}
		glEnd();
	}

	// ����x��y������

	{
		glColor3f(0.0f, 0.0f, 1.0f); // ָ���ߵ���ɫ,��ɫ

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
	}

	glutSwapBuffers();
}

void SetupRC()
{
	glClearColor(0, 0.0, 0.0, 1);
	glColor3f(1.0f, 0.0f, 0.0f);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat nRange = 100.0f;

	// Prevent a divide by zero

	if (h == 0)
		h = 1;

	// Set Viewport to window dimensions

	glViewport(0, 0, w, h);

	// Reset projection matrix stack

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)

	if (w <= h)
		glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w, -nRange, nRange);
	else
		glOrtho(-nRange * w / h, nRange * w / h, -nRange, nRange, -nRange, nRange);

	// Reset Model view matrix stack

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Point examples");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	SetupRC();
	glutMainLoop();

	return 1;
}