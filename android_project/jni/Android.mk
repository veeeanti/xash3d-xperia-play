LOCAL_PATH := $(call my-dir)

# Build the main Xash3D library
include $(CLEAR_VARS)

LOCAL_MODULE := xash

# Source files
LOCAL_SRC_FILES := xash_jni.cpp

# Include directories
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../engine \
                   $(LOCAL_PATH)/../../engine/common \
                   $(LOCAL_PATH)/../../engine/client \
                   $(LOCAL_PATH)/../../engine/platform/android \
                   $(LOCAL_PATH)/../../common

# Libraries to link
LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv1_CM

# Static libraries
LOCAL_STATIC_LIBRARIES := android_native_app_glue

# Additional compiler flags for Xperia Play support
LOCAL_CFLAGS := -DXASH_ANDROID -DXASH_XPERIA_PLAY

include $(BUILD_SHARED_LIBRARY)

# Import modules
$(call import-module,android/native_app_glue)