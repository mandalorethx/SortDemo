//
// Created by matt on 5/21/16.
//

#include "SDSubMesh.h"

SDSubMesh::SDSubMesh() {
    m_nVertexCount = 0;
    m_hVbo = 0;
    m_hTexture = 0;
    m_mMvp = TMat4();

    memset(m_vBindings, 0, sizeof(m_vBindings));
}

SDSubMesh::~SDSubMesh() {
    Destroy();
}

bool32 SDSubMesh::Create(void* pInfo) {
    TSubMeshInfo* pMeshInfo = SOFT_CAST(TSubMeshInfo*, pInfo);
    m_nVertexCount = pMeshInfo->nNumVertices;

    glGenBuffers(1, &m_hVbo); CHECKGL;
    glBindBuffer(GL_ARRAY_BUFFER, m_hVbo); CHECKGL;
    glBufferData(GL_ARRAY_BUFFER, m_nVertexCount*3*sizeof(TVec3), NULL, GL_STATIC_DRAW); CHECKGL;
    glBindBuffer(GL_ARRAY_BUFFER, 0); CHECKGL;

    return true;
}

void SDSubMesh::Destroy() {
    glDeleteBuffers(1, &m_hVbo);
    glDeleteTextures(1, &m_hTexture);

    m_nVertexCount = 0;
    m_hVbo = 0;
    m_hTexture = 0;
    m_mMvp = TMat4();
}

bool32 SDSubMesh::UploadVertexData(TVec3* pPos, TVec3* pNormals, TVec3* pCoord) {
    size_t nCurOffset = 0;
    glBindBuffer(GL_ARRAY_BUFFER, m_hVbo); CHECKGL;
    if (pPos != NULL) {
        m_vBindings[ATTRIB_POSITION].eAttribute = ATTRIB_POSITION;
        m_vBindings[ATTRIB_POSITION].nSize      = 3;
        m_vBindings[ATTRIB_POSITION].eType      = GL_FLOAT;
        m_vBindings[ATTRIB_POSITION].nOffset    = nCurOffset;
        glBufferSubData(GL_ARRAY_BUFFER, nCurOffset, m_nVertexCount*sizeof(TVec3), pPos); CHECKGL;
        nCurOffset += m_nVertexCount*sizeof(TVec3);
    }
    else {
        m_vBindings[ATTRIB_POSITION].eAttribute = NumAttribs;
        ERROR_MSG("NULL positions!");
        return false;
    }

    m_vBindings[ATTRIB_NORMALS].eAttribute = ATTRIB_NORMALS;
    m_vBindings[ATTRIB_NORMALS].nSize      = 3;
    m_vBindings[ATTRIB_NORMALS].eType      = GL_FLOAT;
    m_vBindings[ATTRIB_NORMALS].nOffset    = nCurOffset;
    if (pNormals != NULL) {
        glBufferSubData(GL_ARRAY_BUFFER, nCurOffset, m_nVertexCount*sizeof(TVec3), pNormals); CHECKGL;
        nCurOffset += m_nVertexCount*sizeof(TVec3);
    } else {
        TVec3* pTmpNormals = SOFT_CAST(TVec3*, calloc(m_nVertexCount, sizeof(TVec3)));
        for (uint32 nVertex = 0; nVertex < m_nVertexCount; ++nVertex) {
            pTmpNormals[nVertex].x = pPos[nVertex].x;
            pTmpNormals[nVertex].y = pPos[nVertex].y;
            pTmpNormals[nVertex].z = pPos[nVertex].z;
        }
        glBufferSubData(GL_ARRAY_BUFFER, nCurOffset, m_nVertexCount*sizeof(TVec3), pTmpNormals); CHECKGL;
        nCurOffset += m_nVertexCount*sizeof(TVec3);
        free(pTmpNormals);
    }

    m_vBindings[ATTRIB_TEXCOORD].eAttribute = ATTRIB_TEXCOORD;
    m_vBindings[ATTRIB_TEXCOORD].nSize      = 3;
    m_vBindings[ATTRIB_TEXCOORD].eType      = GL_FLOAT;
    m_vBindings[ATTRIB_TEXCOORD].nOffset    = nCurOffset;
    if (pCoord != NULL)
    {
        glBufferSubData(GL_ARRAY_BUFFER, nCurOffset, m_nVertexCount*sizeof(TVec3), pCoord); CHECKGL;
        nCurOffset += m_nVertexCount*sizeof(TVec3);
    } else {
        TVec3* pTmpCoords = SOFT_CAST(TVec3*, calloc(m_nVertexCount, sizeof(TVec3)));
        for (uint32 nVertex = 0; nVertex < m_nVertexCount; ++nVertex) {
            pTmpCoords[nVertex].x = ( pPos[nVertex].x + 1.f)/2.f;
            pTmpCoords[nVertex].y = ( pPos[nVertex].y + 1.f)/2.f;
            pTmpCoords[nVertex].z = ( pPos[nVertex].z + 1.f)/2.f;
        }
        glBufferSubData(GL_ARRAY_BUFFER, nCurOffset, m_nVertexCount*sizeof(TVec3), pTmpCoords); CHECKGL;
        nCurOffset += m_nVertexCount*sizeof(TVec3);
        free(pTmpCoords);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0); CHECKGL;
    return true;

}

