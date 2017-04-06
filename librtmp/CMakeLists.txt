cmake_minimum_required(VERSION 3.4.1)

add_definitions(-DVERSION=v2.4)
#add_definitions(-DCRYPTO=OPENSSL)
#add_definitions(-DUSE_OPENSSL)
add_definitions(-DNO_CRYPTO)
add_definitions(-DRTMPDUMP_VERSION="v2.4 NO_CRYPTO")

add_library(
     rtmp
     SHARED
     src/main/cpp/rtmpdump/librtmp/amf.c
     src/main/cpp/rtmpdump/librtmp/hashswf.c
     src/main/cpp/rtmpdump/librtmp/log.c
     src/main/cpp/rtmpdump/librtmp/parseurl.c
     src/main/cpp/rtmpdump/librtmp/rtmp.c
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
