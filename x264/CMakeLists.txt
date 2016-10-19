# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds it for you.
# Gradle automatically packages shared libraries with your APK.

include_directories( "src/main/cpp/x264/" )


# System architecture detection
# string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" SYSPROC)
# set(X86_ALIASES x86 i386 i686 x86_64 amd64)
# set(ARM_ALIASES armv5te armv6l armv7l armv7-a aarch64)
# list(FIND X86_ALIASES "${SYSPROC}" X86MATCH)
# list(FIND ARM_ALIASES "${SYSPROC}" ARMMATCH)
# set(MIPS_ALIASES mips mips64)
# list(FIND MIPS_ALIASES "${SYSPROC}" MIPSMATCH)

# if("${SYSPROC}" STREQUAL "" OR X86MATCH GREATER "-1")
#     if("${CMAKE_SIZEOF_VOID_P}" MATCHES 8)
#         set(X64 1)
#         add_definitions(-DARCH_X86_64=1)
#         add_definitions(-DHAVE_NEON=1)
#         message(STATUS "Detected x86_64 target processor")
#     else()
#         set(X86 1)
#         add_definitions(-DARCH_X86=1)
#     message(STATUS "Detected x86 target processor")
#     endif()
# elseif(ARMMATCH GREATER "-1")
#     message(STATUS "Detected ARM target processor")
#
#     if("${CMAKE_SIZEOF_VOID_P}" MATCHES 8)
#     set(ARM_X64 1)
#     add_definitions(-DARCH_AARCH64=1)
#     add_definitions(-DHAVE_NEON=1)
#     message(STATUS "Detected arm64 target processor")
#     else()
#     set(ARM 1)
#     add_definitions(-DARCH_ARM=1)
#     add_definitions(-DHAVE_ARMV6=1)
#     message(STATUS "Detected arm target processor")
#     endif()
#elseif(MIPSMATCH GREATER "-1")
#    message(STATUS "Detected mips target processor")
#
#    if("${CMAKE_SIZEOF_VOID_P}" MATCHES 8)
#    set(MIPS_X64 1)
#    add_definitions(-DARCH_MIPS64=1)
#    message(STATUS "Detected mips64 target processor")
#    else()
#    set(MIPS 1)
#    add_definitions(-DARCH_MIPS=1)
#    message(STATUS "Detected mips target processor")
#    endif()
# else()
#     message(STATUS "CMAKE_SYSTEM_PROCESSOR value `${CMAKE_SYSTEM_PROCESSOR}` is unknown")
#     message(STATUS "Please add this value near ${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}")
# endif()

set(ARM_ASM
    src/main/cpp/x264/common/arm/asm.S
    src/main/cpp/x264/common/arm/bitstream-a.S
    src/main/cpp/x264/common/arm/cpu-a.S
    src/main/cpp/x264/common/arm/dct-a.S
    src/main/cpp/x264/common/arm/deblock-a.S
    src/main/cpp/x264/common/arm/mc-a.S
    src/main/cpp/x264/common/arm/mc-c.c
    src/main/cpp/x264/common/arm/pixel-a.S
    src/main/cpp/x264/common/arm/predict-a.S
    src/main/cpp/x264/common/arm/predict-a.S
    src/main/cpp/x264/common/arm/predict-c.c
    src/main/cpp/x264/common/arm/quant-a.S
)


set(ARM_64_ASM
    src/main/cpp/x264/common/aarch64/asm.S
    src/main/cpp/x264/common/aarch64/asm-offsets.c
    src/main/cpp/x264/common/aarch64/bitstream-a.S
    src/main/cpp/x264/common/aarch64/cabac-a.S
    src/main/cpp/x264/common/aarch64/dct-a.S
    src/main/cpp/x264/common/aarch64/deblock-a.S
    src/main/cpp/x264/common/aarch64/mc-a.S
    src/main/cpp/x264/common/aarch64/mc-c.c
    src/main/cpp/x264/common/aarch64/pixel-a.S
    src/main/cpp/x264/common/aarch64/predict-a.S
    src/main/cpp/x264/common/aarch64/predict-a.S
    src/main/cpp/x264/common/aarch64/predict-c.c
    src/main/cpp/x264/common/aarch64/quant-a.S
)

