//
// Created by matt on 5/21/16.
//

#include "SDStack.h"

SDStack::SDStack() {
    m_nNumElements = 0;
    m_pBack = NULL;
}

SDStack::~SDStack() {
    if(m_pBack != NULL) {
        while (m_nNumElements > 0) {
            RemoveBack();
        }
    }
}

void   SDStack::PushBack(void* pItem, size_t nSize /*= -1*/) {
    TNode* pNewNode = SOFT_CAST(TNode*, calloc(sizeof(TNode), 1));
    pNewNode->pFront = m_pBack;

    if (nSize == -1) {
//        pNewNode->nSize = sizeof(void*);
//        pNewNode->pData = calloc(nSize, 1);
//        memcpy(pNewNode->pData, &pItem, nSize);
        pNewNode->nSize = -1;
        pNewNode->pData = pItem;
    } else {
        pNewNode->nSize = nSize;
        pNewNode->pData = calloc(nSize, 1);
        memcpy(pNewNode->pData, pItem, nSize);
    }


    if (m_pBack != NULL) {
        m_pBack->pBack = pNewNode;
    }
    m_pBack = pNewNode;
    m_nNumElements++;
}

void*  SDStack::GetBack() {
    return GetItem(m_nNumElements-1);
}

void*  SDStack::GetFront() {
    return GetItem(0);
}

void*  SDStack::GetItem(uint32 nItem) {
    TNode* pCurNode = m_pBack;
    uint32 nCount = m_nNumElements - 1;
    while (pCurNode != NULL && nCount > nItem) {
        pCurNode = pCurNode->pFront;
        nCount--;
    }

    if (pCurNode == NULL) {
        ERROR_MSG("Stack: No element %d to get!", nItem);
        return NULL;
    }

    return pCurNode->pData;
}

void   SDStack::RemoveBack() {
    RemoveItem(m_nNumElements-1);
}

void   SDStack::RemoveFront() {
    RemoveItem(0);
}

void   SDStack::RemoveItem(uint32 nItem) {
    TNode* pCurNode = m_pBack;
    uint32 nCount = m_nNumElements-1;
    while (pCurNode != NULL && nCount > nItem) {
        pCurNode = pCurNode->pFront;
        nCount--;
    }

    if (pCurNode == NULL) {
        ERROR_MSG("Stack: No element %d to remove!", nItem);
        return;
    }

    TNode* pTmp = pCurNode->pFront;
    if (pCurNode->pBack != NULL) {
        pCurNode->pBack->pFront = pTmp;
    }

    if (pTmp != NULL) {
        pTmp->pBack = pCurNode->pBack;
    }
    if (pCurNode->nSize != -1) {
        free(pCurNode->pData);
    }

    free(pCurNode);
    m_nNumElements--;
}

uint32 SDStack::GetNumElements() {
    return m_nNumElements;
}

void* SDStack::GetArray() {
    size_t nTotalSize = 0;
    TNode* pCurNode = m_pBack;
    while (pCurNode != NULL) {
        if (pCurNode->nSize == -1) {
            nTotalSize += sizeof(void*);
        } else {
            nTotalSize += pCurNode->nSize;
        }
        pCurNode = pCurNode->pFront;
    }

    uint8* ppArray = SOFT_CAST(uint8*, calloc(nTotalSize, 1));
    size_t nOffset = 0;
    pCurNode = m_pBack;
    while (pCurNode != NULL) {
        size_t nCurSize = pCurNode->nSize;
        if (nCurSize = -1) {
            nCurSize = sizeof(void*);
        }
        memcpy(ppArray + nOffset, pCurNode->pData, nCurSize);
        pCurNode = pCurNode->pFront;
    }

    return ppArray;
}
