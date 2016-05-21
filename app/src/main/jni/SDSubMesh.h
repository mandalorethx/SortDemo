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
        uint32 nNumIndices;
    };

    SDSubMesh();
    ~SDSubMesh();

    virtual bool32 Create(void* pInfo);
    virtual void   Destroy();

    bool32 UploadVertexData(TVec3* pPos, TVec3* pNormals, TVec2* pCoord);
    bool32 UploadIndexData(uint32* pIndices);
    bool32 SetTexture(uint32 nLoc, GLuint hTexId);
    bool32 SetMVP(uint32 nLoc, TMat4 mMvp);

    void Draw();
private:
    uint32 m_nVertexCount;
    uint32 m_nIndexCount;
    GLuint m_hVbo;
    GLuint m_hIbo;
    uint32 m_nTextureLocation;
    GLuint m_hTexture;
    uint32 m_nMatrixLocation;
    TMat4  m_mMvp;

};


#endif //SORTDEMO_SDSUBMESH_H
