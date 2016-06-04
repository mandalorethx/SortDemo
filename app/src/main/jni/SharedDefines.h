//
// Created by matt on 5/20/16.
//

#ifndef SORTDEMO_SHAREDDEFINES_H
#define SORTDEMO_SHAREDDEFINES_H

#include <jni.h>
#include <android/log.h>
#include <GLES2/gl2.h>
#include <cstring>
#include <cstdio>

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
    TVec2(float fX, float fY) : x(fX), y(fY) {}
};

struct TVec3
{
    float x;
    float y;
    float z;

    TVec3() : x(0.0), y(0.0), z(0.0) {}
    TVec3(float fX, float fY, float fZ) : x(fX), y(fY), z(fZ) {}
};

struct TVec4
{
    float x;
    float y;
    float z;
    float w;

    TVec4() : x(0.0), y(0.0), z(0.0), w(0.0) {}
    TVec4(float fX, float fY, float fZ, float fW) : x(fX), y(fY), z(fZ), w(fW) {}
};

struct TMat4
{
    TVec4 cX;
    TVec4 cY;
    TVec4 cZ;
    TVec4 cW;

    TMat4() : cX(), cY(), cZ(), cW() {}
};

static inline void ErrorMessage(const char* pszFile, int32 nLine, const char* pszFormat, ...)
{
    va_list vl;
    va_start(vl, pszFormat);

    char pszTmpString[1024];
    vsprintf(pszTmpString, pszFormat, vl);

    va_end(vl);

    LOGE("%s::%ld %s\n", pszFile, nLine, pszTmpString);
};

#define ERROR_MSG(...) ErrorMessage(__FILE__, __LINE__, __VA_ARGS__)

static inline bool32 CheckGL(const char* pszFile, int32 nLine)
{
    GLenum eError = glGetError();
    if (eError != GL_NO_ERROR)
    {
        ErrorMessage(pszFile, nLine, "(0x%X)", eError);
        return false;
    }
    return true;
}

#define CHECKGL CheckGL(__FILE__, __LINE__)

#define SOFT_CAST(type, var) static_cast<type>(var)
#define HARD_CAST(type, var) reinterpret_cast<type>(var)
#define CONST_CAST(type, var) const_cast<type>(var)

static const float PI = 3.141592654;

#define SDMAX(x, y) (x > y ? x : y)
#define SDMIN(x, y) (x < y ? x : y)

struct TMaterialInfo
{
    TVec3 ambient;
    TVec3 diffuse;
    TVec3 specular;
    TVec3 transmittance;
    TVec3 emission;
    float shininess;
    float ior;      // index of refraction
    float dissolve; // 1 == opaque; 0 == fully transparent
    // illumination model (see http://www.fileformat.info/format/material/)
    int32 illum;

    int32 dummy; // Suppress padding warning.

    char* ambient_texname;            // map_Ka
    char* diffuse_texname;            // map_Kd
    char* specular_texname;           // map_Ks
    char* specular_highlight_texname; // map_Ns
    char* bump_texname;               // map_bump, bump
    char* displacement_texname;       // disp
    char* alpha_texname;              // map_d
};



#endif //SORTDEMO_SHAREDDEFINES_H
