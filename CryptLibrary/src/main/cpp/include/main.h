#ifndef CRYPTLIB_MAIN_H
#define CRYPTLIB_MAIN_H

#include "xlib.h"
#include <jni.h>

extern "C" {

    /**
     * MD5加密
     */
    JNIEXPORT jstring JNICALL
    Java_me_xbh_lib_core_cxx_Md5_digest(JNIEnv *env, jobject thiz, jstring plainText);

    /**
     * 获取AES随机密钥
     */
    JNIEXPORT jstring JNICALL
    Java_me_xbh_lib_core_cxx_AesImpl_getRandomKey(JNIEnv *env);

    /**
     * 获取本地密钥
     */
    JNIEXPORT jstring JNICALL
    Java_me_xbh_lib_core_cxx_AesImpl_getLocalKey(JNIEnv *env, jobject thiz, jobject context);

    /**
     * AES ECB加密
     */
    JNIEXPORT jstring JNICALL
    Java_me_xbh_lib_core_cxx_AesImpl_encode(JNIEnv *env, jobject thiz, jstring plainText, jstring key);

    /**
     * AES ECB解密
     */
    JNIEXPORT jstring JNICALL
    Java_me_xbh_lib_core_cxx_AesImpl_decode(JNIEnv *env, jobject thiz, jstring cipherText, jstring key);

    /**
     * 获取RSA公钥
     */
    JNIEXPORT jstring JNICALL
    Java_me_xbh_lib_core_cxx_RsaImpl_getPublicKey(JNIEnv *env, jobject thiz, jint build);

    /**
     * RSA公钥加密
     */
    JNIEXPORT jstring JNICALL
    Java_me_xbh_lib_core_cxx_RsaImpl_encryptByPublicKey(JNIEnv *env, jobject thiz, jstring plain, jstring key);

    /**
     * RSA公钥解密
     */
    JNIEXPORT jstring JNICALL
    Java_me_xbh_lib_core_cxx_RsaImpl_decryptByPublicKey(JNIEnv *env, jobject thiz, jstring cipher, jstring key);

}
#endif //CRYPTLIB_MAIN_H
