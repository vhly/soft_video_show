package mobi.vhly.demo01;

import android.annotation.TargetApi;
import android.graphics.ImageFormat;
import android.graphics.Rect;
import android.hardware.Camera;
import android.media.CamcorderProfile;
import android.media.CameraProfile;
import android.media.MediaCodec;
import android.media.MediaCodecInfo;
import android.media.MediaCodecList;
import android.media.MediaFormat;
import android.os.Build;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.List;

@TargetApi(16)
public class HardEncodingActivity extends AppCompatActivity implements SurfaceHolder.Callback, Camera.PreviewCallback {

    private Camera mCamera;

    private MediaCodec mMediaCodec;

    private byte[] mBuffer;

    private MediaCodec.BufferInfo mOutputBufferInfo;

    private FileOutputStream mVideoFileOutput;

    private File mTargetFile;

    private long mCurrentFrame;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_hard_encoding);

        File filesDir = getFilesDir();
        String state = Environment.getExternalStorageState();
        if (state.equals(Environment.MEDIA_MOUNTED)) {
            filesDir = Environment.getExternalStorageDirectory();
            filesDir = new File(filesDir, "my-videos");
        }
        if (!filesDir.exists()) {
            filesDir.mkdirs();
        }

        mTargetFile = new File(filesDir, "myvideo.mp4");
        if (!mTargetFile.exists()) {
            try {
                mTargetFile.createNewFile();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        SurfaceView surfaceView = (SurfaceView) findViewById(R.id.hard_surface_view);
        surfaceView.getHolder().addCallback(this);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        mCamera = openFrontCamera();


        if (mCamera != null) {
            Camera.Parameters parameters = mCamera.getParameters();

            List<Camera.Size> sizes = parameters.getSupportedPreviewSizes();
            Camera.Size largestSize = getLargestSize(sizes);
            if (largestSize != null) {
                parameters.setPreviewSize(largestSize.width, largestSize.height);
            }
            parameters.setPreviewFormat(ImageFormat.NV21);
//            parameters.setFocusMode(Camera.Parameters.FOCUS_MODE_CONTINUOUS_VIDEO);
            mCamera.setParameters(parameters);
            mCamera.setDisplayOrientation(90);


            try {
                mVideoFileOutput = new FileOutputStream(mTargetFile);

//                Rect rect = holder.getSurfaceFrame();
                Camera.Size previewSize = parameters.getPreviewSize();
                int width = previewSize.width;
                int height = previewSize.height;
                mBuffer = new byte[width * height * 3 / 2]; // for
                mCamera.addCallbackBuffer(mBuffer);
                mCamera.setPreviewCallbackWithBuffer(this);
                mCamera.setPreviewDisplay(holder);
                mCamera.startPreview();

                mOutputBufferInfo = new MediaCodec.BufferInfo();

                int cc = MediaCodecList.getCodecCount();
                for (int i = 0; i < cc; i++) {
                    MediaCodecInfo codecInfo = MediaCodecList.getCodecInfoAt(i);
                    boolean encoder = codecInfo.isEncoder();
                    String name = codecInfo.getName();
                    System.out.println("name = " + name);
                    if (encoder) {
                        String[] supportedTypes = codecInfo.getSupportedTypes();
                        for (String supportedType : supportedTypes) {
                            System.out.println("supportedType = " + supportedType);
                        }
                    }
                }

                mMediaCodec = MediaCodec.createEncoderByType("video/avc");
                MediaFormat videoFormat = MediaFormat.createVideoFormat("video/avc", width, height);

                videoFormat.setInteger(MediaFormat.KEY_BIT_RATE, 125000);
                videoFormat.setInteger(MediaFormat.KEY_FRAME_RATE, 30);
                videoFormat.setInteger(MediaFormat.KEY_COLOR_FORMAT, MediaCodecInfo.CodecCapabilities.COLOR_FormatYUV420SemiPlanar);

                videoFormat.setInteger(MediaFormat.KEY_I_FRAME_INTERVAL, 5);
                // 编码形式
                mMediaCodec.configure(videoFormat, null, null, MediaCodec.CONFIGURE_FLAG_ENCODE);
                mCurrentFrame = 0;
                mMediaCodec.start();



            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private Camera openFrontCamera() {
        Camera ret = null;
        int numberOfCameras = Camera.getNumberOfCameras();
        int cameraId = -1;
        if (numberOfCameras > 0) {
            Camera.CameraInfo info = new Camera.CameraInfo();
            for (int i = 0; i < numberOfCameras; i++) {
                Camera.getCameraInfo(i, info);
                if (info.facing == Camera.CameraInfo.CAMERA_FACING_FRONT) {
                    cameraId = i;
                    break;
                }
            }
        }
        if (cameraId != -1) {
            ret = Camera.open(cameraId);
        }
        return ret;
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {


        if (mMediaCodec != null) {
            mMediaCodec.flush();
            mMediaCodec.stop();
            mMediaCodec.release();
            mMediaCodec = null;
        }

        if (mCamera != null) {
            try {
                mCamera.stopPreview();
            } catch (Exception e) {
                e.printStackTrace();
            }
            try {
                mCamera.release();
            } catch (Exception e) {
                e.printStackTrace();
            }
            mCamera = null;
        }
        if (mVideoFileOutput != null) {
            try {
                mVideoFileOutput.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
            mVideoFileOutput = null;
        }

        mOutputBufferInfo = null;
        mBuffer = null;

    }

    public void btnRecordOnClick(View view) {


    }

    @Override
    public void onPreviewFrame(byte[] data, Camera camera) {
        encodeVideo(data);
        camera.addCallbackBuffer(mBuffer);
    }

    private void encodeVideo(byte[] data) {
        if (mMediaCodec != null) {
            int index = mMediaCodec.dequeueInputBuffer(-1);
            if (index != -1) {
                ByteBuffer buffer = getInputBuffer(index);
                if (buffer != null) {
                    buffer.position(0);
                    buffer.put(data);
                    buffer.position(0);
                    System.out.println("start queue");
                    mCurrentFrame++;
                    mMediaCodec.queueInputBuffer(index, 0, data.length, mCurrentFrame, 0);

                    int outIndex = mMediaCodec.dequeueOutputBuffer(mOutputBufferInfo, -1);
                    System.out.println("outIndex = " + outIndex);
                    if (outIndex >= 0) {
                        ByteBuffer outputBuffer = getOutputBuffer(outIndex);
                        try {
                            int offset = mOutputBufferInfo.offset;
                            int size = mOutputBufferInfo.size;
                            byte[] dd = new byte[size];
                            outputBuffer.position(offset);
                            outputBuffer.get(dd, 0, size);
                            mVideoFileOutput.write(dd);
                            dd = null;
                            mMediaCodec.releaseOutputBuffer(outIndex, true);
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                }
            }
        }
    }

    private ByteBuffer getInputBuffer(int index) {
        ByteBuffer ret = null;
        if (index > -1) {
            if (Build.VERSION.SDK_INT >= 21) {
                ret = mMediaCodec.getInputBuffer(index);
            } else {
                try {
                    ret = mMediaCodec.getInputBuffers()[index];
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
        return ret;
    }

    private ByteBuffer getOutputBuffer(int index) {
        ByteBuffer ret = null;
        if (index > -1) {
            if (Build.VERSION.SDK_INT >= 21) {
                ret = mMediaCodec.getOutputBuffer(index);
            } else {
                try {
                    ret = mMediaCodec.getOutputBuffers()[index];
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
        return ret;
    }

    private static Camera.Size getLargestSize(List<Camera.Size> sizes) {
        Camera.Size ret = null;
        if (sizes != null) {
            int len = sizes.size();
            if (len > 0) {
                ret = sizes.get(0);

                for (int i = 0; i < len; i++) {
                    Camera.Size size = sizes.get(i);
                    if (size.width > ret.width && size.height > ret.height) {
                        ret = size;
                    }
                }
            }
        }
        return ret;
    }
}
