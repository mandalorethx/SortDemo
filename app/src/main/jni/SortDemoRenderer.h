//
// Created by matt on 5/20/16.
//

#ifndef SORTDEMO_SORTDEMORENDERER_H
#define SORTDEMO_SORTDEMORENDERER_H

#include "SharedDefines.h"
#include "SDMesh.h"
#include "SDPipeline.h"
#include "SDStack.h"

class SortDemoRenderer {
public:
    SortDemoRenderer();
    ~SortDemoRenderer();

    bool32 CreateRenderer(uint32 nWidth, uint32 nHeight);
    bool32 AddMesh(const char* pszBasePath, const char* pszMeshFile);
    void   DrawFrame();
    void   DestroyRenderer();
    void   UpdateViewport(uint32 nWidth, uint32 nHeight);
private:
    uint32     m_nWidth;
    uint32     m_nHeight;
    SDStack    m_meshStack;
    SDPipeline m_pipeline;
    uint32     m_nFrameNum;
    double     m_fStartTime;
    double     m_fLastTime;
};



#endif //SORTDEMO_SORTDEMORENDERER_H
