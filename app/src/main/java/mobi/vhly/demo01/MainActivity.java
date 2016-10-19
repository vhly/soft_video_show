package mobi.vhly.demo01;

import android.Manifest;
import android.content.pm.PackageManager;
import android.graphics.ImageFormat;
import android.graphics.Rect;
import android.hardware.Camera;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.WindowManager;

import java.io.File;
import java.io.IOException;

import mobi.vhly.x264.X264Encoder;

public class MainActivity extends AppCompatActivity
        implements SurfaceHolder.Callback, Camera.PreviewCallback, Runnable {

    private int mPrevWidth;
    private int mPrevHeight;
    private Camera mCamera;

    private boolean hasExit;
    //    private Vector<byte[]> mQueue;
    private final String lock = "lock";
    private boolean running;

    private byte[] mPrevBuf;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

//        mQueue = new Vector<>();

        Thread thread = new Thread(this);
        thread.start();

        int st = ActivityCompat.checkSelfPermission(this, Manifest.permission.CAMERA);

        if (st == PackageManager.PERMISSION_GRANTED) {
            mCamera = Camera.open();
            SurfaceView surfaceView = (SurfaceView) findViewById(R.id.prev_view);
            surfaceView.getHolder().addCallback(this);
        } else {
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.CAMERA}, 998);
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        if (requestCode == 998) {
            if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                mCamera = Camera.open();
                SurfaceView surfaceView = (SurfaceView) findViewById(R.id.prev_view);
                initCamera(surfaceView.getHolder());
            }
        }
    }


    private void initCamera(SurfaceHolder holder) {
        if (!hasExit) {
            Surface surface = holder.getSurface();
            if (surface != null && surface.isValid() && mCamera != null) {
//                mQueue.clear();
                try {

                    Camera.Parameters parameters = mCamera.getParameters();
                    parameters.setPreviewFormat(ImageFormat.YV12);
//                    parameters.setPictureFormat(PixelFormat.YCbCr_420_SP);
//                    parameters.setPreviewFpsRange(30, 40);
                    parameters.setPreviewFrameRate(30);
                    mCamera.setParameters(parameters);

                    mCamera.setDisplayOrientation(90);
                    Rect surfaceFrame = holder.getSurfaceFrame();
                    if (mPrevBuf == null) {
                        mPrevBuf = new byte[surfaceFrame.width() * surfaceFrame.height() * 3 / 2];
                    }
                    mCamera.addCallbackBuffer(mPrevBuf);
                    mCamera.setPreviewCallbackWithBuffer(this);
                    mCamera.setPreviewDisplay(holder);
                    mCamera.startPreview();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        File filesDir = getFilesDir();
        if (!filesDir.exists()) {
            filesDir.mkdirs();
        }

        File targetFile = new File(filesDir, "myvideo.264");
        if (!targetFile.exists()) {
            try {
                targetFile.createNewFile();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        X264Encoder.initEncoder(targetFile.getAbsolutePath());
        initCamera(holder);
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        mPrevHeight = height;
        mPrevWidth = width;
        if (mCamera != null) {
            Camera.Parameters parameters = mCamera.getParameters();
            parameters.setPreviewSize(mPrevWidth, mPrevHeight);
        }
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        if (holder.getSurface() != null) {
            try {
                if (mCamera != null) {
                    mCamera.stopPreview();
                    mCamera.setPreviewCallback(null);
                    hasExit = true;
                    try {
                        mCamera.release();
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                    mCamera = null;
                }
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
    }


    @Override
    protected void onDestroy() {
        running = false;
//        mQueue.clear();
        Thread.yield();
        X264Encoder.destroyEncoder();
        super.onDestroy();
    }

    @Override
    public void onPreviewFrame(byte[] data, Camera camera) {
        synchronized (lock) {
//            mQueue.add(data);
            lock.notify();
            camera.addCallbackBuffer(mPrevBuf);
        }
    }

    @Override
    public void run() {
        running = true;
        try {
            while (running) {
                synchronized (lock) {
                    lock.wait(5);
                }
//                if(!mQueue.isEmpty()){
//                    byte[] data = mQueue.remove(0);
                byte[] data = mPrevBuf;
                if (mPrevWidth > 0 && mPrevHeight > 0 && running) {
                    try {
                        Camera.Size size = mCamera.getParameters().getPreviewSize();
                        X264Encoder.encodePreview(data, size.width, size.height);
                    } catch (Throwable e) {
                        e.printStackTrace();
                    }
                }
//                }
            }
        } catch (InterruptedException ex) {
            ex.printStackTrace();
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

}
