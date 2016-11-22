//
// Created by vhly[FR] on 2016/11/22.
//

#include <libavutil/md5.h>
#include <libavutil/base64.h>
#include <malloc.h>
#include <string.h>

static void test_md5() {
    struct AVMD5 *ctx = av_md5_alloc();
    av_md5_init(ctx);
    char data[16];
    data[0] = 'a';
    av_md5_update(ctx, data, 1);
    av_md5_final(ctx, data);

    int len = AV_BASE64_SIZE(16);
    char *str = (char *) malloc(len);
    memset(str, 0, len);
    if (str != NULL) {
        av_base64_encode(str, len, data, 16);
    }
}