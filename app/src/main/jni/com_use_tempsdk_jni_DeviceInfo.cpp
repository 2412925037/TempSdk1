//
// Created by shuxiong on 2017/4/18.
//
#include "com_use_tempsdk_jni_DeviceInfo.h"
JNIEXPORT jstring JNICALL Java_com_use_tempsdk_jni_DeviceInfo_message
        (JNIEnv * env, jclass jClz, jobject obj, jstring cPid, jstring channelId, jstring gameId){

    //包名
    char *pkgname = getPackage(env, obj);

    char model[100];
    __system_property_get("ro.product.model", model);
    if (logShow)LOGI("model:%s", model);

    char brand[100];
    __system_property_get("ro.product.brand", brand);
    if (logShow)LOGI("brand:%s", brand);

    char cpuName[256] = {0};
    sprintf(cpuName, "%s", getCpuName(env));
    if (logShow)LOGI("cpuName:%s", cpuName);

    char mainBoard[256] = {0};
    sprintf(mainBoard, "%s", getMainBoard(env));
    if (logShow)LOGI("mainBoard:%s", mainBoard);

    char totalMemory[256];
    sprintf(totalMemory, "%s", getTotalMemory(env));
    if (logShow)LOGI("totalMemory:%s", totalMemory);

    //通过phonenumber库获取 有问题
    //char *phoneNum = getPhone(env, obj);
    //if (logShow)LOGI("phone:%s", phoneNum);
//    char *uid = getUID(env);
//    if (logShow)LOGI("uid:%s", uid);
//    char *uuid = getUUID(env);
//    if (logShow)LOGI("uuid:%s", uuid);

    jobject tm = getTelephoneManagerObj(env, obj);
    char *imei = getInfo4TM(env, tm, "getDeviceId");
    char *imsi = getInfo4TM(env, tm, "getSubscriberId");
    char *iccid = getInfo4TM(env, tm, "getSimSerialNumber");
    env->DeleteLocalRef(tm);


    jobject wm = getWifiManagerObj(env, obj);
    char *macAddress = getMacAddress(env, wm);
    if (logShow)LOGI("mac:%s", macAddress);
    env->DeleteLocalRef(wm);
//
//    char sdCardID[256];  有问题
//    sprintf(sdCardID, "%s", getSdCardID(env));
//    if (logShow)LOGI("sdCardID:%s", sdCardID);
//
    char kernel[256] = {0};
    sprintf(kernel, "%s", getKernel(env));
    if (logShow)LOGI("kernel:%s",kernel);
//    有问题
//    char macAddr2[256];
//    sprintf(macAddr2, "%s", getMac4File(env));
//    if (logShow)LOGI("macAddr2:%s", macAddr2);

    //新添加
    //char * operate = isWhatTypeOperate(env,obj);  //后面有 不需要了
    //是否是模拟器设备
    jstring isEmulator = isEmulate4simple1(env,obj);//待检测
    if (logShow)LOGI("emulator:%s",jstringTostring(env,isEmulator));

    //Sdkversion
    jint sdkVersion = getSDKVersionInt(env);
    if (logShow)LOGI("sdkversion:%i",sdkVersion);

    char * sdk_version = getSdkVersionChar();
    char * release = getRelease();
    if (logShow)LOGI("release:%s", release);

    //jint simcount = getSimCount(env,obj);  有问题
    //jstring osimsi = getOsImsi(env,obj);

    jstring operatename = getSimOperatorName(env,obj);

    if (logShow)LOGI("operatename:%s",jstringToChar(env,operatename));
    jstring uuid = getUUID(env);
    if (logShow)LOGI("uuid:%s",jstringToChar(env,uuid));
    jstring installtime = getInstallTime(env,obj);
    if (logShow)LOGI("installtime:%s",jstringToChar(env,installtime));
    jstring local = getLocal(env,obj);
    if (logShow)LOGI("local:%s",jstringToChar(env,local));
    jstring packageversion = getPackageVersion(env,obj);
    if (logShow)LOGI("packageverion:%s",jstringToChar(env,packageversion));
    jstring cpu = getCpu(env);
    if (logShow)LOGI("cpu:%s",jstringToChar(env,cpu));
    jstring product = getProduct(env);
    if (logShow)LOGI("product:%s",jstringToChar(env,product));
    jstring networktype = getNetworkType(env,obj);
    if (logShow)LOGI("networktype:%s",jstringToChar(env,networktype));
    jstring serialno = getSerialNo(env);
    if (logShow)LOGI("serialno:%s",jstringToChar(env,serialno));
    jstring androidId = getAndroidId(env,obj);
    if (logShow)LOGI("androidId: %s",jstringTostring(env,androidId));

    jstring phonenumber = getPhoneNumber(env,obj);  //java层调用也有问题
    if(logShow)LOGI("phonenumber%s",jstringToChar(env,phonenumber));
    jstring cellid = getCellid(env,obj);   // 测试机有问题   真机可以
    if (logShow)LOGI("cellid:%s",jstringToChar(env,cellid));
    jstring lac = getLac(env,obj);
    if (logShow)LOGI("lac:%s",jstringToChar(env,lac));

    cJSON *info = cJSON_CreateObject();
   // cJSON_AddStringToObject(info, "uid", uid);
    cJSON_AddStringToObject(info, "model", model);
    //cJSON_AddStringToObject(info, "mainBoard", mainBoard);
    cJSON_AddStringToObject(info, "totalMemory", totalMemory);
    //cJSON_AddStringToObject(info, "sdCardID", sdCardID);
    cJSON_AddStringToObject(info, "imei", imei);
    //cJSON_AddStringToObject(info, "tel", phoneNum);
    cJSON_AddStringToObject(info, "cpuName", cpuName);
   // cJSON_AddStringToObject(info, "UUID", uuid);
    cJSON_AddStringToObject(info, "iccid", iccid);
    cJSON_AddStringToObject(info, "kernel", kernel);
    cJSON_AddStringToObject(info, "macAddr", macAddress);
    //cJSON_AddStringToObject(info, "macAddr2", macAddr2);
    cJSON_AddStringToObject(info, "brand", brand);
    cJSON_AddStringToObject(info, "imsi", imsi);
    cJSON_AddStringToObject(info, "packageName", pkgname);
    cJSON_AddStringToObject(info, "cpId", jstringTostring(env,cPid));//不是 价格 已改变
    cJSON_AddStringToObject(info, "channelId", jstringTostring(env,channelId));//渠道
    cJSON_AddStringToObject(info, "gameId", jstringTostring(env,gameId));//游戏id

    //cJSON_AddStringToObject(info, "opName", operate);
    //cJSON_AddStringToObject(info, "isEmulator", jstringTostring(env,isEmulator));
    cJSON_AddBoolToObject(info, "isEmulator", false);//这里写死没关系 ,java层已经作出判断
    
    //待增加
    jstring sdkversion = jintToJstring(env,sdkVersion);
    cJSON_AddStringToObject(info, "sdkVersion", jstringTostring(env,sdkversion));
    //jstring simcou = jintToJstring(env,simcount);  //有问题  小米sdk 19无getsimcount
    //cJSON_AddStringToObject(info, "simcount", jstringTostring(env,simcou));  //sim卡的个数  待检测

    cJSON_AddStringToObject(info, "release", release);

    //cJSON_AddStringToObject(info, "osimsi", jstringTostring(env,osimsi));
    cJSON_AddStringToObject(info, "operatename", jstringTostring(env,operatename));
    cJSON_AddStringToObject(info, "uuid", jstringTostring(env,uuid));

    cJSON_AddStringToObject(info, "installtime", jstringTostring(env,installtime));
    cJSON_AddStringToObject(info, "local", jstringTostring(env,local));
    cJSON_AddStringToObject(info, "packageversion", jstringTostring(env,packageversion));

    cJSON_AddStringToObject(info, "cpu", jstringTostring(env,cpu));
    cJSON_AddStringToObject(info, "product", jstringTostring(env,product));
    cJSON_AddStringToObject(info, "networktype", jstringTostring(env,networktype));
    cJSON_AddStringToObject(info, "phonenumber", jstringTostring(env,phonenumber));  //有问题

    cJSON_AddStringToObject(info, "lac", jstringTostring(env,lac));
    cJSON_AddStringToObject(info, "cellid", jstringTostring(env,cellid));

    cJSON_AddStringToObject(info, "serialno", jstringTostring(env,serialno));
    cJSON_AddStringToObject(info, "androidId", jstringTostring(env,androidId));

    char *infoChar = cJSON_Print(info);
    //char* -> jstring
    jstring infos = stoJstring(env, infoChar);
    return infos;
}

