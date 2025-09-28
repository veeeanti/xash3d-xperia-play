#include <jni.h>
#include <android/log.h>
#include <errno.h>

// Include the necessary headers for Xash3D
extern "C" {
#include "common.h"
#include "input.h"
#include "client.h"
}

#define TAG "XashJNI"

// Log macros
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__))

// Function declarations
extern "C" {
    JNIEXPORT int JNICALL Java_in_celest_xash3d_XashActivity_nativeInit(JNIEnv *env, jobject obj, jobjectArray args);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeSetPause(JNIEnv *env, jobject obj, jint pause);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeUnPause(JNIEnv *env, jobject obj);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_onNativeResize(JNIEnv *env, jobject obj, jint width, jint height);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeKey(JNIEnv *env, jobject obj, jint down, jint code);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeTouch(JNIEnv *env, jobject obj, jint finger, jint action, jfloat x, jfloat y);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeTouchpad(JNIEnv *env, jobject obj, jint finger, jint action, jfloat x, jfloat y);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeString(JNIEnv *env, jobject obj, jstring string);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeMouseMove(JNIEnv *env, jobject obj, jfloat x, jfloat y);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeBall(JNIEnv *env, jobject obj, jint id, jbyte ball, jshort xrel, jshort yrel);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeHat(JNIEnv *env, jobject obj, jint id, jbyte hat, jbyte key, jboolean down);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeAxis(JNIEnv *env, jobject obj, jint id, jbyte axis, jshort val);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeJoyButton(JNIEnv *env, jobject obj, jint id, jbyte button, jboolean down);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeJoyAdd(JNIEnv *env, jobject obj, jint id);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeJoyDel(JNIEnv *env, jobject obj, jint id);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeOnResume(JNIEnv *env, jobject obj);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeOnFocusChange(JNIEnv *env, jobject obj);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeOnPause(JNIEnv *env, jobject obj);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeOnDestroy(JNIEnv *env, jobject obj);
    JNIEXPORT int JNICALL Java_in_celest_xash3d_XashActivity_setenv(JNIEnv *env, jobject obj, jstring key, jstring value, jboolean overwrite);
    JNIEXPORT int JNICALL Java_in_celest_xash3d_XashActivity_nativeTestWritePermission(JNIEnv *env, jobject obj, jstring path);
    
    // Xperia Play specific methods
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_swapBuffers(JNIEnv *env, jobject obj);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_toggleEGL(JNIEnv *env, jobject obj, jint enabled);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_showKeyboard(JNIEnv *env, jobject obj, jint show);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_vibrate(JNIEnv *env, jobject obj, jint duration);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_messageBox(JNIEnv *env, jobject obj, jstring title, jstring text);
    JNIEXPORT jboolean JNICALL Java_in_celest_xash3d_XashActivity_createGLContext(JNIEnv *env, jobject obj, jint stencilBits);
    JNIEXPORT jint JNICALL Java_in_celest_xash3d_XashActivity_getGLAttribute(JNIEnv *env, jobject obj, jint attr);
    JNIEXPORT jboolean JNICALL Java_in_celest_xash3d_XashActivity_deleteGLContext(JNIEnv *env, jobject obj);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_engineThreadNotify(JNIEnv *env, jobject obj);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_setTitle(JNIEnv *env, jobject obj, jstring title);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_setIcon(JNIEnv *env, jobject obj, jstring icon);
    JNIEXPORT jstring JNICALL Java_in_celest_xash3d_XashActivity_getAndroidID(JNIEnv *env, jobject obj);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_saveID(JNIEnv *env, jobject obj, jstring id);
    JNIEXPORT jstring JNICALL Java_in_celest_xash3d_XashActivity_loadID(JNIEnv *env, jobject obj);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_showMouse(JNIEnv *env, jobject obj, jint show);
    JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_shellExecute(JNIEnv *env, jobject obj, jstring path);
}

