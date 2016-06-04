//
// Created by matt on 5/21/16.
//

#ifndef SORTDEMO_SDSTACK_H
#define SORTDEMO_SDSTACK_H

#include "SharedDefines.h"

class SDStack {
public:
    struct TNode
    {
        TNode* pFront;
        TNode* pBack;
        void*  pData;
        size_t nSize;

        TNode() : pFront(NULL), pBack(NULL), pData(NULL), nSize(0) {}
    };

    SDStack();
    ~SDStack();

    void   PushBack(void* pItem, size_t nSize = -1);
    void*  GetBack();
    void*  GetFront();
    void*  GetItem(uint32 nItem);

    void   RemoveBack();
    void   RemoveFront();
    void   RemoveItem(uint32 nItem);

    uint32 GetNumElements();

    void*  GetArray();
private:
    TNode*  m_pBack;
    int32   m_nNumElements;
};


#endif //SORTDEMO_SDSTACK_H
