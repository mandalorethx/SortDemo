//
// Created by matt on 5/21/16.
//

#include "SDSubMesh.h"

SDSubMesh::SDSubMesh()
{
    m_nVertexCount = 0;
    m_nIndexCount = 0;
    m_hVbo = 0;
    m_hIbo = 0;
    m_nTextureLocation = 0;
    m_hTexture = 0;
    m_nMatrixLocation = 0;
    m_mMvp = TMat4();
}

SDSubMesh::~SDSubMesh()
{
    Destroy();
}

bool32 SDSubMesh::Create(void* pInfo)
{
    TSubMeshInfo* pMeshInfo = SOFT_CAST(TSubMeshInfo*, pInfo);
    m_nVertexCount = pMeshInfo->nNumVertices;
    m_nIndexCount = pMeshInfo->nNumIndices;

    glGenBuffers(1, &m_hVbo); CHECKGL;
    glBindBuffer(GL_ARRAY_BUFFER, m_hVbo); CHECKGL;
    glBufferData(GL_ARRAY_BUFFER, m_nVertexCount*(2*sizeof(TVec3)+sizeof(TVec2)),NULL, GL_STATIC_DRAW); CHECKGL;
    glBindBuffer(GL_ARRAY_BUFFER, 0); CHECKGL;

    glGenBuffers(1, &m_hIbo); CHECKGL;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_hIbo); CHECKGL;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_nIndexCount*sizeof(GLuint),NULL, GL_STATIC_DRAW); CHECKGL;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); CHECKGL;

}

void SDSubMesh::Destroy()
{
    glDeleteBuffers(1, &m_hVbo);
    glDeleteBuffers(1, &m_hIbo);
    glDeleteTextures(1, &m_hTexture);

    m_nVertexCount = 0;
    m_nIndexCount = 0;
    m_hVbo = 0;
    m_hIbo = 0;
    m_nTextureLocation = 0;
    m_hTexture = 0;
    m_nMatrixLocation = 0;
    m_mMvp = TMat4();
}

bool32 SDSubMesh::UploadVertexData(TVec3* pPos, TVec3* pNormals, TVec2* pCoord)
{
    // TODO - make more general, so it is OK if tex coords are NULL
    glBindBuffer(GL_ARRAY_BUFFER, m_hVbo); CHECKGL;
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_nVertexCount*sizeof(TVec3), pPos); CHECKGL;
    glBufferSubData(GL_ARRAY_BUFFER, m_nVertexCount*sizeof(TVec3), m_nVertexCount*sizeof(TVec3), pNormals); CHECKGL;
    glBufferSubData(GL_ARRAY_BUFFER, 2*m_nVertexCount*sizeof(TVec3), m_nVertexCount*sizeof(TVec2), pCoord); CHECKGL;
    glBindBuffer(GL_ARRAY_BUFFER, 0); CHECKGL;

}

bool32 SDSubMesh::UploadIndexData(uint32* pIndices)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_hIbo); CHECKGL;
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_nIndexCount*sizeof(GLuint), pIndices); CHECKGL;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); CHECKGL;

}

bool32 SDSubMesh::SetTexture(uint32 nLoc, GLuint hTexId)
{
    m_hTexture = hTexId;
    m_nTextureLocation = nLoc;
}

bool32 SDSubMesh::SetMVP(uint32 nLoc, TMat4 mMvp)
{
    m_mMvp = mMvp;
    m_nMatrixLocation = nLoc;
}

void SDSubMesh::Draw()
{
    glActiveTexture(GL_TEXTURE0); CHECKGL;
    glBindTexture(GL_TEXTURE_2D, m_hTexture); CHECKGL;
    glUniform1i(m_nTextureLocation, 0); CHECKGL;

    glUniformMatrix4fv(m_nMatrixLocation, 1, GL_FALSE, HARD_CAST(float*, &m_mMvp)); CHECKGL;

    glBindBuffer(GL_ARRAY_BUFFER, m_hVbo); CHECKGL;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_hIbo); CHECKGL;

    glVertexAttribPointer(ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL); CHECKGL;
    glEnableVertexAttribArray(ATTRIB_POSITION); CHECKGL;

    glVertexAttribPointer(ATTRIB_NORMALS, 3, GL_FLOAT, GL_FALSE, 0, HARD_CAST(void*, m_nVertexCount*sizeof(TVec3))); CHECKGL;
    glEnableVertexAttribArray(ATTRIB_NORMALS); CHECKGL;

    glVertexAttribPointer(ATTRIB_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, HARD_CAST(void*, 2*m_nVertexCount*sizeof(TVec3))); CHECKGL;
    glEnableVertexAttribArray(ATTRIB_TEXCOORD); CHECKGL;

    glDrawElements(GL_TRIANGLES, m_nIndexCount, GL_UNSIGNED_INT, NULL); CHECKGL;

    glDisableVertexAttribArray(ATTRIB_TEXCOORD); CHECKGL;
    glDisableVertexAttribArray(ATTRIB_NORMALS); CHECKGL;
    glDisableVertexAttribArray(ATTRIB_POSITION); CHECKGL;

    glBindBuffer(GL_ARRAY_BUFFER, 0); CHECKGL;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); CHECKGL;

    glBindTexture(GL_TEXTURE_2D, 0); CHECKGL;
}
