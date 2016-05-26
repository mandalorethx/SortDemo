//
// Created by matt on 5/23/16.
//

#ifndef SORTDEMO_SDMESHPARSER_H
#define SORTDEMO_SDMESHPARSER_H

#include "SharedDefines.h"
#include "SDStack.h"
#include "SDSubMesh.h"

class SDMeshParser {
public:
    struct TLoadedMaterial
    {
        SDSubMesh::TMaterial material;
        char*                pszName;
        TLoadedMaterial() : material(), pszName(NULL) {}
    };
    static bool32 ParseMeshFile(const char* pszMeshFile, SDStack* pSubObjects);
private:
    static bool32 ParseMaterialFile(const char* pszMaterialFile, SDStack* pMaterials);
    static void FillSubMesh(SDStack* pPositionStack, SDStack* pNormalStack, SDStack* pTexcoordStack, SDStack* pIndexStack, SDSubMesh* pSubMesh);
    static void ResetStacks(SDStack* pPositionStack, SDStack* pNormalStack, SDStack* pTexcoordStack, SDStack* pIndexStack);
};


#endif //SORTDEMO_SDMESHPARSER_H
