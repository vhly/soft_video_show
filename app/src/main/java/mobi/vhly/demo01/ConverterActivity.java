package mobi.vhly.demo01;

import android.Manifest;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.os.Environment;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

import mobi.vhly.x264.X264Encoder;

public class ConverterActivity extends AppCompatActivity implements Runnable{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_converter);

        int st = ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE);
        if(st != PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 998);
        }else{
            startThread();
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        if(requestCode == 998){
            if(grantResults[0] == PackageManager.PERMISSION_GRANTED){
                startThread();
            }
        }
    }

    private void startThread(){
        Thread thread = new Thread(this);
        thread.start();
    }

    @Override
    public void run() {
        AssetManager assets = getAssets();
        try {
            InputStream stream = assets.open("akiyo_cif.yuv");
            if (stream != null) {
                String state = Environment.getExternalStorageState();
                if(Environment.MEDIA_MOUNTED.equals(state)) {
                    File filesDir = getExternalFilesDir(null);
                    if(filesDir == null){
                        filesDir = getFilesDir();
                    }
                    if(!filesDir.exists()){
                        filesDir.mkdirs();
                    }
                    File sourceFile = new File(filesDir, "source.yuv");
                    if(!sourceFile.exists()){
                        sourceFile.createNewFile();
                    }
                    FileOutputStream out = new FileOutputStream(sourceFile);

                    byte[] buf = new byte[1024];
                    int len;
                    while (true) {
                        len = stream.read(buf);
                        if (len == -1) {
                            break;
                        }
                        out.write(buf, 0, len);
                    }

                    out.close();

                    stream.close();

                    // TODO: 转码

                    File h264File = new File(filesDir, "target.h264");
                    if(!h264File.exists()){
                        h264File.createNewFile();
                    }
                    System.out.println("start yuv convert...");
                    long l = X264Encoder.convertYuv2H264(sourceFile.getAbsolutePath(), h264File.getAbsolutePath());
                    System.out.println("l = " + l);

                }

            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
