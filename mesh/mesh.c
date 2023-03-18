#include <math.h>
#include <GL/glut.h>
#define PI 3.1415926
GLfloat rtri;
// 自定义函数
float fun(float x, float y)
{
	return x * x - y * y;
}

// M，N分别表示球体的横纵向被分成多少份
void drawSurf(GLfloat M, GLfloat N)
{
	float dx = 2 / M, dy = 2 / N, x[4], y[4], z[4];
	float sx0 = -1.0, sy0 = -1.0, sx, sy, sxx, syy, szz;
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
				szz = fun(sxx, syy);
				glVertex3f(sxx, syy, szz);
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
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("mesh");
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display); // 设置空闲时用的函数
	glutMainLoop();
	return 0;
}