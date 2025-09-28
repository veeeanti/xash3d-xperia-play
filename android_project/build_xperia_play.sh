#!/bin/bash

# Build script for Xash3D FWGS Xperia Play APK for Android 2.3.3

# Check if Android NDK is set
if [ -z "$ANDROID_NDK" ]; then
    echo "ANDROID_NDK environment variable is not set"
    echo "Please set it to your Android NDK path"
    exit 1
fi

# Check if Android SDK is set
if [ -z "$ANDROID_SDK" ]; then
    echo "ANDROID_SDK environment variable is not set"
    echo "Please set it to your Android SDK path"
    exit 1
fi

# Create necessary directories
mkdir -p jni
mkdir -p src/in/celest/xash3d
mkdir -p res/values
mkdir -p res/layout
mkdir -p libs/armeabi
mkdir -p assets

# Copy the engine library
echo "Copying engine library..."
cp ../engine/libxash.so libs/armeabi/

# Create AndroidManifest.xml
cat > AndroidManifest.xml << EOF
<?xml version="1.0" encoding="utf-8"?>
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    package="in.celest.xash3d"
    android:versionCode="1"
    android:versionName="0.19.2">

    <uses-sdk android:minSdkVersion="10" android:targetSdkVersion="10" />

    <uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
    <uses-permission android:name="android.permission.INTERNET" />
    <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
    <uses-permission android:name="android.permission.VIBRATE" />

    <application
        android:icon="@drawable/icon"
        android:label="@string/app_name"
        android:theme="@android:style/Theme.NoTitleBar.Fullscreen"
        android:allowBackup="true">
        
        <activity
            android:name=".XashActivity"
            android:label="@string/app_name"
            android:configChanges="mcc|mnc|locale|touchscreen|keyboard|keyboardHidden|navigation|orientation|screenLayout|uiMode|screenSize|smallestScreenSize"
            android:screenOrientation="landscape"
            android:launchMode="singleInstance">
            <intent-filter>
                <action android:name="android.intent.action.MAIN" />
                <category android:name="android.intent.category.LAUNCHER" />
            </intent-filter>
        </activity>
    </application>
</manifest>
EOF

# Create build.properties
cat > build.properties << EOF
# Project target
target=android-10
EOF

# Create project.properties
cat > project.properties << EOF
# Project target
target=android-10
android.library.reference.1=../sdk
EOF

# Create proguard-project.txt
cat > proguard-project.txt << EOF
# To enable ProGuard in your project, edit project.properties
# to define the proguard.config property as described in that file.
#
# Add project specific ProGuard rules here.
# By default, the flags in this file are appended to flags specified
# in ${sdk.dir}/tools/proguard/proguard-android.txt
# You can edit the include path and order by changing the ProGuard
# include property in project.properties.
#
# For more details, see
#   http://developer.android.com/guide/developing/tools/proguard.html

# Add any project specific keep options here:

# If your project uses WebView with JS, uncomment the following
# and specify the fully qualified class name to the JavaScript interface
# class:
#-keepclassmembers class fqcn.of.javascript.interface.for.webview {
#   public *;
#}
EOF

# Create build script
cat > build.sh << EOF
#!/bin/bash

# Build the APK
ndk-build -j4 APP_CFLAGS="-w" NDK_CCACHE=ccache
ant debug
EOF

chmod +x build.sh

echo "Android project structure created successfully!"
echo "To build the APK, run: ./build.sh"