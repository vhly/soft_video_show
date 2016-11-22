cmake_minimum_required(VERSION 3.4.1)

include_directories( "src/main/cpp/" )

# System architecture detection

message(STATUS "Detected ${CMAKE_SYSTEM_PROCESSOR}")

string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" SYSPROC)
set(X86_ALIASES x86 i386 i686 x86_64 amd64)
set(ARM64_ALIASES aarch64 arm64-v8a arm64v8-a)
set(ARM_ALIASES armv5te armv6l armv7l armv7-a arch-arm aarch64 arm64-v8a arm64v8-a)
set(ARMV7A_ALIASES armv7-a)
set(MIPS_ALIASES mips mips64)

list(FIND X86_ALIASES "${SYSPROC}" X86MATCH)
list(FIND ARM_ALIASES "${SYSPROC}" ARMMATCH)
list(FIND ARMV7A_ALIASES "${SYSPROC}" ARMV7A_MATCH)
list(FIND ARM64_ALIASES "${SYSPROC}" ARM64MATCH)
list(FIND MIPS_ALIASES "${SYSPROC}" MIPSMATCH)

set(AARCH64_SRC
    src/main/cpp/libavutil/aarch64/asm.S
    src/main/cpp/libavutil/aarch64/float_dsp_neon.S
    src/main/cpp/libavutil/aarch64/cpu.c
    src/main/cpp/libavutil/aarch64/float_dsp_init.c
)

set(ARMV7A_SRC
    src/main/cpp/libavutil/arm/asm.S
    src/main/cpp/libavutil/arm/float_dsp_vfp.S
    src/main/cpp/libavutil/arm/float_dsp_neon.S
    src/main/cpp/libavutil/arm/cpu.c
    src/main/cpp/libavutil/arm/float_dsp_init_arm.c
    src/main/cpp/libavutil/arm/float_dsp_init_neon.c
    src/main/cpp/libavutil/arm/float_dsp_init_vfp.c
)

set(ARM_SRC
    src/main/cpp/libavutil/arm/asm.S
    src/main/cpp/libavutil/arm/float_dsp_neon.S
    src/main/cpp/libavutil/arm/cpu.c
    src/main/cpp/libavutil/arm/float_dsp_init_arm.c
)

set(MIPS_SRC
    src/main/cpp/libavutil/mips/float_dsp_mips.c
)

set(X86_SRC
    src/main/cpp/libavutil/x86/float_dsp_init.c
    src/main/cpp/libavutil/x86/float_dsp.asm
    src/main/cpp/libavutil/x86/cpu.c
    src/main/cpp/libavutil/x86/cpuid.asm
    src/main/cpp/libavutil/x86/emms.asm
    src/main/cpp/libavutil/x86/fixed_dsp.asm
    src/main/cpp/libavutil/x86/fixed_dsp_init.c
    src/main/cpp/libavutil/x86/lls_init.c
    src/main/cpp/libavutil/x86/lls.asm
    src/main/cpp/libavutil/x86/pixelutils.asm
    src/main/cpp/libavutil/x86/pixelutils_init.c
    src/main/cpp/libavutil/x86/x86inc.asm
    src/main/cpp/libavutil/x86/x86util.asm
)

if("${SYSPROC}" STREQUAL "" OR X86MATCH GREATER "-1")
    add_definitions(-DARCH_X86=1)
    if("${CMAKE_SIZEOF_VOID_P}" MATCHES 8)
        set(X86_64 1)
        add_definitions(-DARCH_X86_64=1)
        add_definitions(-DARCH_X86_32=0)
        add_definitions(-DARCH_AARCH64=0)
        add_definitions(-DARCH_ARM=0)
        add_definitions(-DARCH_MIPS64=0)
        add_definitions(-DARCH_MIPS=0)
        add_definitions(-DHAVE_ARMV8=0)
        message(STATUS "Detected x86_64 target processor")
    else()
        set(X86 1)
        add_definitions(-DARCH_X86_32=1)
        add_definitions(-DARCH_X86_64=0)
        add_definitions(-DARCH_AARCH64=0)
        add_definitions(-DARCH_ARM=0)
        add_definitions(-DARCH_MIPS64=0)
        add_definitions(-DARCH_MIPS=0)
        add_definitions(-DHAVE_ARMV8=0)
        message(STATUS "Detected x86 target processor")
    endif()
    set(ARCH_SRC_FILES ${X86_SRC})