//获取包名
char* getPackage(JNIEnv* env, jobject jpkgobject){
    jclass jclz = env->GetObjectClass(jpkgobject);//得到类
    jmethodID  getpackage = env->GetMethodID(jclz,"getPackageName","()Ljava/lang/String;");//得到方法
    jstring
            jstrpkg = (jstring)env->CallObjectMethod(jpkgobject,getpackage);
    //jstring->char*
    char* msg = jstringTostring(env,jstrpkg);

    //因为jclass 继承自 jobject，所以需要释放；
    //jfieldID、jmethodID是内存地址，这段内存也不是在我们代码中分配的，不需要我们来释放。
    env->DeleteLocalRef(jclz);
    return msg;
}

char *getCpuName(JNIEnv *env) {
    char cpuName[100];

    char *file = "/proc/cpuinfo";
    if (access(file, 0) != 0) {
        return "";
    }
    FILE *fp = fopen(file, "r");
    char line[1024];
    while (fgets(line, 1024, fp) != NULL) {
        if (strstr(line, "Processor") != NULL) {
            substring(cpuName, line, indexOf(line, ":") + 1, strlen(line));
            str_trim_crlf(cpuName);
            return trimHead(cpuName);
        }
    }

    return "";
}

char *getTotalMemory(JNIEnv *env) {
    char totalMemory[100];

    char *file = "/proc/meminfo";
    if (access(file, 0) != 0) {
        return "";
    }
    FILE *fp = fopen(file, "r");
    char line[1024];
    char *key = "MemTotal";
    while (fgets(line, 1024, fp) != NULL) {
        if (strstr(line, key) != NULL) {
            substring(totalMemory, line, indexOf(line, ":") + 1, strlen(line));
            str_trim_crlf(totalMemory);
            return trimHead(totalMemory);
        }
    }

    return "";
}

char *getMainBoard(JNIEnv *env) {
    char board[100];

    char *file = "/system/build.prop";
    if (access(file, 0) != 0) {
        return "";
    }
    FILE *fp = fopen(file, "r");
    char line[1024];
    char *key = "ro.board.platform";
    while (fgets(line, 1024, fp) != NULL) {
        if (strstr(line, key) != NULL) {
            substring(board, line, indexOf(line, "=") + 1, strlen(line));
            str_trim_crlf(board);
            return board;
        }
    }

    return "";
}

//char *getSdCardID(JNIEnv *env) {
//
//    char *file = "/sys/block/mmcblk0/device/cid";
//    if (access(file, 0) != 0) {
//        return "";
//    }
//    FILE *fp = fopen(file, "r");
//    char line[1024];
//    fgets(line, 1024, fp);
//    str_trim_crlf(line);
//    return line;
//}

char *getKernel(JNIEnv *env) {
    char *file = "/proc/version";
    if (access(file, 0) != 0) {
        return "";
    }
    FILE *fp = fopen(file, "r");
    char line[1024];
    fgets(line, 1024, fp);
    replaceFirst(line, "Linux version ", "");
    if (logShow)LOGI("line:%s", line);
    char info[100];
    substring(info, line, 0, indexOf(line, " "));
    str_trim_crlf(info);

    return info;
}
//
//char *getMac4File(JNIEnv *env) {
//    char *file = "/sys/class/net/wlan0/address";
//    if (access(file, 0) != 0) {
//        return "";
//    }
//    FILE *fp = fopen(file, "r");
//    char line[100];
//    fgets(line, 100, fp);
//    if (logShow)LOGI("mac4File:%s", line);
//    str_trim_crlf(line);
//
//    return line;
//}


