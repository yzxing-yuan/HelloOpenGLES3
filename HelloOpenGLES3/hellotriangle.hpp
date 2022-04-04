#ifndef HELLOTRIANGLE_H
#define HELLOTRIANGLE_H

#include "IGlesHandle.hpp"
#include "Common/common.hpp"

#if 1
// 使用顶点数组对象的方式加载顶点数据
                       // 位置              // 颜色
static const GLfloat g_vertices[] = {  0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                    -0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                     0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                     0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
};
static const GLushort g_indices[] = {0, 1, 2, 3};

static const GLfloat g_vertices2[] = { 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                    -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                     0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                     0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};
static const GLushort g_indices2[] = {0, 1, 2, 3};
#endif

static bool init(ESContext *esContext)
{
    UserData *userData = (UserData*)esContext->userData;

    glGenBuffers(2, userData->vboIds);  // 获取顶点缓冲区对象

    glBindBuffer(GL_ARRAY_BUFFER, userData->vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices), g_vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, userData->vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indices), g_indices, GL_STATIC_DRAW);

    glGenVertexArrays(2, userData->vaoIds);
    glBindVertexArray(userData->vaoIds[0]);

    /*glBindBuffer(GL_ARRAY_BUFFER, userData->vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices), g_vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, userData->vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indices), g_indices, GL_STATIC_DRAW);*/

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (const void*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (const void*)(0 + 3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(userData->vaoIds[1]);

    glBindBuffer(GL_ARRAY_BUFFER, userData->vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices2), g_vertices2, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, userData->vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indices2), g_indices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (const void*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (const void*)(0 + 3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    return true;
}

static void draw(ESContext *esContext)
{
    UserData *userData = (UserData*)esContext->userData;

 #if false
    // 客户端顶点数组方式加载顶点数据

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (const void*)g_vertices);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (const void*)(g_vertices + 3));
    glEnableVertexAttribArray(0);  // 使能顶点数组
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);  // 绘制数组

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

 #elif false
    // 使用顶点缓冲区对象的方式加载顶点数据

    if(userData->vboIds[0] == 0 && userData->vboIds[1] == 0)
    {
        glGenBuffers(2, userData->vboIds);  // 获取顶点缓冲区对象

        glBindBuffer(GL_ARRAY_BUFFER, userData->vboIds[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices), g_vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, userData->vboIds[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indices), g_indices, GL_STATIC_DRAW);
    }
    //glBindBuffer(GL_ARRAY_BUFFER, userData->vboIds[0]);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices), g_vertices, GL_STATIC_DRAW);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, userData->vboIds[1]);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indices), g_indices, GL_STATIC_DRAW);

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

static void update(ESContext *esContext, float deltaTime)
{
    Q_UNUSED(esContext)
    Q_UNUSED(deltaTime)
}

class HelloTriangle : public IGlesHandle
{
private:
    ESContext m_esContext;

public:
    HelloTriangle()
    {
        memset(&m_esContext, 0, sizeof(m_esContext));
    }

    ~HelloTriangle()
    {
        release();
    }

    bool initialize(ESContext &esContext) override
    {
        m_esContext = esContext;
        m_esContext.initFunc = init;
        m_esContext.drawFunc = draw;
        m_esContext.updateFunc = update;
        return Common::esMain(m_esContext, ":/shaders/vshader_hellotriangle.glsl", ":/shaders/fshader_hellotriangle.glsl");
    }

    void render() override
    {
        Common::esRender(m_esContext);
    }

    void release() override
    {
        Common::esEnd(m_esContext);
    }

    void updateData() override
    {
        Common::esUpdateData(m_esContext, 0);
    }
};

#endif // HELLOTRIANGLE_H