set(X86_ASM
    src/main/cpp/x264/common/x86/bitstream-a.asm
    src/main/cpp/x264/common/x86/cabac-a.asm
    src/main/cpp/x264/common/x86/const-a.asm
    src/main/cpp/x264/common/x86/cpu-a.asm
    src/main/cpp/x264/common/x86/dct-32.asm
    src/main/cpp/x264/common/x86/dct-a.asm
    src/main/cpp/x264/common/x86/deblock-a.asm
    src/main/cpp/x264/common/x86/mc-a2.asm
    src/main/cpp/x264/common/x86/mc-a.asm
    src/main/cpp/x264/common/x86/mc-c.c
    src/main/cpp/x264/common/x86/pixel-32.asm
    src/main/cpp/x264/common/x86/pixel-a.asm
    src/main/cpp/x264/common/x86/predict-a.asm
    src/main/cpp/x264/common/x86/predict-c.c
    src/main/cpp/x264/common/x86/quant-a.asm
    src/main/cpp/x264/common/x86/sad16-a.asm
    src/main/cpp/x264/common/x86/sad-a.asm
    src/main/cpp/x264/common/x86/x86inc.asm
    src/main/cpp/x264/common/x86/x86util.asm
)
set(X86_64_ASM
    src/main/cpp/x264/common/x86/bitstream-a.asm
    src/main/cpp/x264/common/x86/cabac-a.asm
    src/main/cpp/x264/common/x86/const-a.asm
    src/main/cpp/x264/common/x86/cpu-a.asm
    src/main/cpp/x264/common/x86/dct-64.asm
    src/main/cpp/x264/common/x86/dct-a.asm
    src/main/cpp/x264/common/x86/deblock-a.asm
    src/main/cpp/x264/common/x86/mc-a2.asm
    src/main/cpp/x264/common/x86/mc-a.asm
    src/main/cpp/x264/common/x86/mc-c.c
    src/main/cpp/x264/common/x86/pixel-a.asm
    src/main/cpp/x264/common/x86/predict-a.asm
    src/main/cpp/x264/common/x86/predict-c.c
    src/main/cpp/x264/common/x86/quant-a.asm
    src/main/cpp/x264/common/x86/sad16-a.asm
    src/main/cpp/x264/common/x86/sad-a.asm
    src/main/cpp/x264/common/x86/trellis-64.asm
    src/main/cpp/x264/common/x86/x86inc.asm
    src/main/cpp/x264/common/x86/x86util.asm
)
set(MIPS_ASM
    src/main/cpp/x264/common/mips/dct-c.c
    src/main/cpp/x264/common/mips/deblock-c.c
    src/main/cpp/x264/common/mips/mc-c.c
    src/main/cpp/x264/common/mips/pixel-c.c
    src/main/cpp/x264/common/mips/predict-c.c
    src/main/cpp/x264/common/mips/quant-c.c
)
set(MIPS_64_ASM ${MIPS_ASM})

if(X86)
    set(ADDITIONAL_SRC ${X86_ASM})
elseif(X64)
    set(ADDITIONAL_SRC ${X86_64_ASM})
# elseif(MIPS)
#    set(ADDITIONAL_SRC ${MIPS_ASM})
# elseif(MIPS_64)
#    set(ADDITIONAL_SRC ${MIPS_64_ASM})
elseif(ARM)
    set(ADDITIONAL_SRC ${ARM_ASM})
elseif(ARM_X64)
    set(ADDITIONAL_SRC ${ARM_64_ASM})
endif()



add_library( # Sets the name of the library.
     x264

     # Sets the library as a shared library.
     SHARED

     # ${ADDITIONAL_SRC}

     # Provides a relative path to your source file(s).
     # Associated headers in the same location as their source
     # file are automatically included.
     src/main/cpp/mobi_vhly_demo01_MainActivity.c
     src/main/cpp/mobi_vhly_demo01_X264Encoder.c
     src/main/cpp/x264/common/bitstream.c
     src/main/cpp/x264/common/cabac.c
     src/main/cpp/x264/common/common.c
     src/main/cpp/x264/common/cpu.c
     src/main/cpp/x264/common/dct.c
     src/main/cpp/x264/common/deblock.c
     src/main/cpp/x264/common/frame.c
     src/main/cpp/x264/common/macroblock.c
     src/main/cpp/x264/common/mc.c
     src/main/cpp/x264/common/mvpred.c
     src/main/cpp/x264/common/osdep.c
     src/main/cpp/x264/common/pixel.c
     src/main/cpp/x264/common/predict.c
     src/main/cpp/x264/common/quant.c
     src/main/cpp/x264/common/rectangle.c
     src/main/cpp/x264/common/set.c
     src/main/cpp/x264/common/vlc.c

     src/main/cpp/x264/encoder/analyse.c
     src/main/cpp/x264/encoder/cabac.c
     src/main/cpp/x264/encoder/cavlc.c
     src/main/cpp/x264/encoder/encoder.c
     src/main/cpp/x264/encoder/lookahead.c
     src/main/cpp/x264/encoder/macroblock.c
     src/main/cpp/x264/encoder/me.c
     src/main/cpp/x264/encoder/ratecontrol.c
     src/main/cpp/x264/encoder/set.c

     # src/main/cpp/x264/encoder/rdo.c
     # src/main/cpp/x264/encoder/slicetype.c
     # src/main/cpp/x264/encoder/slicetype-cl.c

     src/main/cpp/x264/x264.c

     src/main/cpp/x264/input/input.c
     src/main/cpp/x264/input/raw.c
     src/main/cpp/x264/input/y4m.c
     src/main/cpp/x264/input/timecode.c

     src/main/cpp/x264/filters/filters.c
     src/main/cpp/x264/filters/video/video.c
     src/main/cpp/x264/filters/video/internal.c
     src/main/cpp/x264/filters/video/depth.c
     src/main/cpp/x264/filters/video/select_every.c
     src/main/cpp/x264/filters/video/resize.c
     src/main/cpp/x264/filters/video/fix_vfr_pts.c
     src/main/cpp/x264/filters/video/crop.c
     src/main/cpp/x264/filters/video/cache.c
     src/main/cpp/x264/filters/video/source.c

     src/main/cpp/x264/output/raw.c
     src/main/cpp/x264/output/flv.c
     src/main/cpp/x264/output/flv_bytestream.c
     src/main/cpp/x264/output/matroska.c
     src/main/cpp/x264/output/matroska_ebml.c

     )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because system libraries are included in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
      log-lib

      # Specifies the name of the NDK library that
      # you want CMake to locate.
      log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in the
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
           x264

           # Links the target library to the log library
           # included in the NDK.
           ${log-lib} )
