//
// Created by matt on 5/23/16.
//

#include "SDMeshParser.h"
#include "SharedDefines.h"
#include <cstdio>
#include <cstring>

bool32 SDMeshParser::ParseMeshFile(const char* pszMeshFile, SDStack* pSubObjects)
{
    FILE* pFile = fopen(pszMeshFile, "r");
    if (pFile == NULL) {
        ERROR_MSG("Failed to open mesh file %s!", pszMeshFile);
        return false;
    }

    fseek(pFile, 0, SEEK_END);
    int32 nSize = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);
    char* pszFileContent = SOFT_CAST(char*, calloc(nSize+1, sizeof(char)));
    fread(pszFileContent, sizeof(char), nSize, pFile);
    fclose(pFile);

    SDStack* pPositionStack = new SDStack();
    SDStack* pNormalStack = new SDStack();
    SDStack* pTexcoordStack = new SDStack();
    SDStack* pIndexStack = new SDStack();
    SDStack* pMaterialStack = new SDStack();
    SDStack* pSubObjectsStack = new SDStack();

    char* pszCurPointer = pszFileContent;
    bool32 bDone = false;

    while (!bDone) {
        char* pszNewLine = strchr(pszCurPointer, '\n');
        if (pszNewLine != NULL) {
            size_t nLen = pszNewLine - pszCurPointer + 1;
            char* pszSubLine = SOFT_CAST(char*, calloc(nLen+1, 1));
            memcpy(pszSubLine, pszCurPointer, nLen);

            if (strstr(pszSubLine, "g ") != NULL || strstr(pszSubLine, "o ") != NULL) {
                if (pSubObjectsStack->GetNumElements() > 0) {
                    FillSubMesh(pPositionStack, pNormalStack, pTexcoordStack, pIndexStack, SOFT_CAST(SDSubMesh*, pSubObjectsStack->GetBack()));
                    ResetStacks(pPositionStack, pNormalStack, pTexcoordStack, pIndexStack);
                }
                SDSubMesh* pSubMesh = new SDSubMesh();
                pSubObjectsStack->PushBack(pSubMesh);
            }
            if (strstr(pszSubLine, "v ") != NULL) {
                TVec3* vVertex = new TVec3();
                sscanf(pszSubLine, "v %f %f %f", &vVertex->x, &vVertex->y, &vVertex->z);
                pPositionStack->PushBack(vVertex);
            }
            if (strstr(pszSubLine, "vn ") != NULL) {
                TVec3* vNormal = new TVec3();
                sscanf(pszSubLine, "vn %f %f %f", &vNormal->x, &vNormal->y, &vNormal->z);
                pNormalStack->PushBack(vNormal);
            }
            if (strstr(pszSubLine, "vt ") != NULL) {
                TVec3* vCoord = new TVec3();
                sscanf(pszSubLine, "vt %f %f %f", &vCoord->x, &vCoord->y, &vCoord->z);
                pTexcoordStack->PushBack(vCoord);
            }
            if (strstr(pszSubLine, "f ") != NULL) {
                uint32* pInidces = new uint32[6];
                sscanf(pszSubLine, "f %lu/%lu %lu/%lu %lu/%lu", &pInidces[0], &pInidces[1], &pInidces[2], &pInidces[3], &pInidces[4], &pInidces[5]);
                pIndexStack->PushBack(pInidces);
            }
            if (strstr(pszSubLine, "mtllib ") != NULL) {
                //bool32 bLoadSuccess = ParseMaterialFile(NULL/*TODO - material fil*/, pMaterialStack);
            }
            if (strstr(pszSubLine, "usemtl ") != NULL) {
                char* pszMaterialName = SOFT_CAST(char*, calloc(nLen + 1, sizeof(char)));
                sscanf(pszSubLine, "usemtl %s\n", pszMaterialName);
                for (uint32 nMat = 0; nMat < pMaterialStack->GetNumElements(); ++nMat) {
                    if (strstr(pszMaterialName, SOFT_CAST(TLoadedMaterial*, pMaterialStack->GetItem(nMat))->pszName) != NULL) {
                        SOFT_CAST(SDSubMesh*, pSubObjectsStack->GetBack())->SetMaterial(SOFT_CAST(TLoadedMaterial*, pMaterialStack->GetItem(nMat))->material);
                    }
                }
            }
            free(pszSubLine);

            pszCurPointer += nLen;
        } else {
            FillSubMesh(pPositionStack, pNormalStack, pTexcoordStack, pIndexStack, SOFT_CAST(SDSubMesh*, pSubObjectsStack->GetBack()));
            ResetStacks(pPositionStack, pNormalStack, pTexcoordStack, pIndexStack);
            bDone = true;
        }
    }

    delete pPositionStack;
    delete pNormalStack;
    delete pTexcoordStack;
    delete pIndexStack;

    pSubObjects = pSubObjectsStack;

    free(pszFileContent);

    return true;
}