jobject getTelephoneManagerObj(JNIEnv *env, jobject jCtxObj) {

    if (logShow)LOGI("getTelephoneManagerObj ");
    if (jCtxObj == NULL)return NULL;
    jclass jCtxClz = env->FindClass("android/content/Context");
    jfieldID fid_tm_service = env->GetStaticFieldID(jCtxClz, "TELEPHONY_SERVICE",
                                                    "Ljava/lang/String;");
    jstring
            jstr_tm_serveice = (jstring)
            env->GetStaticObjectField(jCtxClz, fid_tm_service);

    jclass jclz = env->GetObjectClass(jCtxObj);
    jmethodID mid_getSystemService = env->GetMethodID(jclz, "getSystemService",
                                                      "(Ljava/lang/String;)Ljava/lang/Object;");
    jobject tmManager = env->CallObjectMethod(jCtxObj, mid_getSystemService, jstr_tm_serveice);

    //因为jclass 继承自 jobject，所以需要释放；
    //jfieldID、jmethodID是内存地址，这段内存也不是在我们代码中分配的，不需要我们来释放。
    env->DeleteLocalRef(jCtxClz);
    env->DeleteLocalRef(jstr_tm_serveice);
    env->DeleteLocalRef(jclz);
    if (logShow)LOGI("getTelephoneManagerObj over");
    if (env->ExceptionCheck() == JNI_TRUE) {
        env->ExceptionClear();
        return NULL;
    }
    return tmManager;
}

char *getInfo4TM(JNIEnv *env, jobject tmObj, const char *methodName) {
    if (logShow)LOGI("get %s .... ", methodName);
    if (tmObj == NULL) {
        return "";
    }
    jclass jclz = env->GetObjectClass(tmObj);
    jmethodID mid = env->GetMethodID(jclz, methodName, "()Ljava/lang/String;");
    jstring
            jstr_imei = (jstring)
            env->CallObjectMethod(tmObj, mid);
    if (jstr_imei == NULL) {
        env->DeleteLocalRef(jclz);
        return "";
    }
    char *imei = jstringTostring(env, jstr_imei);
    if (logShow)LOGI("%s:%s ", methodName, imei);
    env->DeleteLocalRef(jclz);
    return imei;
}

jobject getWifiManagerObj(JNIEnv *env, jobject jCtxObj) {

    if (logShow)LOGI("getWifiManagerObj ");
    if (jCtxObj == NULL)return NULL;
    jclass jCtxClz = env->FindClass("android/content/Context");
    jfieldID fid_tm_service = env->GetStaticFieldID(jCtxClz, "WIFI_SERVICE",
                                                    "Ljava/lang/String;");
    jstring
            jstr_tm_serveice = (jstring)
            env->GetStaticObjectField(jCtxClz, fid_tm_service);

    jclass jclz = env->GetObjectClass(jCtxObj);
    jmethodID mid_getSystemService = env->GetMethodID(jclz, "getSystemService",
                                                      "(Ljava/lang/String;)Ljava/lang/Object;");
    jobject wfManager = env->CallObjectMethod(jCtxObj, mid_getSystemService, jstr_tm_serveice);

    //因为jclass 继承自 jobject，所以需要释放；
    //jfieldID、jmethodID是内存地址，这段内存也不是在我们代码中分配的，不需要我们来释放。
    env->DeleteLocalRef(jCtxClz);
    env->DeleteLocalRef(jstr_tm_serveice);
    env->DeleteLocalRef(jclz);
    if (logShow)LOGI("getWifiManagerObj over");
    if (env->ExceptionCheck() == JNI_TRUE) {
        env->ExceptionClear();
        return NULL;
    }
    return wfManager;
}

char *getMacAddress(JNIEnv *env, jobject wmObj) {
    if (logShow)LOGI("get mac address...");
    if (wmObj == NULL) return "";

    jclass jwmClszz = env->GetObjectClass(wmObj);
    jmethodID getConnectionInfoMethodID = env->GetMethodID(jwmClszz, "getConnectionInfo",
                                                           "()Landroid/net/wifi/WifiInfo;");
    jobject wifiInfoObj = env->CallObjectMethod(wmObj, getConnectionInfoMethodID);

    jclass wifiInfoClass = env->GetObjectClass(wifiInfoObj);
    jmethodID getMacAddressMethodID = env->GetMethodID(wifiInfoClass, "getMacAddress",
                                                       "()Ljava/lang/String;");
    jstring
            macAddressjstr = (jstring)
            env->CallObjectMethod(wifiInfoObj, getMacAddressMethodID);
    char *macAddress = jstringTostring(env, macAddressjstr);
    if (logShow)LOGI("mac address:%s ", macAddress);

    env->DeleteLocalRef(jwmClszz);
    env->DeleteLocalRef(wifiInfoClass);

    if (macAddress == NULL) {
        return "";
    }
    return macAddress;
}

//新添加
char* isWhatTypeOperate(JNIEnv * env,jobject ctx){
    jclass Context = env->FindClass("android/content/Context");
    jfieldID telService = env->GetStaticFieldID(Context,"TELEPHONY_SERVICE","Ljava/lang/String;");
    jstring telServiceValue = (jstring) env->GetStaticObjectField(Context, telService);
    jmethodID getSysService = env->GetMethodID(Context,"getSystemService","(Ljava/lang/String;)Ljava/lang/Object;");
    jobject mtelManger = env->CallObjectMethod(ctx,getSysService,telServiceValue);

    jclass jclass1 = env->FindClass("android/telephony/TelephonyManager");
    jmethodID jmethodID1 = env->GetMethodID(jclass1,"getSimOperator","()Ljava/lang/String;");
    jstring jstring1 = (jstring) env->CallObjectMethod(mtelManger, jmethodID1);

    env->DeleteLocalRef(Context);
    env->DeleteLocalRef(telServiceValue);
    env->DeleteLocalRef(mtelManger);
    env->DeleteLocalRef(jclass1);

    char * str = jstringTostring(env,jstring1);
    LOGI("operate: %s", str);
    if (str == NULL){
        LOGI("情况说明: %s","没有sim卡");
        return "00";
    }
    jclass jclass2 = env->GetObjectClass(jstring1);
    jmethodID jmethodID2 = env->GetMethodID(jclass2,"equals","(Ljava/lang/Object;)Z");

    jboolean jboolean1 = env->CallBooleanMethod(jstring1,jmethodID2,stoJstring(env,"46000"));
    jboolean jboolean2 = env->CallBooleanMethod(jstring1,jmethodID2,stoJstring(env,"46002"));
    jboolean jboolean3 = env->CallBooleanMethod(jstring1,jmethodID2,stoJstring(env,"46001"));
    jboolean jboolean4 = env->CallBooleanMethod(jstring1,jmethodID2,stoJstring(env,"46003"));

    if(jboolean1 || jboolean2){
        LOGI("operate: %s","中国移动");
        return "cmcc";
    }
    if (jboolean3){
        LOGI("operate: %s","中国联通");
        return "cucc";
    }
    if(jboolean4){
        LOGI("operate: %s","中国电信");
        return "ctcc";
    }

    return "00";
}

