package in.celest.xash3d;

import android.app.Activity;
import android.os.Bundle;
import android.view.WindowManager;
import android.view.Window;
import android.content.res.AssetManager;
import android.content.Context;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.view.Gravity;
import android.view.InputDevice;
import android.view.MotionEvent;
import android.view.KeyEvent;
import android.util.Log;

public class XashActivity extends Activity {
    private static final String TAG = "XashActivity";
    
    // Load the native library
    static {
        System.loadLibrary("xash");
    }
    
    private native int nativeInit(String[] arguments);
    private native void nativeSetPause(int pause);
    private native void nativeUnPause();
    private native void onNativeResize(int x, int y);
    private native void nativeKey(int down, int code);
    private native void nativeTouch(int finger, int action, float x, float y);
    private native void nativeTouchpad(int finger, int action, float x, float y);
    private native void nativeString(String string);
    private native void nativeMouseMove(float x, float y);
    private native void nativeBall(int id, byte ball, short xrel, short yrel);
    private native void nativeHat(int id, byte hat, byte key, boolean down);
    private native void nativeAxis(int id, byte axis, short val);
    private native void nativeJoyButton(int id, byte button, boolean down);
    private native void nativeJoyAdd(int id);
    private native void nativeJoyDel(int id);
    private native void nativeOnResume();
    private native void nativeOnFocusChange();
    private native void nativeOnPause();
    private native void nativeOnDestroy();
    private native int setenv(String key, String value, boolean overwrite);
    private native int nativeTestWritePermission(String path);
    
    // Xperia Play specific methods
    public static native void swapBuffers();
    public static native void toggleEGL(int enabled);
    public static native void showKeyboard(int show);
    public static native void vibrate(int duration);
    public static native void messageBox(String title, String text);
    public static native boolean createGLContext(int stencilBits);
    public static native int getGLAttribute(int attr);
    public static native boolean deleteGLContext();
    public static native void engineThreadNotify();
    public static native void setTitle(String title);
    public static native void setIcon(String icon);
    public static native String getAndroidID();
    public static native void saveID(String id);
    public static native String loadID();
    public static native void showMouse(int show);
    public static native void shellExecute(String path);
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        // Set up the window
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                             WindowManager.LayoutParams.FLAG_FULLSCREEN);
        
        // Create the layout
        RelativeLayout layout = new RelativeLayout(this);
        setContentView(layout);
        
        // Initialize the engine
        String[] args = {"-game", "valve"};
        int result = nativeInit(args);
        if (result != 0) {
            Log.e(TAG, "Failed to initialize native engine with error code: " + result);
        }
    }
    
    @Override
    protected void onResume() {
        super.onResume();
        nativeOnResume();
    }
    
    @Override
    protected void onPause() {
        super.onPause();
        nativeOnPause();
    }
    
    @Override
    protected void onDestroy() {
        super.onDestroy();
        nativeOnDestroy();
    }
    
    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);
        nativeOnFocusChange();
    }
    
    @Override
    public boolean dispatchGenericMotionEvent(MotionEvent event) {
        // Handle Xperia Play touchpad events
        if ((event.getSource() & InputDevice.SOURCE_CLASS_JOYSTICK) != 0) {
            // Handle joystick/touchpad motion events
            int deviceId = event.getDeviceId();
            
            // Handle touchpad as joystick axis
            float x = event.getX();
            float y = event.getY();
            
            // Normalize coordinates to touchpad resolution (966x360)
            // Xperia Play touchpad resolution as documented in XPERIA_PLAY_SUPPORT.md
            nativeTouchpad(0, event.getAction(), x * 966, y * 360);
            
            return true;
        }
        
        // Handle other motion events (touchscreen, etc.)
        if ((event.getSource() & InputDevice.SOURCE_TOUCHSCREEN) != 0) {
            int action = event.getActionMasked();
            int pointerIndex = event.getActionIndex();
            int pointerId = event.getPointerId(pointerIndex);
            
            switch (action) {
                case MotionEvent.ACTION_DOWN:
                case MotionEvent.ACTION_POINTER_DOWN:
                    nativeTouch(pointerId, 0, event.getX(pointerIndex), event.getY(pointerIndex));
                    break;
                case MotionEvent.ACTION_UP:
                case MotionEvent.ACTION_POINTER_UP:
                    nativeTouch(pointerId, 1, event.getX(pointerIndex), event.getY(pointerIndex));
                    break;
                case MotionEvent.ACTION_MOVE:
                    // Handle multiple pointers
                    for (int i = 0; i < event.getPointerCount(); i++) {
                        int pid = event.getPointerId(i);
                        nativeTouch(pid, 2, event.getX(i), event.getY(i));
                    }
                    break;
            }
            
            return true;
        }
        
        return super.dispatchGenericMotionEvent(event);
    }
    
    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        int keyCode = event.getKeyCode();
        int action = event.getAction();
        boolean down = (action == KeyEvent.ACTION_DOWN);
        
        // Map Xperia Play specific buttons
        switch (keyCode) {
            case KeyEvent.KEYCODE_BACK:
                // Circle button should be treated as BACK_ALT
                nativeKey(down ? 1 : 0, 4); // BACK_ALT key code
                return true;
                
            case KeyEvent.KEYCODE_BUTTON_L1:
                nativeKey(down ? 1 : 0, keyCode);
                return true;
                
            case KeyEvent.KEYCODE_BUTTON_R1:
                nativeKey(down ? 1 : 0, keyCode);
                return true;
                
            case KeyEvent.KEYCODE_BUTTON_START:
                nativeKey(down ? 1 : 0, keyCode);
                return true;
                
            case KeyEvent.KEYCODE_BUTTON_SELECT:
                nativeKey(down ? 1 : 0, keyCode);
                return true;
                
            case KeyEvent.KEYCODE_SEARCH:
                nativeKey(down ? 1 : 0, keyCode);
                return true;
                
            default:
                // Handle other keys normally
                nativeKey(down ? 1 : 0, keyCode);
                return true;
        }
    }
}