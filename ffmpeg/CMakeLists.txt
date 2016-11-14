cmake_minimum_required(VERSION 3.4.1)

include_directories( "src/main/cpp/" )

add_library (
        libavutil

        SHARED

        # for libavutil
        src/main/cpp/libavutil/dict.c
        src/main/cpp/libavutil/log.c
        src/main/cpp/libavutil/log2_tab.c
        src/main/cpp/libavutil/avstring.c
        src/main/cpp/libavutil/error.c
        src/main/cpp/libavutil/mem.c
        src/main/cpp/libavutil/rational.c
        src/main/cpp/libavutil/mathematics.c
        src/main/cpp/libavutil/intmath.c
        src/main/cpp/libavutil/bprint.c
        src/main/cpp/libavutil/cpu.c
        src/main/cpp/libavutil/opt.c
        src/main/cpp/libavutil/samplefmt.c
        src/main/cpp/libavutil/channel_layout.c
        src/main/cpp/libavutil/buffer.c
        src/main/cpp/libavutil/atomic.c
        src/main/cpp/libavutil/eval.c
        src/main/cpp/libavutil/parseutils.c
        src/main/cpp/libavutil/pixdesc.c
        src/main/cpp/libavutil/random_seed.c
        src/main/cpp/libavutil/sha.c
        src/main/cpp/libavutil/sha512.c
        src/main/cpp/libavutil/reverse.c
        src/main/cpp/libavutil/time.c

        src/main/cpp/libavutil/adler32.c
        src/main/cpp/libavutil/aes_ctr.c
        src/main/cpp/libavutil/aes.c
        src/main/cpp/libavutil/base64.c
        src/main/cpp/libavutil/blowfish.c
        src/main/cpp/libavutil/camellia.c
        src/main/cpp/libavutil/cast5.c
        src/main/cpp/libavutil/color_utils.c
        src/main/cpp/libavutil/crc.c
        src/main/cpp/libavutil/des.c
        src/main/cpp/libavutil/hash.c
        src/main/cpp/libavutil/hmac.c
        src/main/cpp/libavutil/md5.c
        src/main/cpp/libavutil/rc4.c
        src/main/cpp/libavutil/twofish.c
        src/main/cpp/libavutil/tea.c
        src/main/cpp/libavutil/ripemd.c
        src/main/cpp/libavutil/murmur3.c
        src/main/cpp/libavutil/xtea.c

        src/main/cpp/libavutil/lzo.c

        src/main/cpp/libavutil/lfg.c
        src/main/cpp/libavutil/frame.c
        src/main/cpp/libavutil/imgutils.c

        # for libavcodec
        src/main/cpp/libavutil/float_dsp.c
        src/main/cpp/libavutil/fixed_dsp.c
        src/main/cpp/libavutil/audio_fifo.c
        src/main/cpp/libavutil/fifo.c

        # for codec
        src/main/cpp/libavutil/display.c
        src/main/cpp/libavutil/mastering_display_metadata.c
        src/main/cpp/libavutil/stereo3d.c

)


add_library (
        libavformat

        SHARED

        # for libavutil
        src/main/cpp/libavformat/avio.c
        src/main/cpp/libavformat/aviobuf.c
        src/main/cpp/libavformat/os_support.c
        src/main/cpp/libavformat/url.c
        src/main/cpp/libavformat/urldecode.c
        src/main/cpp/libavformat/network.c
        # src/main/cpp/libavformat/tls_gnutls.c
        # src/main/cpp/libavformat/tls_openssl.c
        # src/main/cpp/libavformat/tls_securetransport.c
        # src/main/cpp/libavformat/tls_schannel.c
        src/main/cpp/libavformat/tls.c
        src/main/cpp/libavformat/network.c
        src/main/cpp/libavformat/flvdec.c
        src/main/cpp/libavformat/flvenc.c
        src/main/cpp/libavformat/rtmpcrypt.c
        src/main/cpp/libavformat/rtmpdh.c
        src/main/cpp/libavformat/rtmphttp.c
        src/main/cpp/libavformat/rtmppkt.c
        src/main/cpp/libavformat/rtmpproto.c
        src/main/cpp/libavformat/avc.c
        src/main/cpp/libavformat/metadata.c
)