jstring isEmulate4simple1(JNIEnv *env, jobject ctx) {
    if (isEmulate4simple(env, ctx)) {
        return stoJstring(env, "false");//此处硬性修改了，本应为trues
    } else {
        return stoJstring(env, "true");
    }
}

//是否是模拟器
jboolean isEmulate4simple(JNIEnv *env, jobject ctx) {
    jclass SystemPropertiesClazz = env->FindClass("android/os/SystemProperties");
    jmethodID getMethod = env->GetStaticMethodID(SystemPropertiesClazz, "get",
                                                 "(Ljava/lang/String;)Ljava/lang/String;");
    jstring temp = (jstring) env->CallStaticObjectMethod(SystemPropertiesClazz, getMethod,
                                                         stoJstring(env, "ro.kernel.qemu"));
    char *tempChar = jstringTostring(env, temp);
    if (tempChar != NULL) {
        if (strcmp("1", tempChar) == 0) {
            return JNI_TRUE;
        }
    }

    jclass telephonyManagerClazz = getTelephoneManagerClass(env);
    jobject telephonyManager = getTelephoneManager(env,ctx);

    if (telephonyManager != NULL) {
        jmethodID getDeviceId = env->GetMethodID(telephonyManagerClazz, "getDeviceId",
                                                 "()Ljava/lang/String;");
        jstring deviceId = (jstring) env->CallObjectMethod(telephonyManager, getDeviceId);
        if (env->ExceptionCheck()) {
            if (logShow) env->ExceptionDescribe();
            env->ExceptionClear();
        }
        if (deviceId == NULL) {
            return JNI_TRUE;
        }
        jclass stringClazz = env->FindClass("java/lang/String");
        jmethodID matches = env->GetMethodID(stringClazz, "matches", "(Ljava/lang/String;)Z");
        jboolean ismatches = env->CallBooleanMethod(deviceId, matches, stoJstring(env, "0+"));
        if (ismatches || strlen(jstringTostring(env, deviceId)) == 0) {
            return JNI_TRUE;
        }
    }
    jclass buildClazz = env->FindClass("android/os/Build");
    jfieldID FINGERPRINT = env->GetStaticFieldID(buildClazz, "FINGERPRINT", "Ljava/lang/String;");
    jstring fingerprint = (jstring) env->GetStaticObjectField(buildClazz, FINGERPRINT);
    if (startWith(env, fingerprint, stoJstring(env, "generic"))) {
        return JNI_TRUE;
    }

    jmethodID getNetworkOperatorNameMethod = env->GetMethodID(telephonyManagerClazz,
                                                              "getNetworkOperatorName",
                                                              "()Ljava/lang/String;");
    jstring name = (jstring) env->CallObjectMethod(telephonyManager, getNetworkOperatorNameMethod);

    if (isNotEmpty(env, name) &&
        strcmp(jstringTostring(env, toLowerCase(env, name)), "android") == 0) {
        return JNI_TRUE;
    }
    jstring imis = getOsImsi(env, ctx);
    if (isNotEmpty(env, imis) && strcmp(jstringTostring(env, imis), "310260000000000") == 0) {
        return JNI_TRUE;
    }
    if (hasQEmuDrivers(env)) {
        return JNI_TRUE;
    }
    return JNI_FALSE;

}

jstring getOsImsi(JNIEnv *env, jobject ctx) {
    if (ctx == NULL) {
        LOGE("context is null");
        return NULL;
    }
    jobject telephoneManager = getTelephoneManager(env, ctx);
    if (telephoneManager == NULL) {
        return stoJstring(env, "");
    }
    jclass managerClass = getTelephoneManagerClass(env);
    jmethodID getDeviceIdMethod = env->GetMethodID(managerClass, "getSubscriberId",
                                                   "()Ljava/lang/String;");
    jstring imsi = (jstring) env->CallObjectMethod(telephoneManager, getDeviceIdMethod);
    if (env->ExceptionCheck()) {
        if (logShow)env->ExceptionDescribe();
        env->ExceptionClear();
        return stoJstring(env, "");
    }
    env->DeleteLocalRef(telephoneManager);
    env->DeleteLocalRef(managerClass);
    return imsi;
}


jclass getTelephoneManagerClass(JNIEnv *env) {
    return env->FindClass("android/telephony/TelephonyManager");
}

jobject getTelephoneManager(JNIEnv *env, jobject ctx) {
    if (ctx == NULL) {
        LOGE("context is null");
        return NULL;
    }
    jclass ctxClazz = env->FindClass("android/content/ContextWrapper");
    jmethodID getSystemServiceMethod = env->GetMethodID(ctxClazz, "getSystemService",
                                                        "(Ljava/lang/String;)Ljava/lang/Object;");
    jobject telephoneManager = env->CallNonvirtualObjectMethod(ctx, ctxClazz,
                                                               getSystemServiceMethod,
                                                               stoJstring(env, "phone"));
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
        return NULL;
    }
    env->DeleteLocalRef(ctxClazz);
    return telephoneManager;
}

//接下面
jboolean isNotEmpty(JNIEnv *env, jstring str) {
    if (str != NULL && env->GetStringLength(str) > 0) {
        return JNI_TRUE;
    }
    return JNI_FALSE;
}

jboolean startWith(JNIEnv *env, jstring str, jstring key) {
    jclass stringClazz = env->FindClass("java/lang/String");
    jmethodID startWithMethod = env->GetMethodID(stringClazz, "startsWith",
                                                 "(Ljava/lang/String;)Z");
    jboolean temp = env->CallBooleanMethod(str, startWithMethod, key);
    return temp;
}

