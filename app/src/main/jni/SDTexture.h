//
// Created by matt on 5/22/16.
//

#ifndef SORTDEMO_SDTEXTURE_H
#define SORTDEMO_SDTEXTURE_H

#include "SharedDefines.h"
#include "SDObject.h"

class SDTexture : public SDObject {
public:
    struct TTextureInfo
    {
        const char* pszFileName;
        uint32      m_nWith;
        uint32      m_nHeight;
        GLenum      m_eFormat;
    };

    SDTexture();
    ~SDTexture();

    virtual bool32 Create(void* pInfo);
    virtual void Destroy();

    void BindTexture();
private:
    bool32 LoadTextureFileTGA(const char* pszFileName, uint32* pWidth, uint32* pHeight, void** ppData);
    bool32 LoadTextureFilePNG(const char* pszFileName, uint32* pWidth, uint32* pHeight, void** ppData);
    bool32 LoadTextureFile(const char* pszFileName, uint32* pWidth, uint32* pHeight, void** ppData);

    GLuint m_hTextureID;
};


#endif //SORTDEMO_SDTEXTURE_H
