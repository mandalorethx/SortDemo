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
    if (pFile == NULL)
    {
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

    while (!bDone)
    {
        char* pszNewLine = strchr(pszCurPointer, '\n');
        if (pszNewLine != NULL)
        {
            size_t nLen = pszNewLine - pszCurPointer + 1;
            char* pszSubLine = SOFT_CAST(char*, calloc(nLen+1, 1));
            memcpy(pszSubLine, pszCurPointer, nLen);

            if (strstr(pszSubLine, "g ") != NULL || strstr(pszSubLine, "o ") != NULL)
            {
                if (pSubObjectsStack->GetNumElements() > 0)
                {
                    FillSubMesh(pPositionStack, pNormalStack, pTexcoordStack, pIndexStack, SOFT_CAST(SDSubMesh*, pSubObjectsStack->GetBack()));
                    ResetStacks(pPositionStack, pNormalStack, pTexcoordStack, pIndexStack);
                }
                SDSubMesh* pSubMesh = new SDSubMesh();
                pSubObjectsStack->PushBack(pSubMesh);
            }
            if (strstr(pszSubLine, "v ") != NULL)
            {
                TVec3* vVertex = new TVec3();
                sscanf(pszSubLine, "v %f %f %f", &vVertex->x, &vVertex->y, &vVertex->z);
                pPositionStack->PushBack(vVertex);
            }
            if (strstr(pszSubLine, "vn ") != NULL)
            {
                TVec3* vNormal = new TVec3();
                sscanf(pszSubLine, "vn %f %f %f", &vNormal->x, &vNormal->y, &vNormal->z);
                pNormalStack->PushBack(vNormal);
            }
            if (strstr(pszSubLine, "vt ") != NULL)
            {
                TVec3* vCoord = new TVec3();
                sscanf(pszSubLine, "vt %f %f %f", &vCoord->x, &vCoord->y, &vCoord->z);
                pTexcoordStack->PushBack(vCoord);
            }
            if (strstr(pszSubLine, "f ") != NULL)
            {
                uint32* pInidces = new uint32[6];
                sscanf(pszSubLine, "f %u/%u %u/%u %u/%u", &pInidces[0], &pInidces[1], &pInidces[2], &pInidces[3], &pInidces[4], &pInidces[5]);
                pIndexStack->PushBack(pInidces);
            }
            if (strstr(pszSubLine, "mtllib ") != NULL)
            {
                bool32 bLoadSuccess = ParseMaterialFile(NULL/*TODO - material fil*/, pMaterialStack);
            }
            if (strstr(pszSubLine, "usemtl ") != NULL)
            {
                char* pszMaterialName = SOFT_CAST(char*, calloc(nLen + 1, sizeof(char)));
                sscanf(pszSubLine, "usemtl %s\n", pszMaterialName);
                for (uint32 nMat = 0; nMat < pMaterialStack->GetNumElements(); ++nMat)
                {
                    if (strstr(pszMaterialName, SOFT_CAST(TLoadedMaterial*, pMaterialStack->GetItem(nMat))->pszName) != NULL)
                    {
                        SOFT_CAST(SDSubMesh*, pSubObjectsStack->GetBack())->SetMaterial(SOFT_CAST(TLoadedMaterial*, pMaterialStack->GetItem(nMat))->material);
                    }
                }
            }
            free(pszSubLine);

            pszCurPointer += nLen;
        }
        else
        {
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

    return true;
}

bool32 SDMeshParser::ParseMaterialFile(const char* pszMaterialFile, SDStack* pMaterials)
{

}

void SDMeshParser::FillSubMesh(SDStack* pPositionStack, SDStack* pNormalStack, SDStack* pTexcoordStack, SDStack* pIndexStack, SDSubMesh* pSubMesh)
{

}

void SDMeshParser::ResetStacks(SDStack* pPositionStack, SDStack* pNormalStack, SDStack* pTexcoordStack, SDStack* pIndexStack)
{

}
