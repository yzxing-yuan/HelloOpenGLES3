#ifndef ILLUMINATION_HPP
#define ILLUMINATION_HPP

#include "IGlesHandle.hpp"
#include "common.hpp"

#if 1
const GLfloat g_vertices[] =
{  // 位置              // 颜色
    0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
   -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
};
const GLuint g_indices[] = {0, 1, 2};
#endif

static bool init(ESContext *esContext)
{
    UserData *userData = (UserData*)esContext->userData;

    // Get the uniform locations
    userData->mvpLoc = glGetUniformLocation(userData->programObject, "u_mvpMatrix");

    // Starting rotation angle for the cube
    userData->angle = 0.0f;

    userData->numIndices = esGenCube(1.0, &userData->vertices, NULL, NULL, &userData->indices);

    /*userData->numVertices = COUNT_OF(g_vertices);
    int size = userData->numVertices * sizeof(GLfloat);
    userData->vertices = (GLfloat*)malloc(size);
    memcpy(userData->vertices, g_vertices, size);

    userData->numIndices = COUNT_OF(g_indices);
    size = userData->numVertices * sizeof(GLfloat);
    userData->indices = (GLuint*)malloc(size);
    memcpy(userData->indices, g_indices, size);*/

    return true;
}

static void draw(ESContext *esContext)
{
#if 0
    GLfloat *vtxMappedBuf;
    GLushort *idxMappedBuf;

    UserData *userData = (UserData*)esContext->userData;
    glGenBuffers(2, userData->vboIds);

    //---------------------------------------------------------------------------------------------------------
    glBindBuffer(GL_ARRAY_BUFFER, userData->vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices), NULL, GL_STATIC_DRAW);
    vtxMappedBuf = (GLfloat*)glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(g_vertices), GL_MAP_WRITE_BIT|GL_MAP_INVALIDATE_BUFFER_BIT);
    if(vtxMappedBuf == NULL)
    {
        esLogMessage("Error mapping array buffer object.");
        return;
    }
    memcpy(vtxMappedBuf, g_vertices, sizeof(g_vertices));
    if(glUnmapBuffer(GL_ARRAY_BUFFER) == GL_FALSE)
    {
        esLogMessage("Error unmapping array buffer object.");
        return;
    }

    //---------------------------------------------------------------------------------------------------------
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, userData->vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indices), NULL, GL_STATIC_DRAW);
    idxMappedBuf = (GLushort*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(g_indices), GL_MAP_WRITE_BIT|GL_MAP_INVALIDATE_BUFFER_BIT);
    if(idxMappedBuf == NULL)
    {
        esLogMessage("Error mapping element buffer object.");
        return;
    }
    memcpy(idxMappedBuf, g_indices, sizeof(g_indices));
    if(glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER) == GL_FALSE)
    {
        esLogMessage("Error unmapping element buffer object.");
        return;
    }
#else
    /*GLfloat *vtxMappedBuf;
    GLushort *idxMappedBuf;

    UserData *userData = (UserData*)esContext->userData;
    glGenBuffers(2, userData->vboIds);

    //---------------------------------------------------------------------------------------------------------
    size_t verticesSize = 24 * sizeof(GLfloat);
    glBindBuffer(GL_ARRAY_BUFFER, userData->vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, NULL, GL_STATIC_DRAW);
    vtxMappedBuf = (GLfloat*)glMapBufferRange(GL_ARRAY_BUFFER, 0, verticesSize, GL_MAP_WRITE_BIT|GL_MAP_INVALIDATE_BUFFER_BIT);
    if(vtxMappedBuf == NULL)
    {
        esLogMessage("Error mapping array buffer object.");
        return;
    }
    memcpy(vtxMappedBuf, userData->vertices, verticesSize);
    if(glUnmapBuffer(GL_ARRAY_BUFFER) == GL_FALSE)
    {
        esLogMessage("Error unmapping array buffer object.");
        return;
    }

    //---------------------------------------------------------------------------------------------------------
    size_t indicesSize = userData->numIndices * sizeof(GLuint);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, userData->vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, NULL, GL_STATIC_DRAW);
    idxMappedBuf = (GLushort*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, indicesSize, GL_MAP_WRITE_BIT|GL_MAP_INVALIDATE_BUFFER_BIT);
    if(idxMappedBuf == NULL)
    {
        esLogMessage("Error mapping element buffer object.");
        return;
    }
    memcpy(idxMappedBuf, userData->indices, indicesSize);
    if(glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER) == GL_FALSE)
    {
        esLogMessage("Error unmapping element buffer object.");
        return;
    }*/
#endif

    /*glBindBuffer(GL_ARRAY_BUFFER, userData->vboIds[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, userData->vboIds[1]);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (const void*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (const void*)(0 + 3 * sizeof(GLfloat)));

    glUniformMatrix4fv(userData->mvpLoc, 1, GL_FALSE, (GLfloat*)&userData->mvpMatrix.m[0][0]);

    //glDrawArrays(GL_TRIANGLE_FAN, 0, userData->numVertices);
    glDrawElements(GL_TRIANGLE_FAN, userData->numIndices, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/


    UserData *userData = (UserData*)esContext->userData;
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), userData->vertices);
    glEnableVertexAttribArray(0);
    glVertexAttrib4f(1, 1.0f, 0.0f, 0.0f, 1.0f);
    glUniformMatrix4fv(userData->mvpLoc, 1, GL_FALSE, (GLfloat*)&userData->mvpMatrix.m[0][0]);
    glDrawElements(GL_TRIANGLES, userData->numIndices, GL_UNSIGNED_INT, userData->indices);
    glDisableVertexAttribArray(0);
}

static void update(ESContext *esContext, float deltaTime)
{
    Q_UNUSED(deltaTime)
#if 1

    UserData *userData = (UserData*)esContext->userData;
    if(userData->angle >= 360)
    {
        userData->angle = 0;
    }
    else
    {
        userData->angle++;
    }

    ESMatrix modelview;
    ESMatrix perspective;
    float    aspect;

    // Compute the window aspect ratio
    aspect = (GLfloat)esContext->width / (GLfloat)esContext->height;

    // Generate a perspective matrix with a 60 degree FOV
    esMatrixLoadIdentity(&perspective);
    //esPerspective(&perspective, 1.0f, aspect, 0.0f, -0.5f);
    esOrtho(&perspective, -1.0, 1.0, -1.0, 1.0, 0.0, 2.0);
    //esMatrixLookAt(&perspective, 0, 0.5, 1, 0, 0, 0, 0, 1, 0);

    esMatrixLoadIdentity(&modelview);
    //esScale(&modelview, 1.5, 1.5, 1.5);
    //esTranslate(&modelview, 0.5, 0.5, 0.0);
    esRotate(&modelview, userData->angle, 0.0, 0.5, 0.0);

    // Compute the final MVP by multiplying the
    // modevleiw and perspective matrices together
    esMatrixMultiply(&userData->mvpMatrix, &modelview, &perspective);
#endif
}

class MatrixTransform : public IGlesHandle
{
private:
    ESContext m_esContext;

public:
    MatrixTransform()
    {
        memset(&m_esContext, 0, sizeof(m_esContext));
    }

    ~MatrixTransform()
    {
        release();
    }

    bool initialize(ESContext &esContext) override
    {
        m_esContext = esContext;
        m_esContext.initFunc = init;
        m_esContext.drawFunc = draw;
        m_esContext.updateFunc = update;
        return Common::esMain(m_esContext, ":/vshader_illumination.glsl", ":/fshader_illumination.glsl");
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

#endif // ILLUMINATION_HPP
