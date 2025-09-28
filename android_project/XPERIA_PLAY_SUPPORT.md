# Xash3D FWGS Xperia Play Support

This document describes the implementation of Xperia Play support for Xash3D FWGS v0.19.2.

## Features Implemented

### 1. Touchpad as Joystick Input
- The Xperia Play's touchpad is implemented as a joystick input device
- Touchpad coordinates are normalized and converted to joystick axis events
- X axis (left/right) and Y axis (forward/back) are properly mapped
- Touchpad resolution of 966x360 is correctly handled

### 2. Gamepad Button Mapping
- Circle button mapped to BACK_ALT (key 4) to prevent opening pause menu
- L1 and R1 bumpers mapped to +duck and +attack2 respectively
- Start and Select buttons mapped to pause and cancelselect
- Search button mapped to toggleconsole
- D-pad mapped to movement commands

### 3. Android 2.3.3 Support
- APK configured for Android 2.3.3 (API level 10)
- Compatible with Xperia Play's hardware and software requirements
- Optimized for ARM architecture (armeabi)

## Building the APK

### Prerequisites
1. Android NDK r10e or compatible version
2. Android SDK with API level 10 (Android 2.3.3) installed
3. Apache Ant build system
4. Xash3D FWGS engine built and available

### Build Steps
1. Set environment variables:
   ```bash
   export ANDROID_NDK=/path/to/android-ndk
   export ANDROID_SDK=/path/to/android-sdk
   ```

2. Navigate to the android_project directory:
   ```bash
   cd android_project
   ```

3. Run the build script:
   ```bash
   ./build_apk.sh
   ```

4. The resulting APK will be located at:
   ```
   bin/xash3d-xperia-play-debug.apk
   ```

## Installation and Usage

### Installing on Xperia Play
1. Enable USB debugging on your Xperia Play:
   - Settings → Applications → Development → USB debugging

2. Connect your device via USB

3. Install the APK:
   ```bash
   adb install -r bin/xash3d-xperia-play-debug.apk
   ```

### Controls
- **Touchpad**: Acts as a joystick for looking around
- **L1 Button**: Duck (+duck)
- **R1 Button**: Secondary attack (+attack2)
- **Circle Button**: Use (+use)
- **Cross Button**: Primary attack (+attack)
- **Square Button**: Jump (+jump)
- **Triangle Button**: Flashlight (impulse 100)
- **Start Button**: Pause menu
- **Select Button**: Cancel/Back
- **Search Button**: Console toggle
- **D-pad**: Movement (forward/back/left/right)

## Configuration Files

### xash3d_xperia_play.cfg
Main configuration file that sets up:
- Joystick support
- Button mappings
- Touchpad sensitivity
- Game-specific settings

### touch_default/xperia_play_touch.cfg
Default touch configuration optimized for Xperia Play's form factor:
- Touchpad areas for looking and moving
- Action buttons positioned for easy access
- Weapon selection controls

## Technical Implementation

### Java Activity (XashActivity.java)
- Handles Xperia Play specific input events
- Maps hardware buttons to game commands
- Processes touchpad events as joystick input
- Manages lifecycle events for proper resource handling

### Native Interface (xash_jni.cpp)
- JNI bridge between Java activity and native engine
- Converts touchpad coordinates to joystick axis events
- Handles button press/release events
- Manages engine lifecycle through native calls

### Android NDK Configuration
- Android.mk: Build configuration for native code
- Application.mk: NDK settings for Xperia Play compatibility
- Target platform: Android 2.3.3 (API level 10)
- Architecture: armeabi for broad device compatibility

## Testing
The implementation has been designed to work with the Xperia Play's specific hardware:
- 966x360 touchpad resolution
- Gamepad button layout
- 512MB RAM limitation
- ARMv7 processor

## Troubleshooting
- If touchpad is not responding, check that the device is properly recognized as a joystick
- If buttons are not working, verify the key mappings in xash3d_xperia_play.cfg
- For performance issues, reduce graphics settings in the game

## Limitations
- Android 2.3.3 is an older platform with limited capabilities
- Some modern Android features are not available
- Hardware acceleration may be limited on older devices