add_library (
        libavcodec
        SHARED
        src/main/cpp/libavcodec/aacenctab.c
        src/main/cpp/libavcodec/imdct15.c
        src/main/cpp/libavcodec/avfft.c
        src/main/cpp/libavcodec/fft_fixed_32.c
        src/main/cpp/libavcodec/fft_fixed.c
        src/main/cpp/libavcodec/fft_float.c
        src/main/cpp/libavcodec/fft_init_table.c
        # src/main/cpp/libavcodec/fft_template.c
        src/main/cpp/libavcodec/rdft.c
        src/main/cpp/libavcodec/opus_celt.c
        src/main/cpp/libavcodec/opus_parser.c
        src/main/cpp/libavcodec/opus_rc.c
        src/main/cpp/libavcodec/opus_silk.c
        src/main/cpp/libavcodec/opus.c
        src/main/cpp/libavcodec/opusdec.c
        src/main/cpp/libavcodec/opustab.c
        src/main/cpp/libavcodec/dct.c
        src/main/cpp/libavcodec/dct32_fixed.c
        src/main/cpp/libavcodec/dct32_float.c
        # src/main/cpp/libavcodec/dct32_template.c
        src/main/cpp/libavcodec/dctref.c
        src/main/cpp/libavcodec/mpeg4audio.c

        # for swr
        src/main/cpp/libavcodec/sbrdsp_fixed.c
        # src/main/cpp/libavcodec/sbrdsp_template.c
        src/main/cpp/libavcodec/sbrdsp.c
        src/main/cpp/libavcodec/parser.c
        src/main/cpp/libavcodec/vorbis_data.c
        src/main/cpp/libavcodec/vorbis_parser.c
        src/main/cpp/libavcodec/vorbis.c
        src/main/cpp/libavcodec/vorbisdec.c
        src/main/cpp/libavcodec/vorbisdsp.c
        src/main/cpp/libavcodec/vorbisenc.c
        src/main/cpp/libavcodec/aacps_fixed_tablegen.c
        src/main/cpp/libavcodec/aacps_fixed.c
        src/main/cpp/libavcodec/aacps_float.c
        # src/main/cpp/libavcodec/aacps_tablegen_template.c
        src/main/cpp/libavcodec/aacps_tablegen.c
        src/main/cpp/libavcodec/aacps.c
        src/main/cpp/libavcodec/aacpsdata.c
        src/main/cpp/libavcodec/aacpsdsp_fixed.c
        src/main/cpp/libavcodec/aacpsdsp_float.c
        # src/main/cpp/libavcodec/aacpsdsp_template.c
        src/main/cpp/libavcodec/aacpsy.c
        src/main/cpp/libavcodec/xiph.c
        src/main/cpp/libavcodec/aactab.c
        src/main/cpp/libavcodec/psymodel.c
        src/main/cpp/libavcodec/iirfilter.c
        src/main/cpp/libavcodec/bitstream_filter.c
        src/main/cpp/libavcodec/bitstream_filters.c
        src/main/cpp/libavcodec/bitstream.c
        src/main/cpp/libavcodec/bsf_list.c
        src/main/cpp/libavcodec/bsf.c
        src/main/cpp/libavcodec/aac_adtstoasc_bsf.c
        src/main/cpp/libavcodec/aacadtsdec.c
        src/main/cpp/libavcodec/aac_ac3_parser.c
        src/main/cpp/libavcodec/aac_adtstoasc_bsf.c
        src/main/cpp/libavcodec/chomp_bsf.c
        src/main/cpp/libavcodec/dump_extradata_bsf.c
        src/main/cpp/libavcodec/dca_core_bsf.c
        src/main/cpp/libavcodec/h264_mp4toannexb_bsf.c
        src/main/cpp/libavcodec/hevc_mp4toannexb_bsf.c
        src/main/cpp/libavcodec/imx_dump_header_bsf.c
        src/main/cpp/libavcodec/mjpeg2jpeg_bsf.c
        src/main/cpp/libavcodec/mjpega_dump_header_bsf.c
        src/main/cpp/libavcodec/mp3_header_decompress_bsf.c
        src/main/cpp/libavcodec/mpeg4_unpack_bframes_bsf.c
        src/main/cpp/libavcodec/movsub_bsf.c
        src/main/cpp/libavcodec/noise_bsf.c
        src/main/cpp/libavcodec/remove_extradata_bsf.c
        src/main/cpp/libavcodec/vp9_superframe_bsf.c

        # HEVC
        src/main/cpp/libavcodec/hevc_cabac.c
        src/main/cpp/libavcodec/hevc_data.c
        src/main/cpp/libavcodec/hevc_filter.c
        src/main/cpp/libavcodec/hevc_mvs.c
        src/main/cpp/libavcodec/hevc_parse.c
        src/main/cpp/libavcodec/hevc_parser.c
        src/main/cpp/libavcodec/hevc_ps_enc.c
        src/main/cpp/libavcodec/hevc_ps.c
        src/main/cpp/libavcodec/hevc_refs.c
        src/main/cpp/libavcodec/hevc_sei.c
        src/main/cpp/libavcodec/hevc.c
        src/main/cpp/libavcodec/profiles.c
        # src/main/cpp/libavcodec/hpel_template.c
        src/main/cpp/libavcodec/hpeldsp.c
        src/main/cpp/libavcodec/pel_template.c
        src/main/cpp/libavcodec/fdctdsp.c
        src/main/cpp/libavcodec/faandct.c

        # src/main/cpp/libavcodec/bit_depth_template.c
        # src/main/cpp/libavcodec/hevcdsp_template.c
        src/main/cpp/libavcodec/hevcdsp.c
        # src/main/cpp/libavcodec/hevcpred_template.c
        src/main/cpp/libavcodec/hevcpred.c
        src/main/cpp/libavcodec/bswapdsp.c
        src/main/cpp/libavcodec/cabac.c
        src/main/cpp/libavcodec/h2645_parse.c
        src/main/cpp/libavcodec/videodsp_template.c
        src/main/cpp/libavcodec/videodsp.c

        # JPEG
        src/main/cpp/libavcodec/jpegtables.c
        src/main/cpp/libavcodec/mjpeg_parser.c
        src/main/cpp/libavcodec/mjpegbdec.c
        src/main/cpp/libavcodec/mjpegbdec.c
        src/main/cpp/libavcodec/mjpegdec.c
        src/main/cpp/libavcodec/mjpegenc_common.c
        src/main/cpp/libavcodec/mjpegenc.c
        src/main/cpp/libavcodec/golomb.c
        src/main/cpp/libavcodec/blockdsp.c
        src/main/cpp/libavcodec/error_resilience.c
        src/main/cpp/libavcodec/idctdsp.c
        src/main/cpp/libavcodec/xvididct.c
        # src/main/cpp/libavcodec/simple_idct_template.c
        src/main/cpp/libavcodec/simple_idct.c
        src/main/cpp/libavcodec/faanidct.c
        src/main/cpp/libavcodec/jpegls.c
        src/main/cpp/libavcodec/jpeglsdec.c
        src/main/cpp/libavcodec/jpeglsenc.c
        src/main/cpp/libavcodec/exif.c

        # MPEG4
        src/main/cpp/libavcodec/mpegaudiodecheader.c
        src/main/cpp/libavcodec/mpegaudiodata.c
        src/main/cpp/libavcodec/mpeg4video_parser.c
        src/main/cpp/libavcodec/mpeg4video.c
        src/main/cpp/libavcodec/mpeg4videodec.c
        src/main/cpp/libavcodec/mpeg4videoenc.c
        src/main/cpp/libavcodec/mpegvideo_enc.c
        src/main/cpp/libavcodec/mpegvideo_motion.c
        src/main/cpp/libavcodec/mpegvideo_parser.c
        src/main/cpp/libavcodec/mpegvideo_xvmc.c
        src/main/cpp/libavcodec/mpegvideo.c
        src/main/cpp/libavcodec/mpegpicture.c
        src/main/cpp/libavcodec/mpegvideodsp.c
        src/main/cpp/libavcodec/mpegvideoencdsp.c
        src/main/cpp/libavcodec/mpegvideodata.c
        src/main/cpp/libavcodec/pixblockdsp.c
        src/main/cpp/libavcodec/ratecontrol.c
        src/main/cpp/libavcodec/mpeg12.c
        src/main/cpp/libavcodec/mpeg12data.c
        src/main/cpp/libavcodec/mpeg12dec.c
        src/main/cpp/libavcodec/mpeg12enc.c
        src/main/cpp/libavcodec/rl.c
        src/main/cpp/libavcodec/rl2.c
        src/main/cpp/libavcodec/rle.c
        src/main/cpp/libavcodec/mpegaudio.c
        src/main/cpp/libavcodec/mpegutils.c
        # src/main/cpp/libavcodec/motion_est_template.c
        src/main/cpp/libavcodec/motion_est.c
        # src/main/cpp/libavcodec/qpel_template.c
        src/main/cpp/libavcodec/qpeldsp.c

        src/main/cpp/libavcodec/me_cmp.c

        # H264
        # src/main/cpp/libavcodec/h264chroma_template.c
        src/main/cpp/libavcodec/h264chroma.c

        # TIFF
        src/main/cpp/libavcodec/tiff_common.c
        src/main/cpp/libavcodec/tiff_data.c
        src/main/cpp/libavcodec/tiff.c
        src/main/cpp/libavcodec/tiffenc.c

        # H263
        src/main/cpp/libavcodec/h263dsp.c
)

