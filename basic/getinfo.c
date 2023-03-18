#include <GL/glut.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutCreateWindow("info");
    const GLubyte *VENDOR, *RENDERER, *VERSION, *EXTENSIONS;
    VENDOR = glGetString(GL_VENDOR);
    puts(VENDOR);
    RENDERER = glGetString(GL_RENDERER);
    puts(RENDERER);
    VERSION = glGetString(GL_VERSION);
    puts(VERSION);
    // EXTENSIONS = glGetString(GL_EXTENSIONS);
    // puts(EXTENSIONS);

    GLint max_layers;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_layers);
    printf("max texture size=%d\n", max_layers);
    return 0;
}