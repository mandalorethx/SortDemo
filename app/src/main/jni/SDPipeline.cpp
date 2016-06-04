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
    LoadShader(GL_VERTEX_SHADER, pPipelineInfo->pszVertexShaderFile, &m_nVs);
    LoadShader(GL_FRAGMENT_SHADER, pPipelineInfo->pszFragmentShaderFile, &m_nFs);

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

    GLint nLinkStatus = 0;
    glGetProgramiv(m_nProgram, GL_LINK_STATUS, &nLinkStatus); CHECKGL;
    if (nLinkStatus == GL_FALSE) {
        GLint nLogLen = 0;
        glGetProgramiv(m_nProgram, GL_INFO_LOG_LENGTH, &nLogLen); CHECKGL;
        if (nLogLen == 0) {
            ERROR_MSG("Link status failed, but info log is 0!");
            return false;
        } else {
            GLchar* pszInfoLog = SOFT_CAST(GLchar*, calloc(nLogLen+1, sizeof(GLchar)));
            glGetProgramInfoLog(m_nProgram, nLogLen+1, &nLogLen, pszInfoLog); CHECKGL;
            ERROR_MSG("Link Log: %s", pszInfoLog);
            free(pszInfoLog);
            return false;
        }
    }

    m_eDepthFunc = GL_LEQUAL;
    m_eCullFace = GL_CCW;
    return true;
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

void SDPipeline::SetCullFace(GLenum eFace) {
    m_eCullFace = eFace;
}

void SDPipeline::Start() {
    if (!glIsProgram(m_nProgram)) {
        ERROR_MSG("Invalid program object!");
    }
    glUseProgram(m_nProgram); CHECKGL;
    if (m_bAlphaEnabled) {
        glEnable(GL_BLEND); CHECKGL;
        glBlendEquation(GL_FUNC_ADD); CHECKGL;
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); CHECKGL;
    }
    else {
        glDisable(GL_BLEND);
    }
    if (m_bCullEnabled) {
        glEnable(GL_CULL_FACE); CHECKGL;
        glFrontFace(m_eCullFace); CHECKGL;
    }
    else {
        glDisable(GL_CULL_FACE); CHECKGL;
    }
    if (m_bDepthEnabled) {
        glEnable(GL_DEPTH_TEST); CHECKGL;
        glDepthFunc(m_eDepthFunc); CHECKGL;
        glClearDepthf(m_fDepthValue); CHECKGL;
        glClear(GL_DEPTH_BUFFER_BIT); CHECKGL;
    } else {
        glDisable(GL_DEPTH_TEST); CHECKGL;
    }

    glClearColor(0.25f, 0.25f, 0.25f, 1.0); CHECKGL;
    glClear(GL_COLOR_BUFFER_BIT); CHECKGL;

}

void SDPipeline::End() {
    glUseProgram(0); CHECKGL;
    glEnable(GL_BLEND); CHECKGL;
    glEnable(GL_CULL_FACE); CHECKGL;
    glEnable(GL_DEPTH_TEST); CHECKGL;

}

void SDPipeline::LoadShader(GLenum shaderType, const char* pSource, GLuint* pShader) {
    GLuint nShader = glCreateShader(shaderType); CHECKGL;
    GLint nShaderLen = strlen(pSource);
    glShaderSource(nShader, 1, &pSource, &nShaderLen); CHECKGL;
    glCompileShader(nShader); CHECKGL;

    GLint nCompiled = -1;
    glGetShaderiv(nShader, GL_COMPILE_STATUS, &nCompiled);
    if (!nCompiled) {
        GLint infoLen = 0;
        glGetShaderiv(nShader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen) {
            char* buf = SOFT_CAST(char*, calloc(infoLen, sizeof(char)));
            if (buf) {
                glGetShaderInfoLog(nShader, infoLen, NULL, buf);
                ERROR_MSG("Could not compile shader %d:\n%s\n", shaderType, buf);
                free(buf);
            }
            glDeleteShader(nShader);
            nShader = 0;
        }
    }

    *pShader = nShader;

}

void SDPipeline::LoadShaderFile(GLenum shaderType, const char* pFile, GLuint* pShader) {
    FILE* pFileObj = fopen(pFile, "r");
    if (pFileObj == NULL) {
        ERROR_MSG("Failed to open shader file %s!", pFile);
        return;
    }

    fseek(pFileObj, 0, SEEK_END);
    int32 nSize = ftell(pFileObj);
    fseek(pFileObj, 0, SEEK_SET);
    char* pszFileContent = SOFT_CAST(char*, calloc(nSize+1, sizeof(char)));
    fread(pszFileContent, sizeof(char), nSize, pFileObj);
    fclose(pFileObj);

    LoadShader(shaderType, pszFileContent, pShader);

    free(pszFileContent);
}
