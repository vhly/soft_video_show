//
// Created by vhly[FR] on 16/9/24.
//

#include "mobi_vhly_demo01_X264Encoder.h"

#include <stdio.h>
#include <stdlib.h>

#include <x264.h>
#include <common/common.h>

#include <android/log.h>

const char *TAG = "X264Encoder\0";

static x264_t *x264 = NULL;
static x264_nal_t *pNal = NULL;
static int piNal = 0;

static x264_picture_t *pIn = NULL;
static x264_picture_t *pOut = NULL;

static FILE *file;

static jboolean bDestroy = JNI_TRUE;

/*
 * Class:     mobi_vhly_demo01_X264Encoder
 * Method:    encodePreview
 * Signature: ([BII)[B
 */
JNIEXPORT jbyteArray JNICALL Java_mobi_vhly_demo01_X264Encoder_encodePreview
        (JNIEnv *env, jclass clazz, jbyteArray data, jint prevW, jint prevH) {
    jbyteArray ret = NULL;

    if(!bDestroy) {
        if (x264 == NULL) {
            // 1. 初始化 x264参数

            x264_param_t *param = (x264_param_t *) malloc(sizeof(x264_param_t));
            x264_param_default(param);

            // 2. 设置参数, 宽高必须设置
            param->i_width = prevW;
            param->i_height = prevH;

            // 单线程
            param->i_threads = 1;

            // 日志级别
            param->i_log_level = X264_LOG_DEBUG;

            param->i_frame_total = 0; //* 编码总帧数.不知道用0.
            param->i_keyint_max = 100; // default is 250

            param->i_fps_num = 30;

            // 流选项
            param->i_bframe = 4; // IBPBPBPBPBP
            param->b_open_gop = 0;
            param->i_bframe_pyramid = 0;
            param->i_bframe_adaptive = X264_B_ADAPT_FAST;

            // 3. 指定编码级别
            x264_param_apply_profile(param, x264_profile_names[1]);

            // 4. 创建 x264 实例

            x264 = x264_encoder_open(param);

            pIn = (x264_picture_t *) malloc(sizeof(x264_picture_t));
            pOut = (x264_picture_t *) malloc(sizeof(x264_picture_t));

            x264_picture_alloc(pIn, X264_CSP_I420, x264->param.i_width, x264->param.i_height);
            pIn->img.i_csp = X264_CSP_I420;
            pIn->img.i_plane = 3;

            // 准备输出数据
            x264_picture_init(pOut);
        }


        // load data to pIn->img

        int ic = 0;

        jboolean bCopy = JNI_FALSE;
        jbyte *buf = (*env)->GetByteArrayElements(env, data, &bCopy);

        int nPicSize=prevW*prevH;
        /*
        Y数据全部从在一块，UV数据使用interleave方式存储
        YYYY
        YYYY
        UVUV
         */
        jbyte * y=pIn->img.plane[0];
        jbyte * v=pIn->img.plane[1];
        jbyte * u=pIn->img.plane[2];
        memcpy(pIn->img.plane[0],buf,nPicSize);
        for (ic=0;ic<nPicSize/4;ic++)
        {
            *(u+ic)=*(buf+nPicSize+ic*2);
            *(v+ic)=*(buf+nPicSize+ic*2+1);
        }

        int frames = x264_encoder_encode(x264, &pNal, &piNal, pIn, pOut);
        if (frames > 0) {
            __android_log_print(ANDROID_LOG_DEBUG, TAG, "%d payloads gen\n", piNal);

//            size_t dd = fwrite(pNal->p_payload, (size_t) frames, 1, file);
//                        if(dd){
//                            __android_log_print(ANDROID_LOG_DEBUG, TAG, "payload data length %d\n",
//                                                frames);
//                        }

            for (ic = 0; ic < piNal; ic++) {
                if(!bDestroy){
                    if(file != NULL){
                        size_t dd = fwrite(pNal[ic].p_payload, (size_t) pNal[ic].i_payload, 1, file);
                        if(dd){
                            __android_log_print(ANDROID_LOG_DEBUG, TAG, "payload data count %d\n",
                                                pNal[ic].i_payload);
                        }
                    }
                }
            }
        }
    }
    return ret;
}


JNIEXPORT jboolean JNICALL
Java_mobi_vhly_demo01_X264Encoder_initEncoder(JNIEnv *env, jclass type, jstring fileName_) {
    jboolean ret = JNI_FALSE;
    const char *fileName = (*env)->GetStringUTFChars(env, fileName_, 0);
    if(bDestroy) {

        if(x264 != NULL){
            x264_encoder_close(x264);
            x264 = NULL;
        }

        // TODO
        file = fopen(fileName, "wb");
        bDestroy = JNI_FALSE;
    }
    (*env)->ReleaseStringUTFChars(env, fileName_, fileName);
    return ret;
}

JNIEXPORT void JNICALL
Java_mobi_vhly_demo01_X264Encoder_destroyEncoder(JNIEnv *env, jclass type) {

    // TODO
    if(!bDestroy) {
        if (file != NULL) {
            fclose(file);
            file = NULL;
        }

        bDestroy = JNI_TRUE;

//        if (x264 != NULL) {
//            x264_encoder_close(x264);
//            x264 = NULL;
//        }

    }
}