bool32 SDSubMesh::SetTexture(GLuint hTexId) {
    m_hTexture = hTexId;
    return true;
}

bool32 SDSubMesh::SetMVP(TMat4 mMvp) {
    m_mMvp = mMvp;
    return true;
}

void SDSubMesh::Draw() {
    if (m_hTexture != 0) {
        glActiveTexture(GL_TEXTURE0);
        CHECKGL;
        glBindTexture(GL_TEXTURE_2D, m_hTexture);
        CHECKGL;
        glUniform1i(UNIFORM_TEXTURE, 0);
        CHECKGL;
    }

    glUniformMatrix4fv(UNIFORM_MVP, 1, GL_FALSE, HARD_CAST(float*, &m_mMvp)); CHECKGL;

//    glUniform3fv(UNIFORM_KA, 1, HARD_CAST(float*, &m_material.vKa)); CHECKGL;
//    glUniform3fv(UNIFORM_KS, 1, HARD_CAST(float*, &m_material.vKs)); CHECKGL;
//    glUniform3fv(UNIFORM_KD, 1, HARD_CAST(float*, &m_material.vKd)); CHECKGL;
//    glUniform1f(UNIFORM_NS, m_material.fNs); CHECKGL;
//    glUniform1f(UNIFORM_NI, m_material.fNi); CHECKGL;
//    glUniform1f(UNIFORM_D, m_material.fD); CHECKGL;
//    glUniform1i(UNIFORM_ILLUM, m_material.nIllum); CHECKGL;

    glBindBuffer(GL_ARRAY_BUFFER, m_hVbo); CHECKGL;

    for (uint32 nAttrib = 0; nAttrib < NumAttribs; ++nAttrib) {
        if (m_vBindings[nAttrib].eAttribute != NumAttribs) {
            glVertexAttribPointer(m_vBindings[nAttrib].eAttribute,
                                  m_vBindings[nAttrib].nSize,
                                  m_vBindings[nAttrib].eType,
                                  GL_FALSE,
                                  0,
                                  HARD_CAST(void*, m_vBindings[nAttrib].nOffset)); CHECKGL;
            glEnableVertexAttribArray(m_vBindings[nAttrib].eAttribute); CHECKGL;
        }
    }

    //glDrawElements(GL_TRIANGLES, m_nIndexCount, GL_UNSIGNED_INT, NULL); CHECKGL;
    glDrawArrays(GL_TRIANGLES, 0, m_nVertexCount); CHECKGL;

    for (uint32 nAttrib = 0; nAttrib < NumAttribs; ++nAttrib) {
        if (m_vBindings[nAttrib].eAttribute != NumAttribs) {
            glDisableVertexAttribArray(nAttrib); CHECKGL;
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0); CHECKGL;

    glBindTexture(GL_TEXTURE_2D, 0); CHECKGL;
}
