//
// Created by matt on 5/22/16.
//

#include "SDPipeline.h"
#include <cstdio>
#include <cstdlib>

SDPipeline::SDPipeline()
{
    m_nVs = 0;
    m_nFs = 0;
    m_nProgram = 0;

    m_bAlphaEnabled = false;
    m_bDepthEnabled = false;
    m_eDepthFunc = GL_INVALID_ENUM;
    m_fDepthValue = 0.f;
    m_bCullEnabled = false;
    m_eCullFace = GL_INVALID_ENUM;
}

SDPipeline::~SDPipeline()
{

}

bool32 SDPipeline::Create(void* pInfo)
{
    TPipelineInfo* pPipelineInfo = SOFT_CAST(TPipelineInfo*, pInfo);
    m_nVs = LoadShaderFile(GL_VERTEX_SHADER, pPipelineInfo->pszVertexShaderFile);
    m_nFs = LoadShaderFile(GL_FRAGMENT_SHADER, pPipelineInfo->pszVertexShaderFile);

    m_nProgram = glCreateProgram(); CHECKGL;
    glAttachShader(m_nProgram, m_nVs); CHECKGL;
    glAttachShader(m_nProgram, m_nFs); CHECKGL;
    glLinkProgram(m_nProgram); CHECKGL;
    if (!glIsProgram(m_nProgram))
    {
        CHECKGL;
        ERROR_MSG("Program creation failed!");
        return false;
    }

    m_eDepthFunc = GL_LEQUAL;
    m_eCullFace = GL_CCW;

}

void SDPipeline::Destroy()
{
    glDeleteProgram(m_nProgram);
    glDeleteShader(m_nVs);
    glDeleteShader(m_nFs);
}

void SDPipeline::SetAlphaBlending(bool32 bEnabled)
{
    m_bAlphaEnabled = bEnabled;
}

void SDPipeline::SetDepthTest(bool32 bEnabled)
{
    m_bDepthEnabled = bEnabled;
}

void SDPipeline::SetDepthFunction(GLenum eDepthFunc)
{
    m_eDepthFunc = eDepthFunc;
}

void SDPipeline::SetDepthValue(float fVal)
{
    m_fDepthValue = fVal;
}

void SDPipeline::SetCulling(bool32 bEnabled)
{
    m_bCullEnabled = bEnabled;
}

void SDPipeline::SetCullFace(GLenum eFace)
{
    m_eCullFace = eFace;
}

GLuint SDPipeline::LoadShader(GLenum shaderType, const char* pSource)
{
    GLuint nShader = glCreateShader(shaderType); CHECKGL;
    GLint nShaderLen = strlen(pSource);
    glShaderSource(nShader, 1, &pSource, &nShaderLen); CHECKGL;
    glCompileShader(nShader); CHECKGL;
    return nShader;

}

GLuint SDPipeline::LoadShaderFile(GLenum shaderType, const char* pFile)
{
    FILE* pFileObj = fopen(pFile, "r");
    if (pFileObj == NULL)
    {
        ERROR_MSG("Failed to open shader file %s!", pFile);
        return 0;
    }

    fseek(pFileObj, 0, SEEK_END);
    int32 nSize = ftell(pFileObj);
    fseek(pFileObj, 0, SEEK_SET);
    char* pszFileContent = SOFT_CAST(char*, calloc(nSize+1, sizeof(char)));
    fread(pszFileContent, sizeof(char), nSize, pFileObj);
    fclose(pFileObj);

    GLuint nShader = LoadShader(shaderType, pszFileContent);

    free(pszFileContent);

    return nShader;

}
