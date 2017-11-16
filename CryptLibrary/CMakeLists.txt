
cmake_minimum_required(VERSION 3.4.1)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/main/cpp/ SOURCE_DIR)

add_library(crypto SHARED IMPORTED )
add_library(openssl SHARED IMPORTED )

set_target_properties(crypto PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/cpp/libs/${ANDROID_ABI}/libcrypto.so)
set_target_properties(openssl PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/cpp/libs/${ANDROID_ABI}/libssl.so)

add_library(
             crypt1
             SHARED
             ${SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/src/main/cpp/include/
                    ${CMAKE_SOURCE_DIR}/src/main/cpp/include/openssl/)

find_library(
              log-lib
              log )


target_link_libraries(
                       crypt1
                       crypto
                       openssl
                       ${log-lib} )