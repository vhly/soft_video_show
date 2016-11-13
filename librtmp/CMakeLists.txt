cmake_minimum_required(VERSION 3.4.1)

include_directories( "src/main/cpp/" )

add_library (
        rtmp

        SHARED

        src/main/cpp/libavutil/dict.c
        src/main/cpp/libavutil/log.c
        src/main/cpp/libavutil/avstring.c
)

find_library (
        log-lib
        log
)

target_link_libraries (
        rtmp
        ${log-lib}
)