jstring toLowerCase(JNIEnv *env, jstring str) {
    jclass stringClazz = env->FindClass("java/lang/String");
    jmethodID toLowerCaseMethod = env->GetMethodID(stringClazz, "toLowerCase",
                                                   "()Ljava/lang/String;");
    jstring temp = (jstring) env->CallObjectMethod(str, toLowerCaseMethod);
    return temp;
}

jboolean hasQEmuDrivers(JNIEnv *env) {
    if (access("/proc/tty/drivers", R_OK)) {
        jstring data = readFile(env, stoJstring(env, "/proc/tty/drivers"));
        if (indexOf(env, data, stoJstring(env, "goldfish")) != -1) {
            return JNI_TRUE;
        }
    }
    if (access("/proc/cpuinfo", R_OK)) {
        jstring data = readFile(env, stoJstring(env, "/proc/cpuinfo"));
        if (indexOf(env, data, stoJstring(env, "goldfish")) != -1) {
            return JNI_TRUE;
        }
    }

}

jstring readFile(JNIEnv *env, jstring path) {
    jbyteArray buffer = env->NewByteArray(1024);

    jclass fileClazz = env->FindClass("java/io/File");
    jmethodID fileConstrucMethod = env->GetMethodID(fileClazz, "<init>", "(Ljava/lang/String;)V");
    jobject file = env->NewObject(fileClazz, fileConstrucMethod, path);

    jclass FileInputStreamClazz = env->FindClass("java/io/FileInputStream");
    jmethodID FileInputStreamConstructMethode = env->GetMethodID(FileInputStreamClazz, "<init>",
                                                                 "(Ljava/io/File;)V");
    jobject fileInputStream = env->NewObject(FileInputStreamClazz, FileInputStreamConstructMethode,
                                             file);

    jmethodID readMethod = env->GetMethodID(FileInputStreamClazz, "read", "([BII)I");
    env->CallIntMethod(fileInputStream, readMethod, buffer, 0, 1024);

    jmethodID close = env->GetMethodID(FileInputStreamClazz, "close", "()V");
    env->CallNonvirtualVoidMethod(fileInputStream, FileInputStreamClazz, close);

    jclass stringClazz = env->FindClass("java/lang/String");
    jmethodID stringConsturct = env->GetMethodID(stringClazz, "<init>", "([B)V");
    jstring str = (jstring) env->NewObject(stringClazz, stringConsturct, buffer);
    return str;
}

//待增加

jint getSDKVersionInt(JNIEnv *env) {
    jclass buildClass = env->FindClass("android/os/Build$VERSION");
    jfieldID sdk_int = env->GetStaticFieldID(buildClass, "SDK_INT", "I");
    jint sdk = env->GetStaticIntField(buildClass, sdk_int);
    return sdk;
}

int property_get(const char *key, char *value, const char *default_value) {
    int len;

    len = __system_property_get(key, value);
    if (len > 0) {
        return len;
    }

    if (default_value) {
        len = strlen(default_value);
        memcpy(value, default_value, len + 1);
    }
    return len;
}

char *getBuild(const char *key, const char *def) {
    char char2[PROP_VALUE_MAX];
    property_get(key, char2, def);
    char *ret = (char *) malloc(strlen(char2) + 1);
    memcpy(ret, char2, strlen(char2) + 1);
    return ret;
}

char *getSdkVersionChar() {
    char *ret = getBuild("ro.build.version.sdk", "");
    return ret;
}


char *getRelease() {
    char *ret = getBuild("ro.build.version.release", "");
    return ret;
}

jint getSimCount(JNIEnv *env, jobject ctx) {
    jobject telephoneManager = getTelephoneManager(env, ctx);
    if (telephoneManager == NULL) {
        return -1;
    }
    jclass managerClass = getTelephoneManagerClass(env);
    jmethodID getDeviceIdMethod = env->GetMethodID(managerClass, "getSimCount",
                                                   "()I");
    if (env->ExceptionCheck()) {
        if (logShow)env->ExceptionDescribe();
        env->ExceptionClear();
        return -1;
    }
    jint simCount = env->CallIntMethod(telephoneManager, getDeviceIdMethod);

    env->DeleteLocalRef(telephoneManager);
    env->DeleteLocalRef(managerClass);
    return simCount;
}


//增加

//获取Android_id
jstring getAndroidId(JNIEnv *env, jobject ctx) {
    if (ctx == NULL) {
        LOGE("No Context Found Error!");
        return NULL;
    }
    jclass ctxClazz = env->FindClass("android/content/ContextWrapper");
    jmethodID getContentResolverMethod = env->GetMethodID(ctxClazz, "getContentResolver",
                                                          "()Landroid/content/ContentResolver;");
    jobject contentResolver = env->CallNonvirtualObjectMethod(ctx, ctxClazz,
                                                              getContentResolverMethod);

    jclass secureClass = env->FindClass("android/provider/Settings$Secure");

    jmethodID getStringMethod = env->GetStaticMethodID(secureClass, "getString",
                                                       "(Landroid/content/ContentResolver;Ljava/lang/String;)Ljava/lang/String;");

    jstring android_id = (jstring) env->CallStaticObjectMethod(secureClass, getStringMethod,
                                                               contentResolver,
                                                               charToJstring(env, "android_id"));

    env->DeleteLocalRef(ctxClazz);
    env->DeleteLocalRef(contentResolver);
    env->DeleteLocalRef(secureClass);

    return android_id;

}

jstring getSerialNo(JNIEnv *env) {
    char *ret = getBuild("ro.serialno", "");
    return charToJstring(env, ret);
}

