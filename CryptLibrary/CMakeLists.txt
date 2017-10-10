
cmake_minimum_required(VERSION 3.4.1)

aux_source_directory(src/main/cpp/ SOURCE_DIR)

add_library(
             crypt
             SHARED
             ${SOURCE_DIR})

include_directories(src/main/cpp/include/)

find_library(
              log-lib
              log )


target_link_libraries(
                       crypt
                       ${log-lib} )