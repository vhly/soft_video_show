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
        src/main/cpp/libavutil/timecode.c

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

