cmake_minimum_required(VERSION 3.4.1)

include_directories( "src/main/cpp/x264/" )

add_library( 
     x264
     SHARED
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

     src/main/cpp/x264/encoder/slicetype.c

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

find_library( 
      log-lib
      log )

find_library( 
      math-lib
      m )

target_link_libraries(
           x264
           ${log-lib}
           ${math-lib}
           )
