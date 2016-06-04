//
// Created by matt on 5/30/16.
//

#include "SDMeshUtils.h"

void SDMeshUtils::SetIdentity(TMat4* pMat) {
    memset(pMat, 0, sizeof(TMat4));
    pMat->cX.x = 1.f;
    pMat->cY.y = 1.f;
    pMat->cZ.z = 1.f;
    pMat->cW.w = 1.f;
}

void SDMeshUtils::MultiplyMat(TMat4 lfm, TMat4 rhm, TMat4* pRes) {

}

void SDMeshUtils::MultiplyVec3(TMat4 mat, TVec3 vec, TVec4* pRes) {
    TVec4 vNewVec = TVec4();
    vNewVec.x = vec.x;
    vNewVec.y = vec.y;
    vNewVec.z = vec.z;

    MultiplyVec4(mat, vNewVec, pRes);
}

void SDMeshUtils::MultiplyVec4(TMat4 mat, TVec4 vec, TVec4* pRes) {

}

void SDMeshUtils::BuildScaleMatrix(float fX, float fY, float fZ, TMat4* pRes) {
    memset(pRes, 0, sizeof(TMat4));
    pRes->cX.x = fX;
    pRes->cY.y = fY;
    pRes->cZ.z = fZ;
    pRes->cW.w = 1.f;
}

void SDMeshUtils::BuildRotatatioMatrix(float fAngle, float fX, float fY, float fZ, TMat4* pRes) {

}