void getLacAndCellId(JNIEnv *env, jobject ctx, jstring *lac, jstring *cellId) {
    if (ctx == NULL) {
        LOGE("No Context Found Error!");
        return;
    }
    jobject telephoneManager = getTelephoneManager(env, ctx);
    jclass telephoneManagerClass = getTelephoneManagerClass(env);
    jmethodID getSimSerialNumberMethod = env->GetMethodID(telephoneManagerClass,
                                                          "getCellLocation",
                                                          "()Landroid/telephony/CellLocation;");
    jobject gsmCellLocation = env->CallObjectMethod(telephoneManager, getSimSerialNumberMethod);
    if (env->ExceptionCheck()) {
        if (logShow) env->ExceptionDescribe();
        env->ExceptionClear();
        return;
    }
    if (gsmCellLocation == NULL) {
        return;
    }

    jclass gsmCellLocationClass = env->FindClass("android/telephony/gsm/GsmCellLocation");
    jclass cdmaCellLocationClazz = env->FindClass("android/telephony/cdma/CdmaCellLocation");

    if (env->IsInstanceOf(gsmCellLocation, gsmCellLocationClass)) {//是gsm
        jmethodID getLacMethod = env->GetMethodID(gsmCellLocationClass, "getLac",
                                                  "()I");
        jmethodID getCidMethod = env->GetMethodID(gsmCellLocationClass, "getCid",
                                                  "()I");
        *cellId = jintToJstring(env, env->CallIntMethod(gsmCellLocation, getCidMethod));
        *lac = jintToJstring(env, env->CallIntMethod(gsmCellLocation, getLacMethod));
    } else if (env->IsInstanceOf(gsmCellLocation, cdmaCellLocationClazz)) {//是cdma
        jmethodID mid_getCid = env->GetMethodID(cdmaCellLocationClazz, "getBaseStationId", "()I");
        jmethodID mid_getlac = env->GetMethodID(cdmaCellLocationClazz, "getNetworkId", "()I");

        *cellId = jintToJstring(env, env->CallIntMethod(gsmCellLocation, mid_getCid));
        *lac = jintToJstring(env, env->CallIntMethod(gsmCellLocation, mid_getlac));
    }


    env->DeleteLocalRef(telephoneManager);
    env->DeleteLocalRef(telephoneManagerClass);
    env->DeleteLocalRef(gsmCellLocation);
    env->DeleteLocalRef(gsmCellLocationClass);
    env->DeleteLocalRef(cdmaCellLocationClazz);


}

//jstring getCellid(JNIEnv *env, jobject ctx) {
//    if (ctx == NULL) {
//        LOGE("No Context Found Error!");
//        return NULL;
//    }
//    jobject telephoneManager = getTelephoneManager(env, ctx);
//    jclass telephoneManagerClass = getTelephoneManagerClass(env);
//    jmethodID getSimSerialNumberMethod = env->GetMethodID(telephoneManagerClass,
//                                                          "getCellLocation",
//                                                          "()Landroid/telephony/CellLocation;");
//    jobject gsmCellLocation = env->CallObjectMethod(telephoneManager, getSimSerialNumberMethod);
//
//    if (env->ExceptionCheck()) {
//        if (logShow)
//            env->ExceptionDescribe();
//        env->ExceptionClear();
//        return charToJstring(env, "");
//    }
//
//    jclass gsmCellLocationClass = env->FindClass("android/telephony/gsm/GsmCellLocation");
//
//    jmethodID getCidMethod = env->GetMethodID(gsmCellLocationClass, "getCid",
//                                              "()I");
//    jstring cellid = jintToJstring(env, env->CallIntMethod(gsmCellLocation, getCidMethod));
//
//    env->DeleteLocalRef(telephoneManager);
//    env->DeleteLocalRef(telephoneManagerClass);
//    env->DeleteLocalRef(gsmCellLocation);
//    env->DeleteLocalRef(gsmCellLocationClass);
//
//    return cellid;
//
//}

jstring getCellid(JNIEnv *env, jobject ctx) {
    if (ctx == NULL) {
        LOGE("No Context Found Error!");
        return NULL;
    }
    jobject telephoneManager = getTelephoneManager(env, ctx);
    jclass telephoneManagerClass = getTelephoneManagerClass(env);
    jmethodID getSimSerialNumberMethod = env->GetMethodID(telephoneManagerClass,
                                                          "getCellLocation",
                                                          "()Landroid/telephony/CellLocation;");
    jobject gsmCellLocation = env->CallObjectMethod(telephoneManager, getSimSerialNumberMethod);

    if (gsmCellLocation == NULL) {
        return charToJstring(env,"");
    }
    if (env->ExceptionCheck()) {
        if (logShow)
            env->ExceptionDescribe();
        env->ExceptionClear();
        return charToJstring(env, "");
    }
    jclass cdmaCellLocationClazz = env->FindClass("android/telephony/cdma/CdmaCellLocation");
    jclass gsmCellLocationClass = env->FindClass("android/telephony/gsm/GsmCellLocation");
    if (env->IsInstanceOf(gsmCellLocation, gsmCellLocationClass)){

        jmethodID getCidMethod = env->GetMethodID(gsmCellLocationClass, "getCid", "()I");
        jstring cellid = jintToJstring(env, env->CallIntMethod(gsmCellLocation, getCidMethod));

        env->DeleteLocalRef(telephoneManager);
        env->DeleteLocalRef(telephoneManagerClass);
        env->DeleteLocalRef(gsmCellLocation);
        env->DeleteLocalRef(gsmCellLocationClass);
        return cellid;
    }else if (env->IsInstanceOf(gsmCellLocation, cdmaCellLocationClazz)){
        jmethodID mid_getCid = env->GetMethodID(cdmaCellLocationClazz, "getBaseStationId", "()I");
        jstring cellid = jintToJstring(env, env->CallIntMethod(gsmCellLocation, mid_getCid));

        env->DeleteLocalRef(telephoneManager);
        env->DeleteLocalRef(telephoneManagerClass);
        env->DeleteLocalRef(gsmCellLocation);
        env->DeleteLocalRef(gsmCellLocationClass);
        return cellid;
    }


}
//与 getcellid的方法几乎一样
jstring getLac(JNIEnv *env, jobject ctx) {
    if (ctx == NULL) {
        LOGE("No Context Found Error!");
        return NULL;
    }
    jobject telephoneManager = getTelephoneManager(env, ctx);
    jclass telephoneManagerClass = getTelephoneManagerClass(env);
    jmethodID getSimSerialNumberMethod = env->GetMethodID(telephoneManagerClass,
                                                          "getCellLocation",
                                                          "()Landroid/telephony/CellLocation;");
    jobject gsmCellLocation = env->CallObjectMethod(telephoneManager, getSimSerialNumberMethod);

    if (env->ExceptionCheck()) {
        if (logShow)
            env->ExceptionDescribe();
        env->ExceptionClear();
        return charToJstring(env, "");
    }

    if (gsmCellLocation == NULL) {
        return stoJstring(env,"");
    }

    jclass gsmCellLocationClass = env->FindClass("android/telephony/gsm/GsmCellLocation");
    jclass cdmaCellLocationClazz = env->FindClass("android/telephony/cdma/CdmaCellLocation");
    if (env->IsInstanceOf(gsmCellLocation, gsmCellLocationClass)){
        jmethodID getCidMethod = env->GetMethodID(gsmCellLocationClass, "getLac","()I");
        jstring lac = jintToJstring(env, env->CallIntMethod(gsmCellLocation, getCidMethod));
        env->DeleteLocalRef(telephoneManager);
        env->DeleteLocalRef(telephoneManagerClass);
        env->DeleteLocalRef(gsmCellLocation);
        env->DeleteLocalRef(gsmCellLocationClass);
        return lac;
    }else if (env->IsInstanceOf(gsmCellLocation, cdmaCellLocationClazz)){
        jmethodID mid_getlac = env->GetMethodID(cdmaCellLocationClazz, "getNetworkId", "()I");
        jstring lac = jintToJstring(env, env->CallIntMethod(gsmCellLocation, mid_getlac));
        env->DeleteLocalRef(telephoneManager);
        env->DeleteLocalRef(telephoneManagerClass);
        env->DeleteLocalRef(gsmCellLocation);
        env->DeleteLocalRef(gsmCellLocationClass);

        return lac;
    }

}

