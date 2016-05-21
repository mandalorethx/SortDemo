//
// Created by matt on 5/21/16.
//

#ifndef SORTDEMO_SDOBJECT_H
#define SORTDEMO_SDOBJECT_H

#include "SharedDefines.h"

class SDObject
{
public:
    SDObject();
    virtual ~SDObject();
    virtual bool32 Create(void* pInfo) = 0;
    virtual void   Destroy() = 0;
};

#endif //SORTDEMO_SDOBJECT_H
