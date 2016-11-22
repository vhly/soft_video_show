# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds it for you.
# Gradle automatically packages shared libraries with your APK.

include_directories( "src/main/cpp/x264/" )

add_library( # Sets the name of the library.
     x264

     # Sets the library as a shared library.
     SHARED

     # Provides a relative path to your source file(s).
     # Associated headers in the same location as their source
     # file are automatically included.
     src/main/cpp/mobi_vhly_demo01_MainActivity.c
     src/main/cpp/mobi_vhly_x264_X264Encoder.c
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


     src/main/cpp/x264/encoder/ratecontrol.c
     src/main/cpp/x264/encoder/analyse.c
     src/main/cpp/x264/encoder/cabac.c
     src/main/cpp/x264/encoder/cavlc.c
     src/main/cpp/x264/encoder/encoder.c
     src/main/cpp/x264/encoder/lookahead.c
     src/main/cpp/x264/encoder/macroblock.c
     src/main/cpp/x264/encoder/me.c
     src/main/cpp/x264/encoder/set.c

     # src/main/cpp/x264/encoder/rdo.c
     src/main/cpp/x264/encoder/slicetype.c
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

find_library( # Sets the name of the path variable.
      math-lib

      # Specifies the name of the NDK library that
      # you want CMake to locate.
      m )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in the
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
           x264

           # Links the target library to the log library
           # included in the NDK.
           ${log-lib}
           ${math-lib}
           )
