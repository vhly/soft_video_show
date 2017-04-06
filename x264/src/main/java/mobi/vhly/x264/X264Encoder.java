package mobi.vhly.x264;

/**
 * Created by vhly[FR].
 * <p>
 * Author: vhly[FR]
 * Email: vhly@163.com
 * Date: 16/9/24
 */

public final class X264Encoder {

    public native static boolean initEncoder(String fileName);

    public native static byte[] encodePreview(byte[] data, int w, int h);

    public native static void destroyEncoder();

    /**
     * 文件转换方法，需要在子线程完成
     * @param yuvFileName
     * @param h264FileName
     * @return
     */
    public native static long convertYuv2H264(String yuvFileName, String h264FileName);

    static {
        System.loadLibrary("x264");
    }

}
