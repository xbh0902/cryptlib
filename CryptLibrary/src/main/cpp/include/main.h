#ifndef CRYPTLIB_MAIN_H
#define CRYPTLIB_MAIN_H

#include "xlib.h"
#include <jni.h>

extern "C" {

    /**
     * MD5加密
     */
    JNIEXPORT jstring JNICALL
    Java_me_xbh_lib_Md5_digest(JNIEnv *env, jclass clazz, jstring plainText);

    /**
     * 获取AES随机密钥
     */
    JNIEXPORT jstring JNICALL
    Java_me_xbh_lib_impl_AesImpl_getRandomKey(JNIEnv *env);

    /**
     * AES加密
     */
    JNIEXPORT jstring JNICALL
    Java_me_xbh_lib_impl_AesImpl_encode(JNIEnv *env, jclass clazz, jstring plainText, jstring key);

    /**
     * AES解密
     */
    JNIEXPORT jstring JNICALL
    Java_me_xbh_lib_impl_AesImpl_decode(JNIEnv *env, jclass clazz, jstring cipherText, jstring key);

    /**
     * 获取RSA公钥
     */
    JNIEXPORT jstring JNICALL
    Java_me_xbh_lib_impl_RsaImpl_getPublicKey(JNIEnv *env, jclass clazz, jint build);

    /**
     * RSA公钥加密
     */
    JNIEXPORT jstring JNICALL
    Java_me_xbh_lib_impl_RsaImpl_encryptByPublicKey(JNIEnv *env, jclass clazz, jstring plain, jstring key);

    /**
     * RSA公钥解密
     */
    JNIEXPORT jstring JNICALL
    Java_me_xbh_lib_impl_RsaImpl_decryptByPublicKey(JNIEnv *env, jobject thiz, jstring cipher, jstring key);

}
#endif //CRYPTLIB_MAIN_H
