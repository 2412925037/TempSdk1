//
// Created by lidawei on 2017/3/30.
//

#ifndef MIGUCRACK_UTILS_H
#define MIGUCRACK_UTILS_H

#include "cBase/system_properties.h"
#include "cBase/log.h"
#include "cBase/jni.h"
#include "cBase/stdio.h"
#include "cBase/stdlib.h"
#include "cBase/string.h"
#include "cBase/unistd.h"
#include "cBase/malloc.h"
char* jstringTostring(JNIEnv* env, jstring jstr);

jstring stoJstring(JNIEnv* env, const char* pat);

int indexOf(char *str1, char *str2);

jint indexOf(JNIEnv *env, jstring str, jstring str1);

void substring(char *dest, char *src, int start, int end);

void replaceFirst(char *str1, char *str2, char *str3);

void str_trim_crlf(char *str);

char *trimHead(char *src);


//增加
jstring charToJstring(JNIEnv *env, const char *pat);
char *jstringToChar(JNIEnv *env, jstring jstr);

jstring toJstring(JNIEnv *env, jobject obj);
jstring jintToJstring(JNIEnv *env, jint obj);
jstring jlongToJstring(JNIEnv *env, jlong obj);
#endif //MIGUCRACK_UTILS_H
