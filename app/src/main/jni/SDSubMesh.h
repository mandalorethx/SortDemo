//
// Created by matt on 5/21/16.
//

#ifndef SORTDEMO_SDSUBMESH_H
#define SORTDEMO_SDSUBMESH_H

#include "SharedDefines.h"
#include "SDObject.h"

enum ESubMeshAttributes
{
    ATTRIB_POSITION,
    ATTRIB_NORMALS,
    ATTRIB_TEXCOORD,
    NumAttribs,
};

class SDSubMesh : public SDObject
{
public:
    struct TSubMeshInfo
    {
        uint32 nNumVertices;
    };

    struct TMaterial
    {
        TVec3 vKa;
        TVec3 vKd;
        TVec3 vKs;
        float fNs;
        float fNi;
        float fD;
        int32 nIllum;

        TMaterial() : vKa(), vKd(), vKs(), fNs(0.f), fD(0.f), nIllum(0) {}
    };

    enum EUniformLocation
    {
        UNIFORM_MVP,
        UNIFORM_TEXTURE,
        UNIFORM_KA,
        UNIFORM_KD,
        UNIFORM_KS,
        UNIFORM_NS,
        UNIFORM_NI,
        UNIFORM_D,
        UNIFORM_ILLUM,
        NumUniforms,
    };


    SDSubMesh();
    ~SDSubMesh();

    virtual bool32 Create(void* pInfo);
    virtual void   Destroy();

    bool32 UploadVertexData(TVec3* pPos, TVec3* pNormals, TVec3* pCoord);
    void   SetMaterial(TMaterial material){m_material=  material;};
    bool32 SetTexture(GLuint hTexId);
    bool32 SetMVP(TMat4 mMvp);

    void Draw();
private:
    struct TAttributeBinding
    {
        ESubMeshAttributes eAttribute;
        uint32             nSize;
        GLenum             eType;
        size_t             nOffset;
    };
    uint32            m_nVertexCount;
    GLuint            m_hVbo;
    GLuint            m_hTexture;
    TMat4             m_mMvp;
    TMaterial         m_material;
    TAttributeBinding m_vBindings[NumAttribs];
};


#endif //SORTDEMO_SDSUBMESH_H
