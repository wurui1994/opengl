#if 0
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#endif
#include <stdio.h>
#include <GL/glut.h>

void myinit(void);
void CALLBACK myReshape(int w, int h);
void CALLBACK display(void);

void myinit(void) // 初始化
{
	glClearColor(0.0, 0.0, 0.0, 0.0); // 将窗口清为黑色
}
void CALLBACK display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	// 将颜色缓存清为glClearColor命令所设置的颜色，即背景色
	glColor4f(1.0, 1.0, 1.0, 1.0); // 选颜色(R,G,B)
	glPointSize(6.0);			   // 设置点的大小
	glBegin(GL_POINTS);			   // 在屏幕上绘制三个点
	glVertex3f(0.1, 0.2, 0.0);
	glVertex3f(0.2, 0.7, 0.0);
	glVertex3f(0.5, 0.8, 0.0);
	glEnd();
	glBegin(GL_LINES); // 在屏幕上绘制一条线段
	glVertex2f(0.0, 0.4);
	glVertex2f(-0.3, 0.8);
	glEnd();
	glBegin(GL_POLYGON); // 在屏幕上绘制一个四边形
	glVertex2f(-0.6, 0.0);
	glVertex2f(-0.4, 0.0);
	glVertex2f(-0.4, 0.3);
	glVertex2f(-0.6, 0.4);
	glEnd();
	glColor3f(1.0, 0.0, 0.0);	 // 设置当前颜色为红色
	glColor3f(0.0, 0.0, 1.0);	 // 设置当前颜色为蓝色
	glRectf(0.5, 0.5, 0.7, 0.7); // 绘制一个矩形
	glColor3f(0.0, 1.0, 0.0);	 // 设置当前颜色为绿色
	glRectf(0.8, 0.8, 0.9, 0.9); // 绘制一个矩形
	glRectf(0.2, 0.2, 0.4, 0.4); // 绘制一个矩形
	glFlush();					 // 强制绘图，不驻留缓存
}

void CALLBACK myReshape(int w, int h) // 用于窗口大小改变时的处理，与绘图无关
{
	glViewport(0, 0, w, h);
}

#if 0
void main(void)
{
	auxInitDisplayMode(AUX_SINGLE|AUX_RGBA); //窗口显示单缓存和RGB(彩色)模式
	auxInitPosition(0,0,200,200); //大小 x=200  y=200   (0,0)是屏幕左上点
	auxInitWindow("openglsample.c");  //初始化窗口，参数是标题
	myinit();
	auxReshapeFunc(myReshape);
	auxMainLoop(display);
}
#endif
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(500, 500);
	glutCreateWindow("element");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(&display);
	glutMainLoop();
	return 0;
}