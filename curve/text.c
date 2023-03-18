#include <math.h>
#include <GL/glut.h>
#include <windows.h>
#include <stdlib.h>

#define MAX_CHAR 128
#define PI 3.14159f
int i, j, n = 20, k;

void selectFont(int size, int charset, const char *face)
{
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
							  charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
							  DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}

void drawString(const char *str) // ��Ļ��ʾ����
{
	static int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall)
	{
		isFirstCall = 0;
		// ����MAX_CHAR����������ʾ�б���
		lists = glGenLists(MAX_CHAR);
		// ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
	for (; *str != '\0'; ++str)
	{
		glCallList(lists + *str);
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// ������
	glLoadIdentity();
	glColor3f(0.0f, 1.0f, 0.0f);
	glLineWidth(1);
	glScalef(10, 10, 1);
	glBegin(GL_LINES);
	for (i = -n / 2; i < n / 2; i++)
	{
		for (j = -n / 2; j < n / 2; j++)
		{
			glVertex2i(i, j);
			glVertex2i(i, j + 1);
			glVertex2i(i, j);
			glVertex2i(i + 1, j);
		}
	}
	glVertex2i(-n / 2, n / 2);
	glVertex2i(n / 2, n / 2);
	glVertex2i(n / 2, -n / 2);
	glVertex2i(n / 2, n / 2);
	glEnd();

	// ��������
	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	glLineWidth(2);
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

	// ������
	char a[3];
	selectFont(14, ANSI_CHARSET, "Consolas"); // ���������ϵͳ�ļ���Ѱ��
	glColor3f(0.0f, 0.0f, 0.0f);			  // ����������ɫ
	for (i = -10; i <= 10; i++)
	{
		itoa(i, a, 10);
		glRasterPos2i(i * 10 - 5, -4), drawString(a);
		if (i < 0)
			k = -3;
		else
			k = 0;
		glRasterPos2i(-5 + k, i * 10 - 4), drawString(a);
	}

	// ������
	glLoadIdentity();
	glScalef(30, 80, 1);
	glLineWidth(1);
	glColor3f(0.0f, 0.0f, 1.0f); // ָ�������ɫ,��ɫ
	//
	GLfloat x = 0, y = 0, d = 0.0;
	glBegin(GL_LINE_STRIP);
	for (d = -PI; d <= PI; d += 0.001f)
	{
		x = d;
		y = sin(d);
		glVertex2f(x, y);
	}
	glEnd();
	//
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
	GLfloat nRange = 110.0f;
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
	glutCreateWindow("text");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 1;
}