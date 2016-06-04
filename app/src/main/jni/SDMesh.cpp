//
// Created by matt on 5/21/16.
//

#include "SDMesh.h"
#include "SDMeshParser.h"

SDMesh::SDMesh()
{

}

SDMesh::~SDMesh()
{
    Destroy();
}

bool32 SDMesh::Create(void* pInfo) {
    TMeshInfo* pMeshInfo = SOFT_CAST(TMeshInfo*, pInfo);
    bool32 bPass =  SDMeshParser::ParseMeshFile(pMeshInfo->pszBasePath, pMeshInfo->pszMeshObjectFile, &m_subMeshes);
    LOGI("Mesh created with %d submeshes\n", m_subMeshes.GetNumElements());
    return bPass;
}

void SDMesh::Destroy() {
    uint32 nNumSubObjects = m_subMeshes.GetNumElements();
    for (uint32 nSm = 0; nSm < nNumSubObjects; ++nSm)
    {
        SDSubMesh* pPart = SOFT_CAST(SDSubMesh*, m_subMeshes.GetBack());
        pPart->Destroy();
        delete pPart;
        m_subMeshes.RemoveBack();
    }
}

void SDMesh::SetTexture(uint32 nSubMesh, GLuint hTexture) {
    SOFT_CAST(SDSubMesh*, m_subMeshes.GetItem(nSubMesh))->SetTexture(hTexture);
}

void SDMesh::SetMVP(TMat4 mMvp) {
    uint32 nNumSubObjects = m_subMeshes.GetNumElements();
    for (uint32 nSm = 0; nSm < nNumSubObjects; ++nSm) {
        SOFT_CAST(SDSubMesh*, m_subMeshes.GetItem(nSm))->SetMVP(mMvp);
    }
}

void SDMesh::Draw() {
    uint32 nNumSubObjects = m_subMeshes.GetNumElements();
    for (uint32 nSm = 0; nSm < nNumSubObjects; ++nSm) {
        SOFT_CAST(SDSubMesh*, m_subMeshes.GetItem(nSm))->Draw();
    }
}
