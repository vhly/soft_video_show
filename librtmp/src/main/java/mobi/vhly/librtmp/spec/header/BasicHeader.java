package mobi.vhly.librtmp.spec.header;

/**
 * Created by vhly[FR].
 * <p>
 * Author: vhly[FR]
 * Email: vhly@163.com
 * Date: 16/10/8
 */

public class BasicHeader {

    public static final int CHUNK_MESSAGE_TYPE_0 = 0;
    public static final int CHUNK_MESSAGE_TYPE_1 = 1;
    public static final int CHUNK_MESSAGE_TYPE_2 = 2;
    public static final int CHUNK_MESSAGE_TYPE_3 = 3;

    /**
     * Chunk Message Type
     */
    private byte fmt;

    private short chunkStreamId;
}
