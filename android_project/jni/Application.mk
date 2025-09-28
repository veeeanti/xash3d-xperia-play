# Application.mk - NDK build configuration for Xash3D Xperia Play

# Target platform (Android 2.3.3 - API level 10)
APP_PLATFORM := android-10

# Target architecture - armeabi for compatibility with older devices
APP_ABI := armeabi

# STL library - gnustl_static for compatibility
APP_STL := gnustl_static

# Optimization flags
APP_CFLAGS := -O2 -DNDEBUG -DXASH_ANDROID -DXASH_XPERIA_PLAY

# Module to build
APP_MODULES := xash

# Use unified headers (for newer NDK versions)
NDK_APP_UNIFIED_HEADERS := true

# Disable RTTI and exceptions for smaller binary size
APP_CPPFLAGS := -fno-rtti -fno-exceptions