#ifndef COMMON_HPP
#define COMMON_HPP

#include <QByteArray>
#include <QFile>
#include <QThread>
#include "esUtil.h"

#define COUNT_OF(a) (sizeof(a) / sizeof(a[0]))

typedef struct
{
   // Handle to a program object
   GLuint programObject;  // 程序对象的句柄
   GLuint vboIds[2];      // 顶点缓冲区对象
   GLuint vaoIds[1];      // 顶点数组对象Id

   // Uniform locations
   GLint  mvpLoc;

   // Vertex daata
   GLfloat  *vertices;
   GLuint   *indices;
   int       numVertices;
   int       numIndices;

   // Rotation angle
   GLfloat   angle;

   // MVP matrix
   ESMatrix  mvpMatrix;
} UserData;

class Common
{
public:
    // 加载着色器文件
    static QByteArray LoadShaderFile(const QString &fileName)
    {
        QByteArray shaderByteArr;

        QFile file(fileName);
        file.open(QIODevice::ReadOnly|QIODevice::Text);
        if(file.isOpen())
        {
            shaderByteArr = file.readAll();
            file.close();
        }

        return shaderByteArr;
    }

    ///
    // Create a shader object, load the shader source, and
    // compile the shader.
    // 创建一个着色器对象、加载着色器源代码和编译该着色器代码。
    //
    static GLuint LoadShader(GLenum type, const char *shaderSrc)
    {
       GLuint shader;  // 着色器对象的句柄
       GLint compiled;  // 编译状态

       // Create the shader object（创建着色器对象）
       shader = glCreateShader(type);

       if(shader == 0)
       {
          return 0;
       }

       // Load the shader source（加载着色器源代码）
       glShaderSource(shader, 1, &shaderSrc, NULL);

       // Compile the shader（编译着色器代码）
       glCompileShader(shader);

       // Check the compile status（检查编译状态）
       glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);  // 获取着色器对象的编译状态

       if(!compiled)
       {
          GLint infoLen = 0;

          glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);  // 获取着色器对象的日志字符串的长度

          if(infoLen > 1)
          {
             char *infoLog = (char*)malloc(sizeof(char)* infoLen);

             glGetShaderInfoLog(shader, infoLen, NULL, infoLog);  // 获取着色器对象的日志字符串
             esLogMessage("Error compiling shader:\n%s\n", infoLog);  // 打印日志信息

             free(infoLog);
          }

          glDeleteShader(shader);  // 删除着色器对象

          return 0;
       }

       return shader;
    }

    // 创建和绑定缓冲区对象
    static void InitVertexBufferObjects(GLfloat *vertexBuffer,
                                 GLushort *indices,
                                 GLuint numVertices,
                                 GLuint numIndices,
                                 GLuint *vboIds)
    {
        glGenBuffers(2, vboIds);

        glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
        glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(GLfloat), vertexBuffer, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLushort), indices, GL_STATIC_DRAW);
    }

    static bool init(const ESContext &esContext, const QString &vshaderFilePath, const QString &fshaderFilePath)
    {
        UserData *userData = (UserData*)esContext.userData;

        QByteArray vShaderByteArr = LoadShaderFile(vshaderFilePath);
        QByteArray fShaderByteArr = LoadShaderFile(fshaderFilePath);

        GLuint vertexShader;
        GLuint fragmentShader;
        GLuint programObject;
        GLint linked;

        // Load the vertex/fragment shaders（加载顶点/片段着色器）
        vertexShader = Common::LoadShader(GL_VERTEX_SHADER, vShaderByteArr.data());
        fragmentShader = Common::LoadShader(GL_FRAGMENT_SHADER, fShaderByteArr.data());

        // Create the program object（创建程序对象）
        programObject = glCreateProgram();

        if(programObject == 0)
        {
           return false;
        }

        glAttachShader(programObject, vertexShader);  // 连接顶点着色器
        glAttachShader(programObject, fragmentShader);  // 连接片段着色器

        // Link the program（链接程序）
        glLinkProgram(programObject);

        // Check the link status（检查链接状态）
        glGetProgramiv(programObject, GL_LINK_STATUS, &linked);  // 获取程序对象的链接状态

        if(!linked)
        {
           GLint infoLen = 0;

           glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);  // 获取程序对象的日志字符串的长度

           if(infoLen > 1)
           {
              char *infoLog = (char*)malloc(sizeof(char)* infoLen);

              glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);  // 获取程序对象的日志字符串
              esLogMessage("Error linking program:\n%s\n", infoLog);  // 打印日志信息

              free(infoLog);
           }

           glDeleteProgram(programObject);  // 删除程序对象

           return false;
        }

        // Store the program object（存储程序对象）
        userData->programObject = programObject;

        return true;
    }

    ///
    // Draw a triangle using the shader pair created in Init()
    // 绘制函数
    //
    static void draw(const ESContext &esContext)
    {
       UserData *userData = (UserData*)esContext.userData;

       // Set the viewport（设置视区）
       glViewport(0, 0, esContext.width, esContext.height);

       // Clear the color buffer（清除颜色缓冲区）
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       // Use the program object（设置指定的程序对象为活动程序）
       glUseProgram(userData->programObject);
    }

    // 开始程序操作
    static bool esMain(ESContext &esContext, const QString &vshaderFilePath, const QString &fshaderFilePath)
    {
        esContext.userData = malloc(sizeof(UserData));
        memset(esContext.userData, 0, sizeof(UserData));

       esCreateWindow(&esContext, /*"Hello Triangle", esContext->width, esContext->height,*/ ES_WINDOW_RGB);

       if(!init(esContext, vshaderFilePath, fshaderFilePath))
       {
           return false;
       }

       if (esContext.initFunc)
       {
           if(!esContext.initFunc(&esContext))
           {
              return false;
           }
       }

       esContext.shutdownFunc = Shutdown;

       return true;
    }

    // 渲染操作
    static void esRender(ESContext &esContext)
    {
        draw(esContext);

        if(esContext.drawFunc)
        {
            esContext.drawFunc(&esContext);
            QThread::msleep(22);
            eglSwapBuffers(esContext.eglDisplay, esContext.eglSurface);
        }
    }

    // 结束程序操作
    static void esEnd(ESContext &esContext)
    {
        if(esContext.shutdownFunc != NULL)
        {
            esContext.shutdownFunc(&esContext);
        }

        if(esContext.userData != NULL)
        {
            free(esContext.userData);
        }
    }

    // 更新数据操作
    static void esUpdateData(ESContext &esContext, float deltaTime)
    {
        if(esContext.updateFunc)
        {
            esContext.updateFunc(&esContext, deltaTime);
        }
    }

private:
    static void Shutdown(ESContext *esContext)
    {
       UserData *userData = (UserData*)esContext->userData;

       if(sizeof(userData->vboIds[0] != 0))
       {
           int count = sizeof(userData->vboIds) / sizeof(userData->vboIds[0]);
           glDeleteBuffers(count, userData->vboIds);
       }

       if(userData->vertices != NULL)
       {
          free(userData->vertices);
       }

       if(userData->indices != NULL)
       {
          free(userData->indices);
       }

       glDeleteProgram(userData->programObject);
    }
};

#endif // COMMON_HPP