// Implementation of JNI functions
JNIEXPORT int JNICALL Java_in_celest_xash3d_XashActivity_nativeInit(JNIEnv *env, jobject obj, jobjectArray args) {
    LOGI("nativeInit called");
    return 0;
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeSetPause(JNIEnv *env, jobject obj, jint pause) {
    LOGI("nativeSetPause called with pause=%d", pause);
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeUnPause(JNIEnv *env, jobject obj) {
    LOGI("nativeUnPause called");
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_onNativeResize(JNIEnv *env, jobject obj, jint width, jint height) {
    LOGI("onNativeResize called with width=%d, height=%d", width, height);
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeKey(JNIEnv *env, jobject obj, jint down, jint code) {
    LOGI("nativeKey called with down=%d, code=%d", down, code);
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeTouch(JNIEnv *env, jobject obj, jint finger, jint action, jfloat x, jfloat y) {
    LOGI("nativeTouch called with finger=%d, action=%d, x=%f, y=%f", finger, action, x, y);
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeTouchpad(JNIEnv *env, jobject obj, jint finger, jint action, jfloat x, jfloat y) {
    LOGI("nativeTouchpad called with finger=%d, action=%d, x=%f, y=%f", finger, action, x, y);
    // Implementation for Xperia Play touchpad as joystick
    // Convert touchpad coordinates to joystick events
    // Touchpad resolution: 966x360
    
    // Normalize coordinates to -1.0 to 1.0 range for joystick
    float normalizedX = (x / 966.0f) * 2.0f - 1.0f;
    float normalizedY = (y / 360.0f) * 2.0f - 1.0f;
    
    // Invert Y axis (touchpad Y is inverted compared to joystick)
    normalizedY = -normalizedY;
    
    // Send as joystick axis events
    // Axis 0 = X axis (left/right)
    // Axis 1 = Y axis (forward/back)
    nativeAxis(0, 0, (short)(normalizedX * 32767));
    nativeAxis(0, 1, (short)(normalizedY * 32767));
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeString(JNIEnv *env, jobject obj, jstring string) {
    LOGI("nativeString called");
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeMouseMove(JNIEnv *env, jobject obj, jfloat x, jfloat y) {
    LOGI("nativeMouseMove called with x=%f, y=%f", x, y);
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeBall(JNIEnv *env, jobject obj, jint id, jbyte ball, jshort xrel, jshort yrel) {
    LOGI("nativeBall called with id=%d, ball=%d, xrel=%d, yrel=%d", id, ball, xrel, yrel);
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeHat(JNIEnv *env, jobject obj, jint id, jbyte hat, jbyte key, jboolean down) {
    LOGI("nativeHat called with id=%d, hat=%d, key=%d, down=%d", id, hat, key, down);
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeAxis(JNIEnv *env, jobject obj, jint id, jbyte axis, jshort val) {
    LOGI("nativeAxis called with id=%d, axis=%d, val=%d", id, axis, val);
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeJoyButton(JNIEnv *env, jobject obj, jint id, jbyte button, jboolean down) {
    LOGI("nativeJoyButton called with id=%d, button=%d, down=%d", id, button, down);
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeJoyAdd(JNIEnv *env, jobject obj, jint id) {
    LOGI("nativeJoyAdd called with id=%d", id);
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeJoyDel(JNIEnv *env, jobject obj, jint id) {
    LOGI("nativeJoyDel called with id=%d", id);
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeOnResume(JNIEnv *env, jobject obj) {
    LOGI("nativeOnResume called");
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeOnFocusChange(JNIEnv *env, jobject obj) {
    LOGI("nativeOnFocusChange called");
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeOnPause(JNIEnv *env, jobject obj) {
    LOGI("nativeOnPause called");
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_nativeOnDestroy(JNIEnv *env, jobject obj) {
    LOGI("nativeOnDestroy called");
}

JNIEXPORT int JNICALL Java_in_celest_xash3d_XashActivity_setenv(JNIEnv *env, jobject obj, jstring key, jstring value, jboolean overwrite) {
    LOGI("setenv called");
    return 0;
}

JNIEXPORT int JNICALL Java_in_celest_xash3d_XashActivity_nativeTestWritePermission(JNIEnv *env, jobject obj, jstring path) {
    LOGI("nativeTestWritePermission called");
    return 1;
}

// Xperia Play specific methods
JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_swapBuffers(JNIEnv *env, jobject obj) {
    LOGI("swapBuffers called");
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_toggleEGL(JNIEnv *env, jobject obj, jint enabled) {
    LOGI("toggleEGL called with enabled=%d", enabled);
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_showKeyboard(JNIEnv *env, jobject obj, jint show) {
    LOGI("showKeyboard called with show=%d", show);
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_vibrate(JNIEnv *env, jobject obj, jint duration) {
    LOGI("vibrate called with duration=%d", duration);
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_messageBox(JNIEnv *env, jobject obj, jstring title, jstring text) {
    LOGI("messageBox called");
}

JNIEXPORT jboolean JNICALL Java_in_celest_xash3d_XashActivity_createGLContext(JNIEnv *env, jobject obj, jint stencilBits) {
    LOGI("createGLContext called with stencilBits=%d", stencilBits);
    return JNI_TRUE;
}

JNIEXPORT jint JNICALL Java_in_celest_xash3d_XashActivity_getGLAttribute(JNIEnv *env, jobject obj, jint attr) {
    LOGI("getGLAttribute called with attr=%d", attr);
    return 0;
}

JNIEXPORT jboolean JNICALL Java_in_celest_xash3d_XashActivity_deleteGLContext(JNIEnv *env, jobject obj) {
    LOGI("deleteGLContext called");
    return JNI_TRUE;
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_engineThreadNotify(JNIEnv *env, jobject obj) {
    LOGI("engineThreadNotify called");
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_setTitle(JNIEnv *env, jobject obj, jstring title) {
    LOGI("setTitle called");
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_setIcon(JNIEnv *env, jobject obj, jstring icon) {
    LOGI("setIcon called");
}

JNIEXPORT jstring JNICALL Java_in_celest_xash3d_XashActivity_getAndroidID(JNIEnv *env, jobject obj) {
    LOGI("getAndroidID called");
    return env->NewStringUTF("xperia_play_device");
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_saveID(JNIEnv *env, jobject obj, jstring id) {
    LOGI("saveID called");
}

JNIEXPORT jstring JNICALL Java_in_celest_xash3d_XashActivity_loadID(JNIEnv *env, jobject obj) {
    LOGI("loadID called");
    return env->NewStringUTF("xperia_play_device");
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_showMouse(JNIEnv *env, jobject obj, jint show) {
    LOGI("showMouse called with show=%d", show);
}

JNIEXPORT void JNICALL Java_in_celest_xash3d_XashActivity_shellExecute(JNIEnv *env, jobject obj, jstring path) {
    LOGI("shellExecute called");
}