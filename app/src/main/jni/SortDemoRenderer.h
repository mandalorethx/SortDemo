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
    bool32 AddMesh(const char* pszMeshFile);
    void   DrawFrame();
    void   DestroyRenderer();
private:
    uint32     m_nWidth;
    uint32     m_nHeight;
    SDStack    m_meshStack;
    SDPipeline m_pipeline;
};



#endif //SORTDEMO_SORTDEMORENDERER_H
