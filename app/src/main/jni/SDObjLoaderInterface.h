//
// Created by matt on 6/1/16.
//

#ifndef SORTDEMO_SDOBJLOADERINTERFACE_H
#define SORTDEMO_SDOBJLOADERINTERFACE_H

#include "SharedDefines.h"
#include "SDStack.h"

namespace SDObjLoaderInterface {
    struct TMeshInfo
    {
        SDStack* pPositions;
        SDStack* pNormals;
        SDStack* pCoords;
        SDStack* pMaterials;
    };

    bool32 LoadMeshFile(const char* pszPath, const char* pszFileName, SDStack* pMeshes, SDStack* pMaterials);

};


#endif //SORTDEMO_SDOBJLOADERINTERFACE_H
