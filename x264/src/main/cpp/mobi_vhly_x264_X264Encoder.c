//
// Created by vhly[FR] on 16/9/24.
//

#include "mobi_vhly_x264_X264Encoder.h"

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
 * 本方法用于进行视频预览部分的压缩编码，每一个预览图像都是直接从摄像头获取的 YUV 格式的图片，有专门的字节数组存放；
 */
JNIEXPORT jbyteArray JNICALL
Java_mobi_vhly_x264_X264Encoder_encodePreview
        (JNIEnv *env, jclass clazz, jbyteArray data, jint prevW, jint prevH) {
    jbyteArray ret = NULL;

    if (!bDestroy) {
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

            // bitrate
            param->rc.i_bitrate = 8 * 1024 * 1024;
            param->i_fps_den = 1;
            param->i_fps_num = 15;

            param->b_vfr_input = 1; // base time

            // 流选项
            param->i_bframe = 4; // IBPBPBPBPBP
            param->b_open_gop = 0;
            param->i_bframe_pyramid = 0;
            param->i_bframe_adaptive = X264_B_ADAPT_FAST;

            // 3. 指定编码级别
            x264_param_apply_profile(param, x264_profile_names[0]);

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

        int nPicSize = prevW * prevH;
        /*
        Y数据全部从在一块，UV数据使用interleave方式存储
        YYYY
        YYYY
        UVUV
         */
//        jbyte *y = pIn->img.plane[0];
//        jbyte *v = pIn->img.plane[1];
//        jbyte *u = pIn->img.plane[2];
        memcpy(pIn->img.plane[0], buf, nPicSize);
        memcpy(pIn->img.plane[1], buf + nPicSize, nPicSize / 4);
        memcpy(pIn->img.plane[2], buf + nPicSize + nPicSize / 4, nPicSize / 4);

        int frames = x264_encoder_encode(x264, &pNal, &piNal, pIn, pOut);
        if (frames > 0) {
            __android_log_print(ANDROID_LOG_DEBUG, TAG, "%d payloads gen\n", piNal);
            for (ic = 0; ic < piNal; ic++) {
                if (!bDestroy) {
                    if (file != NULL) {
                        size_t dd = fwrite(pNal[ic].p_payload, (size_t) pNal[ic].i_payload, 1,
                                           file);
                    }
                }
            }
        }
    }else{
        int i = 0, j;
        int cret = 0;
        //flush encoder
        while (1) {
            cret = x264_encoder_encode(x264, &pNal, &piNal, NULL, pOut);
            if (cret == 0) {
                break;
            }
            if(file == NULL){
                break;
            }
            printf("Flush 1 frame.\n");
            for (j = 0; j < piNal; ++j) {
                fwrite(pNal[j].p_payload, 1, pNal[j].i_payload, file);
            }
            i++;
        }

        if(file != NULL){
            fclose(file);
            file = NULL;
        }

        x264_encoder_close(x264);
        x264 = NULL;
        x264_picture_clean(pIn);

        free(pIn);
        free(pOut);
    }
    return ret;
}


JNIEXPORT jboolean JNICALL
Java_mobi_vhly_x264_X264Encoder_initEncoder(JNIEnv *env, jclass type, jstring fileName_) {
    jboolean ret = JNI_FALSE;
    // 获取输出的文件绝对路径
    const char *fileName = (*env)->GetStringUTFChars(env, fileName_, 0);
    if (bDestroy) {

        if (x264 != NULL) {
            x264_encoder_close(x264);
            x264 = NULL;
        }

        // 打开一个文件，进行输出，file 是静态变量，需要在使用完成后进行关闭
        file = fopen(fileName, "wb");
        bDestroy = JNI_FALSE;
    }
    (*env)->ReleaseStringUTFChars(env, fileName_, fileName);
    return ret;
}

JNIEXPORT void JNICALL
Java_mobi_vhly_x264_X264Encoder_destroyEncoder(JNIEnv *env, jclass type) {

    // TODO
    if (!bDestroy) {
        bDestroy = JNI_TRUE;
    }
}

