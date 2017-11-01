
cmake_minimum_required(VERSION 3.4.1)

aux_source_directory(src/main/cpp/ SOURCE_DIR)

#动态方式加载
add_library(openssl SHARED IMPORTED )
add_library(ssl SHARED IMPORTED )
#引入第三方.so库
set_target_properties(openssl PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/cpp/libs/${ANDROID_ABI}/libcrypto.so)
set_target_properties(ssl PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/cpp/libs/${ANDROID_ABI}/libssl.so)

add_library(
             ehkingCrypt2
             SHARED
             ${SOURCE_DIR})

include_directories(src/main/cpp/include/
                    src/main/cpp/include/openssl/)

find_library(
              log-lib
              log )


target_link_libraries(
                       ehkingCrypt2
                       openssl
                       ssl
                       ${log-lib} )