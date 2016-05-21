//
// Created by matt on 5/20/16.
//

#ifndef SORTDEMO_SHAREDDEFINES_H
#define SORTDEMO_SHAREDDEFINES_H

#include <jni.h>
#include <android/log.h>

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

#define SOFT_CAST(type, var) static_cast<type>(var)
#define HARD_CAST(type, var) reinterpret_cast<type>(var)
#define CONST_CASE(type, var) const_cast<type>(var)

#endif //SORTDEMO_SHAREDDEFINES_H
