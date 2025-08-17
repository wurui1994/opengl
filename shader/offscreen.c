
#ifdef DEBUG
#define GL_CHECK(stmt) \
    stmt;              \
    glCheck(#stmt, __FILE__, __LINE__)
#else
#define GL_CHECK(stmt) stmt
#endif

#include <stdio.h>
#include <stdlib.h>

#include <OpenGL/OpenGL.h>
#include <Opengl/glext.h>

#include <string.h>

#ifdef __APPLE__
#include <OpenGL/glu.h>
#include <OpenGL/gl3.h>
// #include <OpenGL/gl3.h>
#else
#include <GL/glu.h>
#endif

void setupContext()
{
    CGLContextObj context;
    CGLPixelFormatAttribute attributes[13] = {
        kCGLPFAOpenGLProfile,
        (CGLPixelFormatAttribute)kCGLOGLPVersion_Legacy,
        kCGLPFAAccelerated,
        kCGLPFAColorSize, (CGLPixelFormatAttribute)24,
        kCGLPFAAlphaSize, (CGLPixelFormatAttribute)8,
        kCGLPFADoubleBuffer,
        kCGLPFASampleBuffers, (CGLPixelFormatAttribute)1,
        kCGLPFASamples, (CGLPixelFormatAttribute)4,
        (CGLPixelFormatAttribute)0};
    CGLPixelFormatObj pix;
    CGLError errorCode;
    GLint num;
    errorCode = CGLChoosePixelFormat(attributes, &pix, &num);
    errorCode = CGLCreateContext(pix, NULL, &context);
    CGLDestroyPixelFormat(pix);
    errorCode = CGLSetCurrentContext(context);
}

void prepareFramebuffer(int width, int height)
{
    GLuint fbo_id = 0;
    GLuint old_fbo_id = 0;
    GLuint renderbuf_id = 0;
    GLuint depthbuf_id = 0;
    // Generate and bind FBO
    GL_CHECK(glGenFramebuffers(1, &fbo_id));
    // glGetIntegerv(GL_FRAMEBUFFER_BINDING, &old_fbo_id);

    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, fbo_id));

    // Generate depth and render buffers
    // GL_CHECK(glGenRenderbuffers(1, &depthbuf_id));
    GL_CHECK(glGenRenderbuffers(1, &renderbuf_id));

    GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, renderbuf_id));
    GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB, width, height));

    // Attach render and depth buffers
    GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                       GL_RENDERBUFFER, renderbuf_id));
}

void renderOpenGL(int width, int height)
{
    GL_CHECK(glViewport(0, 0, width, height));
    //
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    //
    const GLchar *vs_s = "attribute vec4 p;void main(){gl_Position=p;}";
    const GLchar *fs_s = "void main(){gl_FragColor=vec4(1.0,0.0,0.0,1.0);}";
    //
    glShaderSource(vs, 1, &vs_s, 0);
    glShaderSource(fs, 1, &fs_s, 0);
    //
    // glCompileShader(vs);
    glCompileShader(fs);
    //
    GLuint program = glCreateProgram();
    // glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glUseProgram(program);
    //
    float vertices[] = {
        -0.9f, -0.5f, 0.0f, // left
        -0.0f, -0.5f, 0.0f, // right
        -0.45f, 0.5f, 0.0f, // top
                            // second triangle
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top
    };

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)vertices);

    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glFinish();
}

unsigned char *inputImage(int width, int height)
{
    unsigned char *canvas = 0;
    int byte_size = width * height * 3;
    canvas = malloc(byte_size);

    // background black
    memset(canvas, 0, byte_size);
    // gen chess block
    int block_size = 32;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int index = y * width * 3 + x * 3;
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

void renderTexture(int width, int height)
{
    //
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    GL_CHECK(glViewport(0, 0, width, height));

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
//
// const GLchar *vs_s = "attribute vec4 p;void main(){gl_Position=p;}";
// const GLchar *fs_s = "void main(){gl_FragColor=vec4(1.0,0.0,0.0,1.0);}";
#if 1
    const GLchar *vs_s = "attribute vec2 position;"
                         "varying vec2 uv;"
                         "void main(){gl_Position=vec4(position, 0, 1);"
                         "uv = position* 0.5 + 0.5;"
                         "}";
    const GLchar *fs_s = "uniform float time;"
                         "uniform sampler2D texture;"
                         "varying vec2 uv;"
                         "void main(){"
                         //  "gl_FragColor=vec4(1.0,0,0.0,1.0);"
                        //  "gl_FragColor = texture2D(texture, uv * 0.5 + 0.5);"
                            "vec2 uv = uv*0.8+0.1;"
                            "uv += cos(time*vec2(6.0, 7.0) + uv*10.0)*0.02;"
                            "gl_FragColor = texture2D(texture, uv);"
                         "}";
#else
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

#if 1
    static const float position[12] = {
        -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f};
    // GLuint VAO;
    // glGenVertexArrays(1, &VAO);
    // glBindVertexArray(VAO);

    // GLuint pos_buf;
    // glGenBuffers(1, &pos_buf);
    // glBindBuffer(GL_ARRAY_BUFFER, pos_buf);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);

    GLint loc = 0;//glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(loc);
    // glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)position);
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


    unsigned char *canvas = inputImage(width, height);
    // saveFramebuffer(width, height, canvas);
    // glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, canvas);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, canvas);
    // glUniform1i(glGetUniformLocation(program, "texture"), 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glFinish();
}

void saveFramebuffer(int width, int height)
{
    char *img = malloc(width * height * 3);
    // todo: need to vertical flip
    glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, img);
    FILE *ff = fopen("offscreen.ppm", "w");
    char header[256];
    snprintf(header, 256, "P6 %d %d 255 ", width, height);
    size_t i = fwrite(header, sizeof(char), 16, ff);
    i = fwrite(img, sizeof(char), width * height * 3, ff);
    fclose(ff);
    free(img);
}

int main(int argc, char *argv[])
{
    int width = 640;
    int height = 480;

    setupContext();
    prepareFramebuffer(width, height);

    // renderOpenGL(width, height);
    renderTexture(width, height);

    saveFramebuffer(width, height);
    return 0;
}