bool32 SDMeshParser::ParseMaterialFile(const char* pszMaterialFile, SDStack* pMaterials)
{
    FILE* pFile = fopen(pszMaterialFile, "r");
    if (pFile == NULL) {
        ERROR_MSG("Failed to open material file %s!", pszMaterialFile);
        return false;
    }

    fseek(pFile, 0, SEEK_END);
    int32 nSize = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);
    char* pszFileContent = SOFT_CAST(char*, calloc(nSize+1, sizeof(char)));
    fread(pszFileContent, sizeof(char), nSize, pFile);
    fclose(pFile);

    char* pszCurPointer = pszFileContent;
    bool32 bDone = false;

    TLoadedMaterial curMaterial = TLoadedMaterial();

    while (!bDone) {
        char *pszNewLine = strchr(pszCurPointer, '\n');
        if (pszNewLine != NULL) {
            size_t nLen = pszNewLine - pszCurPointer + 1;
            char* pszSubLine = SOFT_CAST(char*, calloc(nLen+1, 1));
            memcpy(pszSubLine, pszCurPointer, nLen);
            if (strstr(pszSubLine, "newmtl ") != NULL) {
                if (curMaterial.pszName != NULL) {
                    TLoadedMaterial* pMaterial = new TLoadedMaterial();
                    *pMaterial = curMaterial;
                    pMaterials->PushBack(pMaterial);
                    curMaterial = TLoadedMaterial();
                }
                curMaterial.pszName = SOFT_CAST(char*, calloc(nLen, sizeof(char)));
                sscanf(pszSubLine, "newmtl %s\n", curMaterial.pszName);
            }
            if (strstr(pszSubLine, "Ka ") == NULL) {
                sscanf(pszSubLine, "Ka %f %f %f", &curMaterial.material.vKa.x, &curMaterial.material.vKa.y, &curMaterial.material.vKa.z);
            }
            if (strstr(pszSubLine, "Kd ") == NULL) {
                sscanf(pszSubLine, "Kd %f %f %f", &curMaterial.material.vKd.x, &curMaterial.material.vKd.y, &curMaterial.material.vKd.z);
            }
            if (strstr(pszSubLine, "Ks ") == NULL) {
                sscanf(pszSubLine, "Ks %f %f %f", &curMaterial.material.vKs.x, &curMaterial.material.vKs.y, &curMaterial.material.vKs.z);
            }
            if (strstr(pszSubLine, "illum ") == NULL) {
                sscanf(pszSubLine, "illum %ld", &curMaterial.material.nIllum);
            }
            if (strstr(pszSubLine, "Ns ") == NULL) {
                sscanf(pszSubLine, "Ns %f", &curMaterial.material.fNs);
            }
            if (strstr(pszSubLine, "Ni ") == NULL) {
                sscanf(pszSubLine, "Ni %f", &curMaterial.material.fNi);
            }
            if (strstr(pszSubLine, "d ") == NULL) {
                sscanf(pszSubLine, "d %f", &curMaterial.material.fD);
            }
            if (strstr(pszSubLine, "map_Kd ") == NULL) {
                // TODO - texture
            }

            free(pszSubLine);
            pszCurPointer += nLen;
       } else {
            bDone = true;
        }
    }

    free(pszFileContent);

    return true;

}

