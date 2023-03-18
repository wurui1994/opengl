// 二次简化
// #include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#define PI 3.1415926
GLfloat rtri;
// 球心坐标为（x，y，z），球的半径为r，M，N分别表示球体的横纵向被分成多少份
void drawSphere(GLfloat r, GLfloat M, GLfloat N)
{
	float dx = PI / M, dy = 2 * PI / N;
	float x[4], y[4], z[4];
	float sx = 0.0, sy = 0.0;
	int i = 0, j = 0, p1, p2;
	glBegin(GL_LINE_LOOP);
	for (i = 0; i < M; i++, sx = i * dx)
	{
		for (j = 0; j < N; j++, sy = j * dy)
		{
			for (int k = 0; k < 4; k++)
			{
				p1 = (k == 1 || k == 2);
				p2 = (k == 2 || k == 3);
				// sx=sx + dx*p1;sy=sy + dy*p2;
				x[k] = r * sin(sx + dx * p1) * cos(sy + dy * p2);
				y[k] = r * sin(sx + dx * p1) * sin(sy + dy * p2);
				z[k] = r * cos(sx + dx * p1);
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
	glRotatef(rtri, 0.0f, 1.0f, 1.0f);
	glPointSize(4);
	glColor3f(0.0f, 1.0f, 1.0f);
	drawSphere(2, 30, 30);
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
	glutCreateWindow("sphere");
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display); // 设置空闲时用的函数
	glutMainLoop();
	return 0;
}

#if 0
// 简化版
// #include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#define PI 3.1415926
// 球心坐标为（x，y，z），球的半径为radius，M，N分别表示球体的横纵向被分成多少份
void drawSphere(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat radius, GLfloat M, GLfloat N)
{
	float step_x = PI / M;
	float step_y = 2 * PI / N;
	float x[4], y[4], z[4];

	float sx = 0.0;
	float sy = 0.0;
	int i = 0, j = 0;
	glBegin(GL_LINE_LOOP);
	for (i = 0; i < M; i++)
	{
		sx = i * step_x;
		for (j = 0; j < N; j++)
		{
			sy = j * step_y;
			for (int k = 0; k < 4; k++)
			{
				x[k] = radius * sin(sx + step_x * (k == 1 || k == 2)) * cos(sy + step_y * (k == 2 || k == 3));
				y[k] = radius * sin(sx + step_x * (k == 1 || k == 2)) * sin(sy + step_y * (k == 2 || k == 3));
				z[k] = radius * cos(sx + step_x * (k == 1 || k == 2));
				glVertex3f(xx + x[k], yy + y[k], zz + z[k]);
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
	glRotatef(rtri, 0.0f, 1.0f, 1.0f);
	glPointSize(4);
	glColor3f(0.0f, 1.0f, 1.0f);
	drawSphere(0, 0, 0, 2, 30, 30);
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
	glutCreateWindow("sphere");
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display); // 设置空闲时用的函数
	glutMainLoop();
	return 0;
}
#endif

#if 0
// 原版
/////////////////////////////////////////////////////

// #include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#define PI 3.1415926
// 球心坐标为（x，y，z），球的半径为radius，M，N分别表示球体的横纵向被分成多少份
void drawSphere(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat radius, GLfloat M, GLfloat N)
{
	float step_z = PI / M;
	float step_xy = 2 * PI / N;
	float x[4], y[4], z[4];

	float angle_z = 0.0;
	float angle_xy = 0.0;
	int i = 0, j = 0;
	glBegin(GL_LINE_LOOP);
	for (i = 0; i < M; i++)
	{
		angle_z = i * step_z;

		for (j = 0; j < N; j++)
		{
			angle_xy = j * step_xy;

			x[0] = radius * sin(angle_z) * cos(angle_xy);
			y[0] = radius * sin(angle_z) * sin(angle_xy);
			z[0] = radius * cos(angle_z);

			x[1] = radius * sin(angle_z + step_z) * cos(angle_xy);
			y[1] = radius * sin(angle_z + step_z) * sin(angle_xy);
			z[1] = radius * cos(angle_z + step_z);

			x[2] = radius * sin(angle_z + step_z) * cos(angle_xy + step_xy);
			y[2] = radius * sin(angle_z + step_z) * sin(angle_xy + step_xy);
			z[2] = radius * cos(angle_z + step_z);

			x[3] = radius * sin(angle_z) * cos(angle_xy + step_xy);
			y[3] = radius * sin(angle_z) * sin(angle_xy + step_xy);
			z[3] = radius * cos(angle_z);

			for (int k = 0; k < 4; k++)
			{
				glVertex3f(xx + x[k], yy + y[k], zz + z[k]);
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
	glRotatef(rtri, 0.0f, 1.0f, 1.0f);
	glPointSize(4);
	glColor3f(0.0f, 1.0f, 1.0f);
	drawSphere(0, 0, 0, 2, 30, 30);
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
	glutCreateWindow("sphere");
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display); // 设置空闲时用的函数
	glutMainLoop();
	return 0;
}
#endif