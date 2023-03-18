#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gl/glut.h>
#include <SOIL/SOIL.h>

char name[20];

int Bind(char name[])
{
	GLuint id;
	id = SOIL_load_OGL_texture(name,
							   SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glBindTexture(GL_TEXTURE_2D, id);
	return id;
}

void Position(float a, float b, float c, float d)
{
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(a, d);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(a, c);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(b, c);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(b, d);
	glEnd();
}

void display(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//
	Position(0, 1, 1, 0);
	// glDeleteTextures(1, &idd);

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	strcpy(name, argv[1]);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(300, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("");
	Bind(name);
	glutDisplayFunc(&display);
	glEnable(GL_TEXTURE_2D);
	glutMainLoop();
	return 0;
}