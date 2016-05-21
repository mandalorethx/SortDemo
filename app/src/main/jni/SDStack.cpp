//
// Created by matt on 5/21/16.
//

#include "SDStack.h"

SDStack::SDStack()
{
    m_nNumElements = 0;
    m_ppArray = NULL;
}
SDStack::~SDStack()
{
    delete[] m_ppArray;
}

void   SDStack::PushBack(void* pItem)
{
    void** ppNewArray = new void*[m_nNumElements+1];
    for (uint32 ii = 0; ii < m_nNumElements; ++ii)
    {
        ppNewArray[ii] = m_ppArray[ii];
    }
    ppNewArray[m_nNumElements] = pItem;
    m_nNumElements++;

    delete[] m_ppArray;

    m_ppArray = ppNewArray;

}

void*  SDStack::GetBack()
{
    return GetItem(m_nNumElements-1);
}

void*  SDStack::GetFront()
{
    return GetItem(0);
}

void*  SDStack::GetItem(uint32 nItem)
{
    return m_ppArray[nItem];
}

void   SDStack::RemoveBack()
{
    RemoveItem(m_nNumElements-1);
}

void   SDStack::RemoveFront()
{
    RemoveItem(0);
}

void   SDStack::RemoveItem(uint32 nItem)
{
    void** ppNewArray = new void*[m_nNumElements-1];
    uint32 nWriteItem = 0;
    for (uint32 ii = 0; ii < m_nNumElements; ++ii)
    {
        if (ii != nItem) {
            ppNewArray[nWriteItem] = m_ppArray[ii];
            nWriteItem++;
        }
    }
    m_nNumElements--;

    delete[] m_ppArray;

    m_ppArray = ppNewArray;
}

uint32 SDStack::GetNumElements()
{
    return m_nNumElements;
}

void** SDStack::GetArray()
{
    return m_ppArray;
}
