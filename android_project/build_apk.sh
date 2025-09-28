#!/bin/bash

# Build script for Xash3D FWGS Xperia Play APK for Android 2.3.3

# Check if ANDROID_NDK is set
if [ -z "$ANDROID_NDK" ]; then
    echo "ERROR: ANDROID_NDK environment variable is not set"
    echo "Please set it to your Android NDK path"
    echo "Example: export ANDROID_NDK=/path/to/android-ndk"
    exit 1
fi

# Check if ANDROID_SDK is set
if [ -z "$ANDROID_SDK" ]; then
    echo "ERROR: ANDROID_SDK environment variable is not set"
    echo "Please set it to your Android SDK path"
    echo "Example: export ANDROID_SDK=/path/to/android-sdk"
    exit 1
fi

echo "Building Xash3D FWGS Xperia Play APK for Android 2.3.3..."

# Create necessary directories
echo "Creating directories..."
mkdir -p libs/armeabi
mkdir -p assets
mkdir -p assets/touch_default

# Copy the Xperia Play configuration
echo "Copying Xperia Play configuration..."
cp assets/xash3d_xperia_play.cfg ../xash3d_xperia_play.cfg 2>/dev/null || true

# Build the native code with NDK
echo "Building native code with NDK..."
$ANDROID_NDK/ndk-build -j4 APP_CFLAGS="-w" NDK_CCACHE=ccache

if [ $? -ne 0 ]; then
    echo "ERROR: NDK build failed"
    exit 1
fi

# Check if we need to initialize the Android project
if [ ! -f "local.properties" ]; then
    echo "Initializing Android project..."
    $ANDROID_SDK/tools/android update project --name xash3d-xperia-play --target android-10 --path .
    
    if [ $? -ne 0 ]; then
        echo "ERROR: Failed to update Android project"
        exit 1
    fi
fi

# Build the APK with Ant
echo "Building APK with Ant..."
ant debug

if [ $? -ne 0 ]; then
    echo "ERROR: Ant build failed"
    exit 1
fi

echo "Build successful!"
echo "APK is located at bin/xash3d-xperia-play-debug.apk"
echo ""
echo "To install on your Xperia Play device:"
echo "1. Enable USB debugging on your device"
echo "2. Connect your device via USB"
echo "3. Run: adb install -r bin/xash3d-xperia-play-debug.apk"