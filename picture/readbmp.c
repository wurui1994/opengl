#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>

#define FileName "test.bmp"
static GLint imagewidth;
static GLint imageheight;
static GLint pixellength;
static GLubyte *pixeldata;

void display(void)
{
	// glClear(GL_COLOR_BUFFER_BIT);

	// 绘制像素
	glDrawPixels(imagewidth, imageheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata);

	//---------------------------------
	glFlush();
	glutSwapBuffers();
}

void readBMP(const char* file)
{
	puts(file);
	// 打开文件
	FILE *pfile = fopen(file, "rb");
	if (pfile == 0)
		exit(0);

	// 读取图像大小
	fseek(pfile, 0x0012, SEEK_SET);
	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
	fread(&imageheight, sizeof(imageheight), 1, pfile);

	// 计算像素数据长度
	pixellength = imagewidth * 3;
	while (pixellength % 4 != 0)
		pixellength++;
	pixellength *= abs(imageheight);

	// 读取像素数据
	pixeldata = (GLubyte *)malloc(pixellength);
	if (pixeldata == 0)
	{
		perror("pixeldata");
		printf("pixellength=%d imagewidth=%d imageheight=%d\n", 
			pixellength, imagewidth, imageheight);
		exit(0);
	}

	fseek(pfile, 54, SEEK_SET);
	fread(pixeldata, pixellength, 1, pfile);

	// 关闭文件
	fclose(pfile);
}

int main(int argc, char *argv[])
{
	readBMP(argv[1]);
	// 初始化glut运行
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	// glutInitWindowPosition(100,100);
	glutInitWindowSize(imagewidth, imageheight);
	glutCreateWindow(FileName);
	glutDisplayFunc(&display);
	glutMainLoop();
	//-------------------------------------
	free(pixeldata);
	return 0;
}
