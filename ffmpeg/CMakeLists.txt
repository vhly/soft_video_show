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