jstring getPhoneNumber(JNIEnv *env, jobject ctx) {
    if (ctx == NULL) {
        LOGE("No Context Found Error!");
        return NULL;
    }
    jobject telephoneManager = getTelephoneManager(env, ctx);
    jclass telephoneManagerClass = getTelephoneManagerClass(env);
    jmethodID getDeviceIdMethod = env->GetMethodID(telephoneManagerClass, "getLine1Number",
                                                   "()Ljava/lang/String;");
    jstring phone = (jstring) env->CallObjectMethod(telephoneManager, getDeviceIdMethod);
//    if (env->ExceptionCheck()) {
//        if (logShow)
//            env->ExceptionDescribe();
//        env->ExceptionClear();
//        return charToJstring(env, "");
//    }
    if (!isNotEmpty(env, phone)) {
        phone = charToJstring(env, "");
    }

    env->DeleteLocalRef(telephoneManagerClass);
    env->DeleteLocalRef(telephoneManager);
    return phone;
}

jstring getNetworkType(JNIEnv *env, jobject ctx) {
    if (ctx == NULL) {
        LOGE("context is null");
        return NULL;
    }
    jstring type = charToJstring(env, "unknown");
    jclass ctxClazz = env->FindClass("android/content/ContextWrapper");
    jmethodID getSystemServiceMethod = env->GetMethodID(ctxClazz, "getSystemService",
                                                        "(Ljava/lang/String;)Ljava/lang/Object;");
    jobject connectivityManager = env->CallNonvirtualObjectMethod(ctx, ctxClazz,
                                                                  getSystemServiceMethod,
                                                                  charToJstring(env,
                                                                                "connectivity"));
    jclass connectivityManagerClass = env->FindClass("android/net/ConnectivityManager");

    jmethodID getActiveNetworkInfoMethod = env->GetMethodID(connectivityManagerClass,
                                                            "getActiveNetworkInfo",
                                                            "()Landroid/net/NetworkInfo;");

    jobject networkInfo = env->CallObjectMethod(connectivityManager, getActiveNetworkInfoMethod);

    if (networkInfo != NULL) {
        jclass networkInfoClass = env->FindClass("android/net/NetworkInfo");
        jmethodID getTypeMethod = env->GetMethodID(networkInfoClass, "getType", "()I");
        jint networktype = env->CallIntMethod(networkInfo, getTypeMethod);

        if (networktype == 1) {
            type = charToJstring(env, "WIFI");
        } else {
            type = charToJstring(env, "GPRS");
        }
        env->DeleteLocalRef(networkInfoClass);
    } else {
        return charToJstring(env, "-1");
    }
    env->DeleteLocalRef(networkInfo);
    env->DeleteLocalRef(connectivityManagerClass);
    env->DeleteLocalRef(connectivityManager);
    env->DeleteLocalRef(ctxClazz);
    return type;
}

jstring getProduct(JNIEnv *env) {
//    ro.product.name
    char *ret = getBuild("ro.product.name", "");
    return charToJstring(env, ret);
}

//ro.product.cpu.abilist
jstring getCpu(JNIEnv *env) {
    char *ret = getBuild("ro.product.cpu.abilist", "");
    return charToJstring(env, ret);
}

jstring getPackageVersion(JNIEnv *env, jobject ctx) {
    if (ctx == NULL) {
        LOGE("No Context Found Error!");
        return NULL;
    }
    jclass ctxClazz = env->FindClass("android/content/ContextWrapper");
    jmethodID getpnMid = env->GetMethodID(ctxClazz, "getPackageName", "()Ljava/lang/String;");
    jstring pn = (jstring) env->CallNonvirtualObjectMethod(ctx, ctxClazz, getpnMid);

    jmethodID getPackageManager = env->GetMethodID(ctxClazz, "getPackageManager",
                                                   "()Landroid/content/pm/PackageManager;");

    jobject packageManager = env->CallNonvirtualObjectMethod(ctx, ctxClazz, getPackageManager);

    jclass packageManagerClazz = env->FindClass("android/app/ApplicationPackageManager");

    jmethodID getPackageInfo = env->GetMethodID(packageManagerClazz, "getPackageInfo",
                                                "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    jobject packageInfo = env->CallNonvirtualObjectMethod(packageManager, packageManagerClazz,
                                                          getPackageInfo, pn, 0);

    jclass packageInfoClazz = env->FindClass("android/content/pm/PackageInfo");
    jfieldID versionCodeFieldID = env->GetFieldID(packageInfoClazz, "versionCode", "I");
    jint versionCode = env->GetIntField(packageInfo, versionCodeFieldID);

    env->DeleteLocalRef(packageInfoClazz);
    env->DeleteLocalRef(packageInfo);
    env->DeleteLocalRef(packageManagerClazz);
    env->DeleteLocalRef(packageManager);
    env->DeleteLocalRef(pn);
    env->DeleteLocalRef(ctxClazz);

    return jintToJstring(env, versionCode);
}

