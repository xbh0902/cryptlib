#include <aes_helper.h>
#include "main.h"
#include "md5.h"
#include "random_tool.h"


JNIEXPORT jstring JNICALL
Java_me_xbh_lib_impl_AesImpl_getRandomKey(JNIEnv *env) {
    return env->NewStringUTF(generateAlphaAndDigit(KEYCODELENGTH).c_str());
}

JNIEXPORT jstring JNICALL
Java_me_xbh_lib_Md5_digest(JNIEnv *env, jclass clazz, jstring plainText) {
    return env->NewStringUTF(MD5(env->GetStringUTFChars(plainText, NULL)).toStr().c_str());
}

JNIEXPORT jstring JNICALL
Java_me_xbh_lib_impl_AesImpl_encrypt(JNIEnv *env, jclass clazz, jstring plainText, jstring key){
    CAesHelper helper;
    string result = helper.Encrypt(env->GetStringUTFChars(plainText, NULL), env->GetStringUTFChars(key, NULL));
    return env->NewStringUTF(result.c_str());
}

JNIEXPORT jstring JNICALL
Java_me_xbh_lib_impl_AesImpl_decrypt(JNIEnv *env, jclass clazz, jstring cipherText, jstring key){
    CAesHelper helper;
    string result = helper.Decrypt(env->GetStringUTFChars(cipherText, NULL), env->GetStringUTFChars(key, NULL));
    return env->NewStringUTF(result.c_str());
}