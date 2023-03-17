#include <math.h>
#include <GL/glut.h>
// #include <windows.h>
#include <stdlib.h>
#include <gl2ps.h>

#define PI 3.14159f
int i, j, n = 20, k;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_SMOOTH);
	// 画网格
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

	// 画坐标轴
	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	glLineWidth(1);
	gl2psLineWidth(1.);
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
		//
		glVertex3f(0.0f, 100.0f, 0.0f);
		glVertex3f(3.0f, 93.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
		glVertex3f(-3.0f, 93.0f, 0.0f);
	}
	glEnd();

	// 标数字
	char a[4];
	glColor3f(0.0f, 0.0f, 0.0f); // 设置字体颜色
	for (i = -10; i <= 10; i++)
	{
		// itoa(i, a, 10);
		sprintf(a, "%d", i);
		puts(a);
		glRasterPos2d(i * 10 - 5, -4),
			gl2psTextOpt(a, "Courier", 12, GL2PS_TEXT_BL, 0);
		if (i < 0)
			k = -3;
		else
			k = 0;
		glRasterPos2d(-5 + k, i * 10 - 4),
			gl2psTextOpt(a, "Courier", 12, GL2PS_TEXT_BL, 0);
	}

	// 画曲线
	glLoadIdentity();
	glScalef(30, 80, 1);
	glLineWidth(1);
	gl2psLineWidth(1.);
	glColor3f(0.0f, 0.0f, 1.0f); // 指定点的颜色,绿色
	//
	GLfloat x = 0, y = 0, d = 0.0;
	glEnable(GL_LINE_STRIP);
	glLineStipple(1, 0xFFFF);
	gl2psEnable(GL2PS_LINE_STIPPLE);
	glBegin(GL_LINES);
	for (d = -PI; d <= PI; d += 0.001f)
	{
		x = d;
		y = sin(d);
		glVertex3f(x, y, 0);
	}
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	gl2psDisable(GL2PS_LINE_STIPPLE);
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

static void keyboard(unsigned char key, int x, int y)
{
	FILE *fp;
	int state = GL2PS_OVERFLOW, buffsize = 0;

	(void)x;
	(void)y; /* not used */
	switch (key)
	{
	case 'q':
		exit(0);
		break;
	case 's':
		fp = fopen("out.eps", "wb");
		printf("Writing 'out.eps'... ");
		while (state == GL2PS_OVERFLOW)
		{
			buffsize += 1024 * 1024;
			gl2psBeginPage("test", "gl2psTestSimple", NULL, GL2PS_PDF, GL2PS_SIMPLE_SORT,
						   GL2PS_DRAW_BACKGROUND | GL2PS_USE_CURRENT_VIEWPORT,
						   GL_RGBA, 0, NULL, 0, 0, 0, buffsize, fp, "out.eps");
			display();
			state = gl2psEndPage();
		}
		fclose(fp);
		printf("Done!\n");
		break;
	}
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
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 1;
}