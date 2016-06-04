//
// Created by matt on 5/30/16.
//

#ifndef SORTDEMO_SDMESHUTILS_H
#define SORTDEMO_SDMESHUTILS_H

#include "SharedDefines.h"

class SDMeshUtils {
public:
    static void SetIdentity(TMat4* pMat);
    static void MultiplyMat(TMat4 lfm, TMat4 rhm, TMat4* pRes);
    static void MultiplyVec3(TMat4 mat, TVec3 vec, TVec4* pRes);
    static void MultiplyVec4(TMat4 mat, TVec4 vec, TVec4* pRes);
    static void BuildScaleMatrix(float fX, float fY, float fZ, TMat4* pRes);
    static void BuildRotatatioMatrix(float fAngle, float fX, float fY, float fZ, TMat4* pRes);

};


#endif //SORTDEMO_SDMESHUTILS_H
