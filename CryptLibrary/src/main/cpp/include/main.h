#ifndef CRYPTLIB_MAIN_H
#define CRYPTLIB_MAIN_H
#include "xlib.h"
#include <jni.h>

extern "C"
JNIEXPORT jstring JNICALL
Java_me_xbh_lib_impl_AesImpl_getRandomKey(JNIEnv *env);

extern "C"
JNIEXPORT jstring JNICALL
Java_me_xbh_lib_Md5_digest(JNIEnv *env, jclass clazz, jstring plainText);


extern "C"
JNIEXPORT jstring JNICALL
Java_me_xbh_lib_impl_AesImpl_encrypt(JNIEnv *env, jclass clazz, jstring plainText, jstring key);

extern "C"
JNIEXPORT jstring JNICALL
Java_me_xbh_lib_impl_AesImpl_decrypt(JNIEnv *env, jclass clazz, jstring cipherText, jstring key);
#endif //CRYPTLIB_MAIN_H

