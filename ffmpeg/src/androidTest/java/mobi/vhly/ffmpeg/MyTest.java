package mobi.vhly.ffmpeg;

import android.util.Base64;

import junit.framework.TestCase;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

/**
 * Created by vhly[FR].
 * <p>
 * Author: vhly[FR]
 * Email: vhly@163.com
 * Date: 2016/11/22
 */

public class MyTest extends TestCase {

    static {
        System.loadLibrary("avutil");
    }

    private static native boolean md5Test(byte[] content, String b64);

    public void testMd5() throws NoSuchAlgorithmException {
        byte[] data = "a".getBytes();
        MessageDigest digest = MessageDigest.getInstance("MD5");
        byte[] buf = digest.digest(data);
        String str = Base64.encodeToString(buf, Base64.NO_WRAP);
        assertTrue(md5Test(data, str));
    }

}
