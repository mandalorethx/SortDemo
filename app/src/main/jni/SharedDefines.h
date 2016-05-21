//
// Created by matt on 5/20/16.
//

#ifndef SORTDEMO_SHAREDDEFINES_H
#define SORTDEMO_SHAREDDEFINES_H

#include <jni.h>
#include <android/log.h>
#include <GLES2/gl2.h>
#include <cstring>

#define  LOG_TAG    "SortDemoRenderer"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

typedef unsigned long uint32;
typedef long int32;
typedef unsigned short uint16;
typedef short int16;
typedef unsigned char uint8;
typedef char int8;
typedef uint32 bool32;

struct TVec2
{
    float x;
    float y;

    TVec2() : x(0.0), y(0.0) {}
};

struct TVec3
{
    float x;
    float y;
    float z;

    TVec3() : x(0.0), y(0.0), z(0.0) {}
};

struct TVec4
{
    float x;
    float y;
    float z;
    float w;

    TVec4() : x(0.0), y(0.0), z(0.0), w(0.0) {}
};

struct TMat4
{
    TVec4 cX;
    TVec4 cY;
    TVec4 cZ;
    TVec4 cW;

    TMat4() : cX(), cY(), cZ(), cW() {}
};

static inline bool32 CheckGL(const char* pszFile, int32 nLine)
{
    GLenum eError = glGetError();
    if (eError != GL_NO_ERROR)
    {
        LOGE("%s::%ld (0x%X)\n", pszFile, nLine, eError);
        return false;
    }
    return true;
}

#define CHECKGL CheckGL(__FILE__, __LINE__)

#define SOFT_CAST(type, var) static_cast<type>(var)
#define HARD_CAST(type, var) reinterpret_cast<type>(var)
#define CONST_CASE(type, var) const_cast<type>(var)

#endif //SORTDEMO_SHAREDDEFINES_H