void SDMeshParser::FillSubMesh(SDStack* pPositionStack, SDStack* pNormalStack, SDStack* pTexcoordStack, SDStack* pIndexStack, SDSubMesh* pSubMesh)
{
    if (pPositionStack->GetNumElements() != pNormalStack->GetNumElements() ||
        pPositionStack->GetNumElements() != pTexcoordStack->GetNumElements() ||
        pTexcoordStack->GetNumElements() != pNormalStack->GetNumElements()) {
        ERROR_MSG("Vertex count mismatch!");
        return;
    }

    TVec3* pPositions = SOFT_CAST(TVec3*, calloc(pPositionStack->GetNumElements(), sizeof(TVec3)));
    TVec3* pNormals = SOFT_CAST(TVec3*, calloc(pNormalStack->GetNumElements(), sizeof(TVec3)));
    TVec3* pTexCoords = SOFT_CAST(TVec3*, calloc(pTexcoordStack->GetNumElements(), sizeof(TVec3)));

    for (uint32 nVertex = 0; nVertex < pPositionStack->GetNumElements(); ++nVertex) {
        pPositions[nVertex] = SOFT_CAST(TVec3*, pPositionStack->GetArray()[nVertex])[0];
        pNormals[nVertex] = SOFT_CAST(TVec3*, pNormalStack->GetArray()[nVertex])[0];
        pTexCoords[nVertex] = SOFT_CAST(TVec3*, pTexcoordStack->GetArray()[nVertex])[0];
    }

    uint32* pIndices = SOFT_CAST(uint32*, calloc(pIndexStack->GetNumElements(), sizeof(uint32)));
    for (uint32 nIndex = 0; nIndex < pIndexStack->GetNumElements(); ++nIndex) {
        pIndices[nIndex] = SOFT_CAST(uint32*, pIndexStack->GetArray()[nIndex])[0];
    }

    SDSubMesh::TSubMeshInfo meshInfo = { pPositionStack->GetNumElements(), pIndexStack->GetNumElements() };

    pSubMesh->Create(&meshInfo);
    pSubMesh->UploadVertexData(pPositions, pNormals, pTexCoords);
    pSubMesh->UploadIndexData(pIndices);

    free(pIndices);
    free(pPositions);
    free(pNormals);
    free(pTexCoords);
}

void SDMeshParser::ResetStacks(SDStack* pPositionStack, SDStack* pNormalStack, SDStack* pTexcoordStack, SDStack* pIndexStack)
{
    for (uint32 nPos = 0; nPos < pPositionStack->GetNumElements(); ++nPos) {
        delete SOFT_CAST(TVec3*, pPositionStack->GetItem(nPos));
    }
    delete pPositionStack;
    pPositionStack = new SDStack();

    for (uint32 nNorm = 0; nNorm < pNormalStack->GetNumElements(); ++nNorm) {
        delete SOFT_CAST(TVec3*, pNormalStack->GetItem(nNorm));
    }
    delete pNormalStack;
    pNormalStack = new SDStack();

    for (uint32 nCoord = 0; nCoord < pTexcoordStack->GetNumElements(); ++nCoord) {
        delete SOFT_CAST(TVec3*, pTexcoordStack->GetItem(nCoord));
    }
    delete pTexcoordStack;
    pTexcoordStack = new SDStack();

    for (uint32 nIndex = 0; nIndex < pIndexStack->GetNumElements(); ++nIndex) {
        delete[] SOFT_CAST(uint32*, pIndexStack->GetItem(nIndex));
    }
    delete pIndexStack;
    pIndexStack = new SDStack();

}
