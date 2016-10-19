//
// Created by vhly[FR] on 16/9/22.
//

#include "mobi_vhly_demo01_MainActivity.h"
#include <stdint.h>
#include <stdlib.h>
#include <x264.h>
#include <common/common.h>

#include <android/log.h>

int iNal   = 0;
x264_nal_t* pNals = NULL;

JNIEXPORT jstring JNICALL Java_mobi_vhly_demo01_MainActivity_stringFromJNI
        (JNIEnv *env, jobject clazz)
{

    x264_param_t *param = (x264_param_t *)malloc(sizeof(x264_param_t));
    x264_param_default(param);

    param->i_width = 128;
    param->i_height = 128;
    param->i_log_level  = X264_LOG_DEBUG;

    //* 设置Profile.使用MainProfile
    x264_param_apply_profile(param, x264_profile_names[1]);
    x264_t *x264 = x264_encoder_open(param);
    __android_log_print(ANDROID_LOG_DEBUG, "b_x264", "open x264 %p\n", x264);

    //* 获取允许缓存的最大帧数.
    int iMaxFrames = x264_encoder_maximum_delayed_frames(x264);
    //* 编码需要的参数.
    iNal = 0;
    pNals = NULL;
    x264_picture_t* pPicIn = (x264_picture_t *) malloc(sizeof(x264_picture_t));
    x264_picture_t* pPicOut = (x264_picture_t *) malloc(sizeof(x264_picture_t));
    x264_picture_init(pPicOut);

    // 分配输入图像的空间,根据 宽度、高度来计算
    x264_picture_alloc(pPicIn, X264_CSP_I420, param->i_width, param->i_height);
    pPicIn->img.i_csp = X264_CSP_I420;
    pPicIn->img.i_plane = 3;

//    pPicIn->img.plane



    x264_encoder_close(x264);

    const char *str = "Hello from JNI C\0";
    return (*env)->NewStringUTF(env, str);
}