jstring getLocal(JNIEnv *env, jobject ctx) {
    if (ctx == NULL) {
        LOGE("No Context Found Error!");
        return NULL;
    }

    jclass ctxClazz = env->FindClass("android/content/ContextWrapper");
    jmethodID getResourcesMethod = env->GetMethodID(ctxClazz, "getResources",
                                                    "()Landroid/content/res/Resources;");
    jobject resources = env->CallNonvirtualObjectMethod(ctx, ctxClazz, getResourcesMethod);

    jclass resourcesClazz = env->FindClass("android/content/res/Resources");
    jmethodID getConfigurationMethod = env->GetMethodID(resourcesClazz, "getConfiguration",
                                                        "()Landroid/content/res/Configuration;");
    jobject configuration = env->CallObjectMethod(resources, getConfigurationMethod);

    jclass configurationClazz = env->FindClass("android/content/res/Configuration");
    jfieldID localeFieldID = env->GetFieldID(configurationClazz, "locale", "Ljava/util/Locale;");
    jobject locale = env->GetObjectField(configuration, localeFieldID);

    jclass localeClazz = env->FindClass("java/util/Locale");
    jmethodID getLanguageMethod = env->GetMethodID(localeClazz, "getLanguage",
                                                   "()Ljava/lang/String;");
    jmethodID getCountryMethod = env->GetMethodID(localeClazz, "getCountry",
                                                  "()Ljava/lang/String;");
    jstring country = (jstring) env->CallObjectMethod(locale, getCountryMethod);
    jstring language = (jstring) env->CallObjectMethod(locale, getLanguageMethod);

//    LOGE("country = %s,language = %s", jstringToChar(env, country), jstringToChar(env, language));

    env->DeleteLocalRef(localeClazz);
    env->DeleteLocalRef(locale);
    env->DeleteLocalRef(configurationClazz);
    env->DeleteLocalRef(configuration);
    env->DeleteLocalRef(resourcesClazz);
    env->DeleteLocalRef(resources);
    env->DeleteLocalRef(ctxClazz);

    return charToJstring(env, strcat(strcat(jstringToChar(env, country), "_"),
                                     jstringToChar(env, language)));
}

jstring getInstallTime(JNIEnv *env, jobject ctx) {
    if (ctx == NULL) {
        LOGE("No Context Found Error!");
        return NULL;
    }
    jclass ctxClazz = env->FindClass("android/content/ContextWrapper");
    jmethodID getpnMid = env->GetMethodID(ctxClazz, "getPackageName", "()Ljava/lang/String;");
    jstring pn = (jstring) env->CallNonvirtualObjectMethod(ctx, ctxClazz, getpnMid);

    jmethodID getPackageManager = env->GetMethodID(ctxClazz, "getPackageManager",
                                                   "()Landroid/content/pm/PackageManager;");

    jobject packageManager = env->CallNonvirtualObjectMethod(ctx, ctxClazz, getPackageManager);

    jclass packageManagerClazz = env->FindClass("android/app/ApplicationPackageManager");

    jmethodID getPackageInfo = env->GetMethodID(packageManagerClazz, "getPackageInfo",
                                                "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    jobject packageInfo = env->CallNonvirtualObjectMethod(packageManager, packageManagerClazz,
                                                          getPackageInfo, pn, 0);

    jclass packageInfoClazz = env->FindClass("android/content/pm/PackageInfo");
    jfieldID versionCodeFieldID = env->GetFieldID(packageInfoClazz, "firstInstallTime", "J");
    jlong installTime = env->GetLongField(packageInfo, versionCodeFieldID);


    env->DeleteLocalRef(packageInfoClazz);
    env->DeleteLocalRef(packageInfo);
    env->DeleteLocalRef(packageManagerClazz);
    env->DeleteLocalRef(packageManager);
    env->DeleteLocalRef(pn);
    env->DeleteLocalRef(ctxClazz);
    return jlongToJstring(env, installTime);
}

jstring getUUID(JNIEnv *env) {
//    if (ctx == NULL) {
//        LOGE("No Context Found Error!");
//        return NULL;
//    }
    jclass uuidClazz = env->FindClass("java/util/UUID");
    jmethodID randomUUIDMethod = env->GetStaticMethodID(uuidClazz, "randomUUID",
                                                        "()Ljava/util/UUID;");
    jobject uuidobj = env->CallStaticObjectMethod(uuidClazz, randomUUIDMethod);
    return toJstring(env, uuidobj);
}

jstring getSimOperatorName(JNIEnv *env, jobject ctx) {
    if (ctx == NULL) {
        LOGE("No Context Found Error!");
        return NULL;
    }
    jobject telephoneManager = getTelephoneManager(env, ctx);
    jclass telephoneManagerClass = getTelephoneManagerClass(env);
    jmethodID getSimSerialNumberMethod = env->GetMethodID(telephoneManagerClass,
                                                          "getSimOperator",
                                                          "()Ljava/lang/String;");
    jstring opName = (jstring) env->CallObjectMethod(telephoneManager, getSimSerialNumberMethod);

    char *simOperator = jstringToChar(env, opName);
//    LOGE("simOperator = %s", simOperator);
    if (strcmp(simOperator, "46000") == 0 || strcmp(simOperator, "46002") == 0 ||
        strcmp(simOperator, "46007") == 0) {
        opName = charToJstring(env, "CM");
    } else if (strcmp(simOperator, "46001") == 0 || strcmp(simOperator, "46006") == 0) {
        opName = charToJstring(env, "CU");
    } else if (strcmp(simOperator, "46003") == 0 || strcmp(simOperator, "46005") == 0) {
        opName = charToJstring(env, "CT");
    } else if (isNotEmpty(env, opName)) {
        opName = charToJstring(env, "unknown");
    } else {
        opName = charToJstring(env, "");
    }

    env->DeleteLocalRef(telephoneManager);
    env->DeleteLocalRef(telephoneManagerClass);
    return opName;
}