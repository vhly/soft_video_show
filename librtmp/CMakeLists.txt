cmake_minimum_required(VERSION 3.4.1)


add_library(
     rtmp
     SHARED
     src/main/cpp/rtmp/
     )

find_library(
      log-lib
      log )

find_library(
      math-lib
      m )

target_link_libraries(
           rtmp
           ${log-lib}
           ${math-lib}
           )
