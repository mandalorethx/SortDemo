//
// Created by matt on 5/20/16.
//

#ifndef SORTDEMO_SORTDEMORENDERER_H
#define SORTDEMO_SORTDEMORENDERER_H

#include <GLES3/gl3.h>
#include "SharedDefines.h"

static inline bool32 CheckGL(const char* pszFile, int32 nLine)
{
    GLenum eError = glGetError();
    if (eError != GL_NO_ERROR)
    {
        LOGE("%s::%d (0x%X)\n", pszFile, nLine, eError);
        return false;
    }
    return true;
}

#define CHECKGL CheckGL(__FILE__, __LINE__)

class SortDemoRenderer {
public:
    SortDemoRenderer();
    ~SortDemoRenderer();

    bool32 CreateRenderer(uint32 nWidth, uint32 nHeight);
    void   DrawFrame();
    void   DestroyRenderer();
private:
    GLuint LoadShader(GLenum shaderType, const char* pSource);
    GLuint LoadShaderFile(GLenum shaderType, const char* pFile);

    uint32 m_nWidth;
    uint32 m_nHeight;

    GLuint m_nVs;
    GLuint m_nFs;
    GLuint m_nProgram;
};



#endif //SORTDEMO_SORTDEMORENDERER_H
