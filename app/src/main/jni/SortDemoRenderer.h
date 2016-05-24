//
// Created by matt on 5/20/16.
//

#ifndef SORTDEMO_SORTDEMORENDERER_H
#define SORTDEMO_SORTDEMORENDERER_H

#include "SharedDefines.h"

class SortDemoRenderer {
public:
    SortDemoRenderer();
    ~SortDemoRenderer();

    bool32 CreateRenderer(uint32 nWidth, uint32 nHeight);
    void   DrawFrame();
    void   DestroyRenderer();
private:
    uint32 m_nWidth;
    uint32 m_nHeight;
};



#endif //SORTDEMO_SORTDEMORENDERER_H
