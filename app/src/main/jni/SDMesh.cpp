//
// Created by matt on 5/21/16.
//

#include "SDMesh.h"

SDMesh::SDMesh()
{

}

SDMesh::~SDMesh()
{
    Destroy();
}

bool32 SDMesh::Create(void* pInfo)
{
    TMeshInfo* pMeshInfo = SOFT_CAST(TMeshInfo*, pInfo);
    uint32 nNumSubObjects = 0;
    uint32* pNumVertices = NULL;
    TVec3** ppPositions = NULL;
    TVec3** ppNormals = NULL;
    TVec2** ppCoords = NULL;
    uint32* pNumIndices = NULL;
    uint32** ppIndices = NULL;
    // TODO - load mesh file

    for (uint32 nSm = 0; nSm < nNumSubObjects; ++nSm)
    {
        SDSubMesh::TSubMeshInfo partInfo = {pNumVertices[nSm], pNumIndices[nSm]};
        SDSubMesh* pPart = new SDSubMesh();
        pPart->Create(&partInfo);
        pPart->UploadVertexData(ppPositions[nSm], ppNormals[nSm], ppCoords[nSm]);
        pPart->UploadIndexData(ppIndices[nSm]);
        m_subMeshes.PushBack(pPart);
    }

    return true;

}

void SDMesh::Destroy()
{
    uint32 nNumSubObjects = m_subMeshes.GetNumElements();
    for (uint32 nSm = 0; nSm < nNumSubObjects; ++nSm)
    {
        SDSubMesh* pPart = SOFT_CAST(SDSubMesh*, m_subMeshes.GetBack());
        pPart->Destroy();
        delete pPart;
        m_subMeshes.RemoveBack();
    }
}

void SDMesh::SetTexture(uint32 nLoc, uint32 nSubMesh, GLuint hTexture)
{
    SOFT_CAST(SDSubMesh*, m_subMeshes.GetItem(nSubMesh))->SetTexture(nLoc, hTexture);
}

void SDMesh::SetMVP(uint32 nLoc, TMat4 mMvp)
{
    uint32 nNumSubObjects = m_subMeshes.GetNumElements();
    for (uint32 nSm = 0; nSm < nNumSubObjects; ++nSm)
    {
        SOFT_CAST(SDSubMesh*, m_subMeshes.GetItem(nSm))->SetMVP(nLoc, mMvp);
    }
}

void SDMesh::Draw()
{
    uint32 nNumSubObjects = m_subMeshes.GetNumElements();
    for (uint32 nSm = 0; nSm < nNumSubObjects; ++nSm)
    {
        SOFT_CAST(SDSubMesh*, m_subMeshes.GetItem(nSm))->Draw();
    }
}
