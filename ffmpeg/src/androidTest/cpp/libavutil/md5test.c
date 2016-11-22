//
// Created by vhly[FR] on 2016/11/22.
//

#include <libavutil/md5.h>
#include <libavutil/base64.h>
#include <malloc.h>
#include <string.h>
#include <jni.h>

static char* test_md5(char *data, int dLen) {
    struct AVMD5 *ctx = av_md5_alloc();
    char digest[16];
    av_md5_init(ctx);
    av_md5_update(ctx, data, dLen);
    av_md5_final(ctx, digest);

    int len = AV_BASE64_SIZE(16);
    char *str = (char *) malloc(len);
    memset(str, 0, len);
    if (str != NULL) {
        av_base64_encode(str, len, digest, 16);
    }
    return str;
}

JNIEXPORT jboolean JNICALL
    Java_mobi_vhly_ffmpeg_MyTest_md5Test(JNIEnv *env, jclass jtype, jbyteArray content, jstring b64)
{
    jboolean ret = JNI_FALSE;
    if(content != NULL && b64 != NULL){
        jsize clen = (*env)->GetArrayLength(env, content);
        jboolean bok = JNI_FALSE;
        jbyte *buf = (*env)->GetByteArrayElements(env, content, &bok);
        char *str = test_md5(buf, clen);
        if(str != NULL){
        ret = strcmp(str, b64) == 0;
            free(str);
            str = NULL;
        }
        (*env)->ReleaseByteArrayElements(env, content, buf, JNI_ABORT);
    }
    return ret;
}