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
    static bool32 ParseMeshFile(const char* pszBasePath, const char* pszMeshFile, SDStack* pSubObjects);
private:
    static void FillSubMesh(SDStack* pPositionStack, SDStack* pNormalStack, SDStack* pTexcoordStack, SDSubMesh* pSubMesh);
};


#endif //SORTDEMO_SDMESHPARSER_H
