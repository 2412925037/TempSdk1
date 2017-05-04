#include "cBase/system_properties.h"
#include "cBase/log.h"
#include "cBase/jni.h"
#include "cBase/stdio.h"
#include "cBase/stdlib.h"
#include "cBase/string.h"
#include "cBase/unistd.h"

#define   LOG_TAG "Native"
#define   VERSION 1
#define   logShow false

#define   LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define   LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)