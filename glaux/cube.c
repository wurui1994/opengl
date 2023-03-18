#if 0
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#endif
#include <GL/glut.h>
#include <stdio.h>
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
	glColor4f(0.2, 0.8, 1.0, 1.0); // 选颜色(R,G,B)
	glRotatef(30, 1.0, 1.0, 0.0);  // 做旋转变换
	// auxWireCube(1.0); //绘制六面体的虚线图
	glutWireCube(1.0); // 绘制六面体的虚线图
	glFlush();		   // 强制绘图，不驻留缓存
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
	glutCreateWindow("cube");
	glutDisplayFunc(&display);
	glutMainLoop();
	return 0;
}
