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
// 初始化
void myinit(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // 将窗口清为黑色
    glShadeModel(GL_FLAT);            // 常量明暗处理方式
}

void CALLBACK display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    // 将颜色缓存清为glClearColor命令所设置的颜色，即背景色
    glColor3f(1.0, 1.0, 1.0);     // 选当前颜色(R,G,B)为白色
    glLoadIdentity();             // 设置当前矩阵为单位矩阵
    glTranslatef(0.0, 0.0, -3.0); // 平移变换
    glRotatef(45, 1.0, 1.0, 0.0); // 旋转变换
    glScalef(1.0, 2.0, 1.0);      // 缩放变换
    // auxWireCube(1.0);    //绘制立方体
    glutWireCube(1.0); // 绘制立方体
    glFlush();         // 强制绘图，不驻留缓存
}
void CALLBACK myReshape(int w, int h) // 用于窗口改变大小时的处理，与绘图无关
{
    glMatrixMode(GL_PROJECTION);                              // 指明当前矩阵操作是针对投影矩阵进行的
    glLoadIdentity();                                         // 设置当前矩阵为单位矩阵
    gluPerspective(70.0, (GLfloat)w / (GLfloat)h, 1.5, 40.0); // 投影变换
    glMatrixMode(GL_MODELVIEW);                               // 返回视点-模型矩阵
    glViewport(0, 0, w, h);                                   // 定义视口变换
}

#if 0
void main(void)
{
    auxInitDisplayMode(AUX_SINGLE|AUX_RGBA);
    //窗口显示单缓存和RGB(彩色)模式
    auxInitPosition(0,0,200,200); //大小 x=200、y=200 ， (0,0)是屏幕左上点
    auxInitWindow("Perspective 3-D Cubes");   //初始化窗口，参数是标题
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
    glutCreateWindow("transform");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(&display);
    glutMainLoop();
    return 0;
}
