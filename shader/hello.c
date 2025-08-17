#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION 1
#endif
// #include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
//
#include <OpenGL/OpenGL.h>
#include <Opengl/glext.h>
#include <Opengl/glu.h>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif
//
#ifdef DEBUG
#define GL_CHECK(stmt) \
    stmt;              \
    glCheck(#stmt, __FILE__, __LINE__)
#else
#define GL_CHECK(stmt) stmt
#endif
//
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//
#define width 640
#define height 480
//
#define USE_BUFFER 0
//
void Run(void);
void glutCenterWindow(void);
//
void update(int value)
{
    glutPostRedisplay();
    glutTimerFunc(100, update, 0);
}
//
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutCenterWindow();
    glutCreateWindow("title");
    //
    // if (glewInit() != GLEW_OK)
    //  return -1;
    //
    // glClearColor(1,1,1,1);
    glutDisplayFunc(Run);
    glutTimerFunc(100, update, 0);
    glutMainLoop();
}
//
void glutCenterWindow(void)
{
    int cx = glutGet(GLUT_SCREEN_WIDTH);
    int cy = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowPosition((cx - width) / 2, (cy - height) / 2);
}

static const float position[12] = {
    -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f};

void saveFramebuffer(int w, int h, char *img)
{
    // char* img = malloc(w * h * 3);
    // todo: need to vertical flip
    // glReadPixels(0, 0, w, h, GL_BGR, GL_UNSIGNED_BYTE, img);
    FILE *ff = fopen("hello.ppm", "w");
    char header[256];
    snprintf(header, 256, "P6 %d %d 255 ", w, h);
    size_t i = fwrite(header, sizeof(char), 16, ff);
    i = fwrite(img, sizeof(char), w * h * 3, ff);
    fclose(ff);
    free(img);
}

unsigned char *inputImage(int w, int h)
{
    unsigned char *canvas = 0;
    int byte_size = w * h * 3;
    canvas = malloc(byte_size);

    // background black
    memset(canvas, 0, byte_size);
    // gen chess block
    int block_size = 32;

    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            int index = y * w * 3 + x * 3;
            int r, g, b;
            if (((y / block_size) & 1) != ((x / block_size) & 1))
            {
                r = 192;
                g = 192;
                b = 192;
            }
            else
            {
                r = 128;
                g = 128;
                b = 128;
            }
            canvas[index + 0] = b;
            canvas[index + 1] = g;
            canvas[index + 2] = r;
            // canvas[index + 3] = 128;
        }
    }
    return canvas;
}


void renderTexture(int w, int h)
{
    //
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    // GL_CHECK(glViewport(0, 0, w, h));

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
//
// const GLchar *vs_s = "attribute vec4 p;void main(){gl_Position=p;}";
// const GLchar *fs_s = "void main(){gl_FragColor=vec4(1.0,0.0,0.0,1.0);}";
#if 1
    const GLchar *vs_s = 
                        "attribute vec2 position;"
                         "varying vec2 uv;"
                         "void main(){gl_Position=vec4(position, 0, 1);"
                         "uv = position* 0.5 + 0.5;"
                         "}";
    const GLchar *fs_s = 
                        // "precision mediump float;"
                        "uniform float time;"
                         "uniform sampler2D texture;"
                         "varying vec2 uv;"
                         "uniform vec2 _uv;"
                         "void main(){\n"
                        //   "gl_FragColor=vec4(1.0,0,0.0,1.0);"
                         //  "gl_FragColor = texture2D(texture, uv * 0.5 + 0.5);"
                        //  "vec2 uv = uv*0.8+0.1;\n"
                        //  "uv += cos(time*vec2(6.0, 7.0) + uv*10.0)*0.02;"
                        // "vec2 xy=uv;"
                        "float duration = 0.5;"
                        "float maxAlpha = 0.4;"
                        "float maxScale = 1.8;"

                        "float progress = mod(time, duration) / duration;" 
                        "float alpha = maxAlpha * (1.0 - progress);"
                        "float scale = 1.0 + (maxScale - 1.0) * progress;"

                        "float weakX = 0.5 + (uv.x - 0.5) / scale;"
                        "float weakY = 0.5 + (uv.y - 0.5) / scale;"
                    
                        "vec2 weakTextureCoords = vec2(weakX, weakY);"
                        "vec4 weakMask = texture2D(texture, weakTextureCoords);"
                        "vec4 mask = texture2D(texture, uv);"

                        "gl_FragColor = mask * (1.0 - alpha) + weakMask * alpha;"
                        //  "gl_FragColor = texture2D(texture, uv);\n"
                         "}";
#else
precision mediump float;

uniform sampler2D texture;
varying vec2 uv;
uniform float time;

void main() {
    float duration = 0.5;
    float maxAlpha = 0.4;
    float maxScale = 1.8;

    float progress = mod(time, duration) / duration; 
    float alpha = maxAlpha * (1.0 - progress);
    float scale = 1.0 + (maxScale - 1.0) * progress;

    float weakX = 0.5 + (uv.x - 0.5) / scale;
    float weakY = 0.5 + (uv.y - 0.5) / scale;
 
    vec2 weakTextureCoords = vec2(weakX, weakY);
    vec4 weakMask = texture2D(texture, weakTextureCoords);
    vec4 mask = texture2D(texture, uv);

    gl_FragColor = mask * (1.0 - alpha) + weakMask * alpha;
}
    const GLchar *vs_s = "attribute vec4 p;void main(){gl_Position=p;}";
    const GLchar *fs_s = "void main(){gl_FragColor=vec4(1.0,0.0,0.0,1.0);}";
#endif
    //
    glShaderSource(vs, 1, &vs_s, 0);
    glShaderSource(fs, 1, &fs_s, 0);
    //
    glCompileShader(vs);
    glCompileShader(fs);
    //
    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glUseProgram(program);

	//
    clock_t c = clock();
    float t = fabs(sin(10.0 * c / CLOCKS_PER_SEC));
    //
    printf("%lf\n", t);
    //
    int timeLoc = glGetUniformLocation(program, "time");
    glUniform1f(timeLoc, t);

#if 1
    static const float position[12] = {
        -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f};
    float uv[12];
    for(int i=0;i<12;i++)
    {
        uv[i] = position[i]*0.5+0.5;
    }
    // GLuint VAO;
    // glGenVertexArrays(1, &VAO);
    // glBindVertexArray(VAO);

    // GLuint pos_buf;
    // glGenBuffers(1, &pos_buf);
    // glBindBuffer(GL_ARRAY_BUFFER, pos_buf);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);

    GLint loc = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(loc);
    // glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)position);
        
    loc = glGetAttribLocation(program, "_uv");
    glEnableVertexAttribArray(loc);
    // glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)uv);
#else
    float vertices[] = {
        -0.9f, -0.5f, 0.0f, // left
        -0.0f, -0.5f, 0.0f, // right
        -0.45f, 0.5f, 0.0f, // top
                            // second triangle
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top
    };

    GLint loc = 0; // glGetAttribLocation(program, "position");
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)vertices);

    glEnableVertexAttribArray(loc);
#endif

    GLuint from;
    glGenTextures(1, &from);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, from);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char *canvas = inputImage(w, h);
    // saveFramebuffer(width, height, canvas);
    // glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, canvas);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, canvas);
    // glUniform1i(glGetUniformLocation(program, "texture"), 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glFinish();
}
//
void Run(void)
{
    renderTexture(width, height);
    glutSwapBuffers();
}