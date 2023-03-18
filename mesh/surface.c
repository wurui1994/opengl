// 画二次曲面
#include <math.h>
#include <GL/glut.h>

GLfloat rtri;

// 立方体旋转角度
void display(void)
{

	// 清除颜色缓存和深度缓存
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, -2.0f, -7.0f);
	glRotatef(-70, 1.0f, 0.0f, 0.0f);
	glRotatef(rtri, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	// drawSurf(30,30);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	GLUquadric *quadratic = gluNewQuadric();
	// 绘制一个圆柱
	gluCylinder(quadratic, 1.0f, 1.0f, 4.0f, 10, 10);
	// 移动圆柱下圆面的原点,向下一个单位
	glTranslatef(0.0f, 0.0f, 2.0f);
	// 绘制一个球体
	glColor3f(0.0f, 1.0f, 0.0f);
	gluSphere(quadratic, 1.3f, 15, 15);
	// 绘制圆盘
	glColor3f(0.0f, 0.0f, 1.0f);
	gluDisk(quadratic, 0.5f, 2.0f, 6, 6);
	//
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
	glutCreateWindow("surface");
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display); // 设置空闲时用的函数
	glutMainLoop();
	return 0;
}