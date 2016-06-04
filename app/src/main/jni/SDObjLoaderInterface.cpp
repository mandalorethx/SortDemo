//
// Created by matt on 6/1/16.
//

#include "SDObjLoaderInterface.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

bool32 SDObjLoaderInterface::LoadMeshFile(const char* pszPath, const char* pszFileName, SDStack* pMeshes, SDStack* pMaterials) {
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    char pszFullPath[256];
    memset(pszFullPath, 0, sizeof(pszFullPath));
    sprintf(pszFullPath, "%s%s", pszPath, pszFileName);

    std::string err;
    bool32 bRet = tinyobj::LoadObj(shapes, materials, err, pszFullPath, pszPath, 1);

    if (!err.empty()) {
        ERROR_MSG("%s", err.c_str());
    }

    if (!bRet) {
        ERROR_MSG("Load OBJ failed!");
        return false;
    }

    uint32 nNumMeshes = shapes.size();

    LOGI("Found %d sub-meshes\n", nNumMeshes);

    for (uint32 nMesh = 0; nMesh < nNumMeshes; ++nMesh) {
        TMeshInfo* pNode = SOFT_CAST(TMeshInfo*, calloc(sizeof(TMeshInfo), 1));
        pNode[nMesh].pPositions = new SDStack();
        pNode[nMesh].pNormals   = new SDStack();
        pNode[nMesh].pCoords    = new SDStack();
        pNode[nMesh].pMaterials = new SDStack();

        LOGI("Sub-mesh %d: %d Indices, %d Vertices, %d Normals, %d TexCoords\n",
             nMesh,
             shapes[nMesh].mesh.indices.size(),
             shapes[nMesh].mesh.positions.size(),
             shapes[nMesh].mesh.normals.size(),
             shapes[nMesh].mesh.texcoords.size() );

        for (uint32 nIndex = 0; nIndex < shapes[nMesh].mesh.indices.size(); ++nIndex) {
            TVec3 vCurPosition = TVec3();
            memcpy(&vCurPosition, &shapes[nMesh].mesh.positions[shapes[nMesh].mesh.indices[nIndex]*3], sizeof(TVec3));
            pNode[nMesh].pPositions->PushBack(&vCurPosition, sizeof(TVec3));

            if (shapes[nMesh].mesh.normals.size() > 0) {
                TVec3 vCurNormal = TVec3();
                memcpy(&vCurNormal, &shapes[nMesh].mesh.normals[shapes[nMesh].mesh.indices[nIndex]*3], sizeof(TVec3));
                pNode[nMesh].pNormals->PushBack(&vCurNormal, sizeof(TVec3));
            }

            if (shapes[nMesh].mesh.texcoords.size() > 0) {
                TVec3 vCurCoord = TVec3();
                memcpy(&vCurCoord, &shapes[nMesh].mesh.texcoords[shapes[nMesh].mesh.indices[nIndex]*2], sizeof(TVec2));
                vCurCoord.y = 1.f - vCurCoord.y;
                pNode[nMesh].pCoords->PushBack(&vCurCoord, sizeof(TVec3));
            }
        }

        pMeshes->PushBack(pNode, -1);
    }

    return true;

}