elseif(ARMMATCH GREATER "-1")

    add_definitions(-DARCH_X86_64=0)
    add_definitions(-DARCH_X86_32=0)
    add_definitions(-DARCH_X86=0)
    add_definitions(-DARCH_MIPS64=0)
    add_definitions(-DARCH_MIPS=0)

    if("${CMAKE_SIZEOF_VOID_P}" MATCHES 8)
        set(ARM64 1)
        add_definitions(-DARCH_AARCH64=1)
        add_definitions(-DHAVE_NEON=0)
        add_definitions(-DHAVE_VFP=1)
        add_definitions(-DHAVE_VFPV3=1)
        add_definitions(-DHAVE_ARMV8=1)
        add_definitions(-DARCH_ARM=0)
        set(ARCH_SRC_FILES ${AARCH64_SRC})
        message(STATUS "Detected arm64 target processor")
    else()
        set(ARM 1)
        add_definitions(-DHAVE_ARMV8=0)
        add_definitions(-DARCH_AARCH64=0)


        if(ARMV7A_MATCH GREATER "-1")
            add_definitions(-DHAVE_NEON=0)
            add_definitions(-DHAVE_VFP=0)
            add_definitions(-DHAVE_VFPV3=0)
            add_definitions(-DARCH_ARM=1)
            set(ARCH_SRC_FILES ${ARM_SRC})
            message(STATUS "Detected armv7a target processor")
        else()
            add_definitions(-DHAVE_NEON=0)
            add_definitions(-DHAVE_VFP=0)
            add_definitions(-DHAVE_VFPV3=0)
            # In old armeabi , disable asm
            add_definitions(-DARCH_ARM=0)
            add_definitions(-mthumb)
            # set(ARCH_SRC_FILES ${ARM_SRC})
            message(STATUS "Detected armveabi target processor")
        endif()
    endif()

elseif(MIPSMATCH GREATER "-1")
    if("${CMAKE_SIZEOF_VOID_P}" MATCHES 8)
        set(MIPS64 1)
        add_definitions(-DARCH_MIPS64=1)
        add_definitions(-DARCH_X86_64=0)
        add_definitions(-DARCH_X86_32=0)
        add_definitions(-DARCH_X86=0)
        add_definitions(-DARCH_ARM=0)
        add_definitions(-DARCH_AARCH64=0)
        add_definitions(-DARCH_MIPS=0)
        message(STATUS "Detected mips64 target processor")
    else()
        set(MIPS 1)
        add_definitions(-DARCH_MIPS=1)
        add_definitions(-DARCH_X86_64=0)
        add_definitions(-DARCH_X86_32=0)
        add_definitions(-DARCH_X86=0)
        add_definitions(-DARCH_ARM=0)
        add_definitions(-DARCH_AARCH64=0)
        add_definitions(-DARCH_MIPS64=0)
        set(ARCH_SRC_FILES ${MIPS_SRC})
        message(STATUS "Detected mips target processor")
    endif()
endif()

add_library (
        avutil

        SHARED

        ${ARCH_SRC_FILES}

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
        src/main/cpp/libavutil/pixelutils.c
        src/main/cpp/libavutil/lls.c

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

        # for file
        src/main/cpp/libavutil/file_open.c
        src/main/cpp/libavutil/file.c

        # for test
        src/androidTest/cpp/libavutil/md5test.c
)

find_library (
        log-lib
        log
)

find_library (
        math-lib
        m
)

message(STATUS "ARCH_NAME is ${ARCH_NAME}")

target_link_libraries (
        avutil
        ${log-lib}
        ${math-lib}
)