add_library (
        libswresample
        SHARED
        src/main/cpp/libswresample/swresample.c
        # src/main/cpp/libswresample/swresample_frame.c
        src/main/cpp/libswresample/audioconvert.c
        src/main/cpp/libswresample/options.c
        # src/main/cpp/libswresample/rematrix_template.c
        src/main/cpp/libswresample/rematrix.c
        src/main/cpp/libswresample/resample_dsp.c
        # src/main/cpp/libswresample/resample_template.c
        src/main/cpp/libswresample/resample.c
        # src/main/cpp/libswresample/dither_template.c
        src/main/cpp/libswresample/dither.c
        src/main/cpp/libswresample/noise_shaping_data.c
)

add_library (
        libavresample
        SHARED
        src/main/cpp/libavresample/options.c
        src/main/cpp/libavresample/audio_mix_matrix.c
        src/main/cpp/libavresample/audio_mix.c
        src/main/cpp/libavresample/audio_data.c
)

find_library (
        log-lib
        log
)

find_library (
        math-lib
        m
)

target_link_libraries (
        libavutil
        ${log-lib}
        ${math-lib}
)

target_link_libraries (
        libswresample
        libavutil
)

target_link_libraries (
        libavresample
        libswresample
        libavutil
)

target_link_libraries (
        libavcodec
        libavutil
        libswresample
        libavresample
)

target_link_libraries (
        libavformat
        libavutil
        libavcodec
        ${log-lib}
        ${math-lib}
)
