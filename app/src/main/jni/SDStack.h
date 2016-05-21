//
// Created by matt on 5/21/16.
//

#ifndef SORTDEMO_SDSTACK_H
#define SORTDEMO_SDSTACK_H

#include "SharedDefines.h"

class SDStack {
public:
    SDStack();
    ~SDStack();

    void   PushBack(void* pItem);
    void*  GetBack();
    void*  GetFront();
    void*  GetItem(uint32 nItem);

    void   RemoveBack();
    void   RemoveFront();
    void   RemoveItem(uint32 nItem);

    uint32 GetNumElements();

    void** GetArray();
private:
    void** m_ppArray;
    uint32 m_nNumElements;
};


#endif //SORTDEMO_SDSTACK_H
