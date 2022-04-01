// The MIT License (MIT)
//
// Copyright (c) 2013 Dan Ginsburg, Budirijanto Purnomo
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

//
// Book:      OpenGL(R) ES 3.0 Programming Guide, 2nd Edition
// Authors:   Dan Ginsburg, Budirijanto Purnomo, Dave Shreiner, Aaftab Munshi
// ISBN-10:   0-321-93388-5
// ISBN-13:   978-0-321-93388-1
// Publisher: Addison-Wesley Professional
// URLs:      http://www.opengles-book.com
//            http://my.safaribooksonline.com/book/animation-and-3d/9780133440133
//
// Hello_Triangle.c
//
//    This is a simple example that draws a single triangle with
//    a minimal vertex/fragment shader.  The purpose of this
//    example is to demonstrate the basic concepts of
//    OpenGL ES 3.0 rendering.

#include "hellotriangle.h"

///
// Initialize the shader and program object（初始化着色器和程序对象）
//
static bool init(ESContext *esContext)
{
    UserData *userData = (UserData*)esContext->userData;

    // 清空画布
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

   // 使用顶点数组对象的方式加载顶点数据
                          // 位置              // 颜色
    GLfloat vertices[] = {  0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                           -0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                            0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                            0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
    };
    GLushort indices[] = {0, 1, 2, 3};

    GLfloat vertices2[] = { 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                           -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                            0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                            0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };
    GLushort indices2[] = {0, 1, 2, 3};

   glGenBuffers(2, userData->vboIds);  // 获取顶点缓冲区对象

   glBindBuffer(GL_ARRAY_BUFFER, userData->vboIds[0]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, userData->vboIds[1]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

   glGenVertexArrays(2, userData->vaoIds);
   glBindVertexArray(userData->vaoIds[0]);

   /*glBindBuffer(GL_ARRAY_BUFFER, userData->vboIds[0]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, userData->vboIds[1]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (const void*)0);
   glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (const void*)(0 + 3 * sizeof(GLfloat)));
   glEnableVertexAttribArray(0);
   glEnableVertexAttribArray(1);

   glBindVertexArray(userData->vaoIds[1]);

   glBindBuffer(GL_ARRAY_BUFFER, userData->vboIds[0]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, userData->vboIds[1]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (const void*)0);
   glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (const void*)(0 + 3 * sizeof(GLfloat)));
   glEnableVertexAttribArray(0);
   glEnableVertexAttribArray(1);

   glBindVertexArray(0);

   return true;
}

///
// Draw a triangle using the shader pair created in Init()
// 绘制函数
//
static void draw(ESContext *esContext)
{
   UserData *userData = (UserData*)esContext->userData;

#if false
   // 客户端顶点数组方式加载顶点数据
   // Load the vertex data（加载顶点数据）
                           // 位置              // 颜色
    GLfloat vertices[] = {  0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                           -0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                            0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                            0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
    };
    GLushort indices[] = {0, 1, 2, 3};

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (const void*)vertices);
   glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (const void*)(vertices + 3));
   glEnableVertexAttribArray(0);  // 使能顶点数组
   glEnableVertexAttribArray(1);

   glDrawArrays(GL_TRIANGLE_FAN, 0, 4);  // 绘制数组

   glDisableVertexAttribArray(0);
   glDisableVertexAttribArray(1);

#elif false
   // 使用顶点缓冲区对象的方式加载顶点数据
                          // 位置              // 颜色
    GLfloat vertices[] = {  0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                           -0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                            0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                            0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
    };
    GLushort indices[] = {0, 1, 2, 3};

    if(userData->vboIds[0] == 0 && userData->vboIds[1] == 0)
    {
        glGenBuffers(2, userData->vboIds);  // 获取顶点缓冲区对象

        glBindBuffer(GL_ARRAY_BUFFER, userData->vboIds[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, userData->vboIds[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }
    //glBindBuffer(GL_ARRAY_BUFFER, userData->vboIds[0]);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, userData->vboIds[1]);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (const void*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (const void*)(0 + 3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    //glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

#else
   // 使用顶点数组对象的方式加载顶点数据
   glBindVertexArray(userData->vaoIds[0]);

   glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
   //glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, 0);

   glBindVertexArray(0);
#endif
}

HelloTriangle::HelloTriangle()
{
    memset(&m_esContext, 0, sizeof(m_esContext));
}

HelloTriangle::~HelloTriangle()
{
    release();
}

bool HelloTriangle::initialize(ESContext &esContext)
{
    m_esContext = esContext;
    m_esContext.initFunc = init;
    m_esContext.drawFunc = draw;
    return Common::esMain(m_esContext, ":/vshader.glsl", ":/fshader.glsl");
}

void HelloTriangle::render()
{
    Common::esRender(m_esContext);
}

void HelloTriangle::release()
{
    Common::esEnd(m_esContext);
}

void HelloTriangle::updateData()
{

}
