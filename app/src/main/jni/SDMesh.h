//
// Created by matt on 5/21/16.
//

#ifndef SORTDEMO_SDMESH_H
#define SORTDEMO_SDMESH_H

#include "SharedDefines.h"
#include "SDSubMesh.h"
#include "SDStack.h"

class SDMesh : public SDObject {
public:
    struct TMeshInfo
    {
        const char* pszMeshObjectFile;
        const char*pszMeshMaterialFile;
    };

    SDMesh();
    ~SDMesh();

    virtual bool32 Create(void* pInfo);
    virtual void Destroy();

    void SetTexture(uint32 nLoc, uint32 nSubMesh, GLuint hTexture);
    void SetMVP(uint32 nLoc, TMat4 mMvp);

    void Draw();
private:
    SDStack m_subMeshes;

};


#endif //SORTDEMO_SDMESH_H
