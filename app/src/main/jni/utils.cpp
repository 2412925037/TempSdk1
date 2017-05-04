//
// Created by lidawei on 2017/3/30.
//

#include "utils.h"
char *jstringTostring(JNIEnv *env, jstring jstr) {
//    char *rtn = NULL;
//    jclass clsstring = env->FindClass("java/lang/String");
//    jstring strencode = env->NewStringUTF("utf-8");
//    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
//    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
//    jsize alen = env->GetArrayLength(barr);
//    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
//    if (alen > 0) {
//        rtn = (char *) malloc(alen + 1);
//
//        memcpy(rtn, ba, alen);
//        rtn[alen] = 0;
//    }
//    env->ReleaseByteArrayElements(barr, ba, 0);
//    return rtn;
    if (jstr == NULL) {
        return NULL;
    }
    char *rtn = "";
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);

    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    if (env->ExceptionCheck() == JNI_TRUE) {
        env->ExceptionDescribe();
        env->ExceptionClear();
        return "";
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    env->DeleteLocalRef(barr);
    env->DeleteLocalRef(clsstring);
    env->DeleteLocalRef(strencode);
    return rtn;
}

jstring stoJstring(JNIEnv *env, const char *pat) {
//    jclass strClass = env->FindClass("java/lang/String");
//    jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
//    jbyteArray bytes = env->NewByteArray(strlen(pat));
//    env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte *) pat);
//    jstring encoding = env->NewStringUTF("utf-8");
//    return (jstring) env->NewObject(strClass, ctorID, bytes, encoding);

    if (NULL == pat) {
        return NULL;
    }
    jclass strClass = env->FindClass("java/lang/String");
    jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    jbyteArray bytes = env->NewByteArray(strlen(pat));
    env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte *) pat);
    jstring encoding = env->NewStringUTF("utf-8");
    jstring ret = (jstring) env->NewObject(strClass, ctorID, bytes, encoding);

    env->DeleteLocalRef(strClass);
    env->DeleteLocalRef(bytes);
    env->DeleteLocalRef(encoding);
    return ret;
}

int indexOf(char *str1, char *str2) {
    char *p = str1;
    int i = 0;
    p = strstr(str1, str2);
    if (p == NULL)
        return -1;
    else {
        while (str1 != p) {
            str1++;
            i++;
        }
    }
    return i;
}


jint indexOf(JNIEnv *env, jstring str, jstring str1) {
    jclass stringClazz = env->FindClass("java/lang/String");
    jmethodID indexOf = env->GetMethodID(stringClazz, "indexOf",
                                         "(Ljava/lang/String;)I");
    jint temp = env->CallIntMethod(str, indexOf, str1);
    return temp;
}


void substring(char *dest, char *src, int start, int end) {
    int i = start;
    if (start > strlen(src))return;
    if (end > strlen(src))
        end = strlen(src);
    while (i < end) {
        dest[i - start] = src[i];
        i++;
    }
    dest[i - start] = '\0';
    return;
}

void replaceFirst(char *str1, char *str2, char *str3) {
    char str4[strlen(str1) + 1];
    char *p;
    strcpy(str4, str1);
    if ((p = strstr(str1, str2)) != NULL)/*p指向str2在str1中第一次出现的位置*/
    {
        while (str1 != p && str1 != NULL)/*将str1指针移动到p的位置*/
        {
            str1++;
        }
        str1[0] = '\0';/*将str1指针指向的值变成/0,以此来截断str1,舍弃str2及以后的内容，只保留str2以前的内容*/
        strcat(str1, str3);/*在str1后拼接上str3,组成新str1*/
        strcat(str1, strstr(str4, str2) +
                     strlen(str2));/*strstr(str4,str2)是指向str2及以后的内容(包括str2),strstr(str4,str2)+strlen(str2)就是将指针向前移动strlen(str2)位，跳过str2*/
    }
}

void str_trim_crlf(char *str) //去除\r\n
{
    char *p = &str[strlen(str) - 1];
    while (*p == '\r' || *p == '\n')
        *p-- = '\0';

}

char *trimHead(char *src) {
    int i = 0;
    char *begin = src;
    while (src[i] == ' ') {
        begin++;
        i++;
    }
    return begin;
}

//增加

jstring charToJstring(JNIEnv *env, const char *pat) {
    if (NULL == pat) {
        return NULL;
    }
    jclass strClass = env->FindClass("java/lang/String");
    jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    jbyteArray bytes = env->NewByteArray(strlen(pat));
    env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte *) pat);
    jstring encoding = env->NewStringUTF("utf-8");
    jstring ret = (jstring) env->NewObject(strClass, ctorID, bytes, encoding);

    env->DeleteLocalRef(strClass);
    env->DeleteLocalRef(bytes);
    env->DeleteLocalRef(encoding);
    return ret;
}


char *jstringToChar(JNIEnv *env, jstring jstr) {
    if (jstr == NULL) {
        return NULL;
    }
    char *rtn = "";
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);

    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    if (env->ExceptionCheck() == JNI_TRUE) {
        env->ExceptionDescribe();
        env->ExceptionClear();
        return "";
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    env->DeleteLocalRef(barr);
    env->DeleteLocalRef(clsstring);
    env->DeleteLocalRef(strencode);
    return rtn;
}

jstring toJstring(JNIEnv *env, jobject obj) {
    jclass objClazz = env->FindClass("java/lang/String");
    jmethodID toStringMid = env->GetStaticMethodID(objClazz, "valueOf",
                                                   "(Ljava/lang/Object;)Ljava/lang/String;");

    jobject ret = env->CallStaticObjectMethod(objClazz, toStringMid, obj);
    env->DeleteLocalRef(objClazz);
    return (jstring) ret;
}

jstring jintToJstring(JNIEnv *env, jint obj) {
    jclass objClazz = env->FindClass("java/lang/String");
    jmethodID toStringMid = env->GetStaticMethodID(objClazz, "valueOf",
                                                   "(I)Ljava/lang/String;");
    jobject ret = env->CallStaticObjectMethod(objClazz, toStringMid, obj);
    env->DeleteLocalRef(objClazz);
    return (jstring) ret;
}

jstring jlongToJstring(JNIEnv *env, jlong obj) {
    jclass objClazz = env->FindClass("java/lang/String");
    jmethodID toStringMid = env->GetStaticMethodID(objClazz, "valueOf",
                                                   "(J)Ljava/lang/String;");
    jobject ret = env->CallStaticObjectMethod(objClazz, toStringMid, obj);
    env->DeleteLocalRef(objClazz);
    return (jstring) ret;
}