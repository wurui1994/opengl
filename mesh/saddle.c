// 简化
// #include <stdio.h>/
#include <math.h>
#include <GL/glut.h>
#define PI 3.1415926

GLfloat rtri;
// 球心坐标为（x，y，z），球的半径为r，M，N分别表示球体的横纵向被分成多少份
void drawSphere(GLfloat r, GLfloat M, GLfloat N)
{
	float dx = 2 / M, dy = 2 / N, x[4], y[4], z[4];
	float sx0 = -1.0, sy0 = -1.0, sx, sy, sxx, syy;
	int i = 0, j = 0, p1, p2;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	for (i = 0; i < M; i++, sx = sx0 + i * dx)
	{
		for (j = 0; j < N; j++, sy = sy0 + j * dy)
		{
			for (int k = 0; k < 4; k++)
			{
				p1 = (k == 1 || k == 2);
				p2 = (k == 2 || k == 3);
				sxx = sx + dx * p1;
				syy = sy + dy * p2;
				x[k] = r * (sxx);
				y[k] = r * (syy);
				z[k] = r * (sxx * sxx - syy * syy);
				glVertex3f(x[k], y[k], z[k]);
			}
		}
	}
	glEnd();
}
// 立方体旋转角度
void display(void)
{
	// 清除颜色缓存和深度缓存
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -7.0f);
	glRotatef(45, 1.0f, 0.0f, 0.0f);
	glRotatef(rtri, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
	drawSphere(1, 30, 30);
	glutSwapBuffers(); // 交换双缓存
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void update(int value)
{
	rtri -= 10.0f;	   // 加一个角度
	glutPostRedisplay();
	glutTimerFunc(100,update,0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	// 使用双缓存模式和深度缓存
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("saddle");
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(100,update,0);
	glutMainLoop();
	return 0;
}

#if 0
//
// #include <stdio.h>
#include <GL/glut.h>
// 球心坐标为（x，y，z），M，N分别表示球体的横纵向被分成多少份
void drawSurf(GLfloat M, GLfloat N)
{
	float step_x = 2 / M;
	float step_y = 2 / N;
	float x[4], y[4], z[4];

	float sx0 = -1.0, sx;
	float sy0 = -1.0, sy;
	int i = 0, j = 0;
	// GL_LINE模式
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	for (i = 0; i < M; i++)
	{
		sx = sx0 + i * step_x;

		for (j = 0; j < N; j++)
		{
			sy = sy0 + j * step_y;
			for (int k = 0; k < 4; k++)
			{
				x[k] = sx + step_x * (k == 1 || k == 2);
				y[k] = sy + step_y * (k == 2 || k == 3);
				z[k] = x[k] * x[k] - y[k] * y[k];
				glVertex3f(x[k], y[k], z[k]);
			}
		}
	}
	glEnd();
}
GLfloat rtri; // 立方体旋转角度
void display(void)
{
	// 清除颜色缓存和深度缓存
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -7.0f);
	glRotatef(45, 1.0f, 0.0f, 0.0f);
	glRotatef(rtri, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
	drawSurf(30, 30);
	rtri -= 0.05f;	   // 加一个角度
	glutSwapBuffers(); // 交换双缓存
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	// 使用双缓存模式和深度缓存
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("saddle");
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
#endif