//
// Created by matt on 5/23/16.
//

#include "SDMeshParser.h"
#include "SharedDefines.h"
#include <cstdio>
#include <cstring>
#include "SDObjLoaderInterface.h"

bool32 SDMeshParser::ParseMeshFile(const char* pszBasePath, const char* pszMeshFile, SDStack* pSubObjects)
{
    SDStack meshList;
    SDStack materialStack;

    if (!SDObjLoaderInterface::LoadMeshFile(pszBasePath, pszMeshFile, &meshList, &materialStack)) {
        ERROR_MSG("Failed to load mesh file %s%s", pszBasePath, pszMeshFile);
        return false;
    }

    if (meshList.GetNumElements() == 0) {
        ERROR_MSG("Got 0 meshes from file!");
        return false;
    }

    uint32 nNumMeshes = meshList.GetNumElements();
    LOGI("Loaded %d sub-meshes from file\n", nNumMeshes);

    for (uint32 nMesh = 0; nMesh < nNumMeshes; ++nMesh) {
        SDObjLoaderInterface::TMeshInfo* pInfo = SOFT_CAST(SDObjLoaderInterface::TMeshInfo*, meshList.GetBack());

        LOGI("Sub mesh %d: %d Positions, %d Normals, %d Coords\n",
             nMesh,
             pInfo->pPositions->GetNumElements(),
             pInfo->pNormals->GetNumElements(),
             pInfo->pCoords->GetNumElements());

        ERROR_MSG(""); SDSubMesh* pSubMesh = new SDSubMesh();
        ERROR_MSG(""); FillSubMesh(pInfo->pPositions, pInfo->pNormals, pInfo->pCoords, pSubMesh);
        ERROR_MSG(""); pSubObjects->PushBack(pSubMesh);
        ERROR_MSG(""); free(pInfo);
        ERROR_MSG(""); meshList.RemoveBack();
    }

    LOGI("Found %d sub objects\n", pSubObjects->GetNumElements());

    return true;
}
void SDMeshParser::FillSubMesh(SDStack* pPositionStack, SDStack* pNormalStack, SDStack* pTexcoordStack, SDSubMesh* pSubMesh)
{
    TVec3* pPositions = NULL;
    pPositions = SOFT_CAST(TVec3*, calloc(pPositionStack->GetNumElements(), sizeof(TVec3)));

    TVec3* pNormals = NULL;
    if (pNormalStack->GetNumElements() > 0) {
        pNormals = SOFT_CAST(TVec3*, calloc(pNormalStack->GetNumElements(), sizeof(TVec3)));
    }

    TVec3* pTexCoords = NULL;
    if (pTexcoordStack->GetNumElements() > 0) {
        pTexCoords = SOFT_CAST(TVec3*, calloc(pTexcoordStack->GetNumElements(), sizeof(TVec3)));
    }

    for (uint32 nVertex = 0; nVertex < pPositionStack->GetNumElements(); ++nVertex) {
        //LOGI("Moving vertex %d out of %d\n", nVertex, pPositionStack->GetNumElements());
        pPositions[nVertex] = SOFT_CAST(TVec3*, pPositionStack->GetItem(nVertex))[0];
        //LOGI("Vertex %d = (%f %f %f)\n", nVertex, pPositions[nVertex].x, pPositions[nVertex].y, pPositions[nVertex].z);
        if (pNormals != NULL) {
            pNormals[nVertex] = SOFT_CAST(TVec3*, pNormalStack->GetItem(nVertex))[0];
        }
        if (pTexCoords != NULL) {
            pTexCoords[nVertex] = SOFT_CAST(TVec3*, pTexcoordStack->GetItem(nVertex))[0];
        }
    }

    SDSubMesh::TSubMeshInfo meshInfo = { pPositionStack->GetNumElements()};

    pSubMesh->Create(&meshInfo);
    pSubMesh->UploadVertexData(pPositions, pNormals, pTexCoords);

    free(pPositions);
    if (pNormals != NULL) {
        free(pNormals);
    }
    if (pTexCoords != NULL) {
        free(pTexCoords);
    }
}
