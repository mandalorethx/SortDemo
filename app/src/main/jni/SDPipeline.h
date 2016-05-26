//
// Created by matt on 5/22/16.
//

#ifndef SORTDEMO_SDPIPELINE_H
#define SORTDEMO_SDPIPELINE_H

#include "SharedDefines.h"
#include "SDObject.h"

class SDPipeline : public SDObject {
public:
    struct TPipelineInfo
    {
        const char* pszVertexShaderFile;
        const char* pszFragmentShaderFile;
    };

    SDPipeline();
    ~SDPipeline();

    virtual bool32 Create(void* pInfo);
    virtual void Destroy();

    void SetAlphaBlending(bool32 bEnabled);
    void SetDepthTest(bool32 bEnabled);
    void SetDepthFunction(GLenum eDepthFunc);
    void SetDepthValue(float fVal);
    void SetCulling(bool32 bEnabled);
    void SetCullFace(GLenum eFace);
    void Start();
    void End();
private:
    GLuint LoadShader(GLenum shaderType, const char* pSource);
    GLuint LoadShaderFile(GLenum shaderType, const char* pFile);

    GLuint m_nVs;
    GLuint m_nFs;
    GLuint m_nProgram;

    bool32 m_bAlphaEnabled;
    bool32 m_bDepthEnabled;
    GLenum m_eDepthFunc;
    float  m_fDepthValue;
    bool32 m_bCullEnabled;
    GLenum m_eCullFace;

};


#endif //SORTDEMO_SDPIPELINE_H