JNIEXPORT jlong JNICALL
Java_mobi_vhly_x264_X264Encoder_convertYuv2H264(JNIEnv *env, jclass type, jstring yuvFileName_,
                                                jstring h264FileName_) {

    jlong ret = 0;

    const char *yuvFileName = (*env)->GetStringUTFChars(env, yuvFileName_, 0);
    const char *h264FileName = (*env)->GetStringUTFChars(env, h264FileName_, 0);

    // TODO 进行视频的转码，来看一下是否是代码的问题导致视频转换不好；

    FILE *yuvFile = fopen(yuvFileName, "rb");
    FILE *h264File = fopen(h264FileName, "wb");

    // 参考 http://blog.csdn.net/leixiaohua1020/article/details/42078645
    // yuv source:  http://trace.eas.asu.edu/yuv/index.html

    // yuv:420

    int y_size;
    int i, j;

    // 默认转码所有的帧
    int frame_num = 0;
    // 格式为 yuv420
    int csp = X264_CSP_I420;
    // 视频宽高 352x288
    int width = 352, height = 288;

    int iNal = 0;
    x264_nal_t *pNals = NULL;
    x264_t *pHandle = NULL;
    // 帧输入
    x264_picture_t *pPic_in = (x264_picture_t *) malloc(sizeof(x264_picture_t));
    // 帧转换输出
    x264_picture_t *pPic_out = (x264_picture_t *) malloc(sizeof(x264_picture_t));
    // 创建转码参数
    x264_param_t *pParam = (x264_param_t *) malloc(sizeof(x264_param_t));

    //Check
    if (yuvFile == NULL || h264File == NULL) {
        printf("Error open files.\n");
        return -1;
    }

    // 默认参数 并且指定宽高
    x264_param_default(pParam);
    pParam->i_width = width;
    pParam->i_height = height;
    /*
    //Param
    pParam->i_log_level  = X264_LOG_DEBUG;
    pParam->i_threads  = X264_SYNC_LOOKAHEAD_AUTO;
    pParam->i_frame_total = 0;
    pParam->i_keyint_max = 10;
    pParam->i_bframe  = 5;
    pParam->b_open_gop  = 0;
    pParam->i_bframe_pyramid = 0;
    pParam->rc.i_qp_constant=0;
    pParam->rc.i_qp_max=0;
    pParam->rc.i_qp_min=0;
    pParam->i_bframe_adaptive = X264_B_ADAPT_TRELLIS;
    pParam->i_fps_den  = 1;
    pParam->i_fps_num  = 25;
    pParam->i_timebase_den = pParam->i_fps_num;
    pParam->i_timebase_num = pParam->i_fps_den;
    */
    pParam->i_csp = csp;
    // HIGH 444
    x264_param_apply_profile(pParam, x264_profile_names[5]);

    // 打开编码器
    pHandle = x264_encoder_open(pParam);

    // 初始化帧图像输出
    x264_picture_init(pPic_out);
    // 分配生成 输入图像的空间
    x264_picture_alloc(pPic_in, csp, pParam->i_width, pParam->i_height);

    //ret = x264_encoder_headers(pHandle, &pNals, &iNal);

    y_size = pParam->i_width * pParam->i_height;
    //detect frame number
    if (frame_num == 0) {
        // 获取文件长度，并且根据输入的 YUV采样方式 来计算帧数
        fseek(yuvFile, 0, SEEK_END);
        switch (csp) {
            case X264_CSP_I444:
                frame_num = ftell(yuvFile) / (y_size * 3);
                break;
            case X264_CSP_I420:
                frame_num = ftell(yuvFile) / (y_size * 3 / 2);
                break;
            default:
                printf("Colorspace Not Support.\n");
                return -1;
        }
        fseek(yuvFile, 0, SEEK_SET);
    }

    //Loop to Encode
    for (i = 0; i < frame_num; i++) {
        switch (csp) {
            case X264_CSP_I444: { // 采样YUV444 每一帧的数据都是按照 [YYYYYYYYYY][UUUUUUUUU][VVVVVVVVV] 形式
                fread(pPic_in->img.plane[0], y_size, 1, yuvFile);         //Y
                fread(pPic_in->img.plane[1], y_size, 1, yuvFile);         //U
                fread(pPic_in->img.plane[2], y_size, 1, yuvFile);         //V
                break;
            }
            case X264_CSP_I420: {  // 采样  YUV420    [YYYY][U][V]
                fread(pPic_in->img.plane[0], y_size, 1, yuvFile);         //Y
                fread(pPic_in->img.plane[1], y_size / 4, 1, yuvFile);     //U
                fread(pPic_in->img.plane[2], y_size / 4, 1, yuvFile);     //V
                break;
            }
            default: {
                printf("Colorspace Not Support.\n");
                return -1;
            }
        }
        pPic_in->i_pts = i;

        // 编码
        ret = x264_encoder_encode(pHandle, &pNals, &iNal, pPic_in, pPic_out);
        if (ret < 0) {
            printf("Error.\n");
            return -1;
        }

        printf("Succeed encode frame: %5d\n", i);

        for (j = 0; j < iNal; ++j) {
            fwrite(pNals[j].p_payload, 1, pNals[j].i_payload, h264File);
        }
    }
    // 此处把剩余的数据全部存储，因为在加入到 encoder的时候，会进行压缩，延迟输出
    i = 0;
    //flush encoder
    while (1) {
        ret = x264_encoder_encode(pHandle, &pNals, &iNal, NULL, pPic_out);
        if (ret == 0) {
            break;
        }
        printf("Flush 1 frame.\n");
        for (j = 0; j < iNal; ++j) {
            fwrite(pNals[j].p_payload, 1, pNals[j].i_payload, h264File);
        }
        i++;
    }
    x264_picture_clean(pPic_in);
    x264_encoder_close(pHandle);
    pHandle = NULL;

    free(pPic_in);
    free(pPic_out);
    free(pParam);

    fclose(yuvFile);
    fclose(h264File);

    ret = frame_num;


    (*env)->ReleaseStringUTFChars(env, yuvFileName_, yuvFileName);
    (*env)->ReleaseStringUTFChars(env, h264FileName_, h264FileName);

    return ret;
}