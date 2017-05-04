LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := device-info
LOCAL_LDFLAGS := -Wl,--build-id
LOCAL_LDLIBS := \
	-llog \

LOCAL_SRC_FILES := \
	D:\TempSdk\app\src\main\jni\cJSON\cJSON.c \
	D:\TempSdk\app\src\main\jni\com_use_tempsdk_jni_DeviceInfo.cpp \
	D:\TempSdk\app\src\main\jni\utils.cpp \

LOCAL_C_INCLUDES += D:\TempSdk\app\src\main\jni
LOCAL_C_INCLUDES += D:\TempSdk\app\src\debug\jni

include $(BUILD_SHARED_LIBRARY)
