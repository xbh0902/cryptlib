#include "main.h"
#include "md5.h"
#include "random_tool.h"
#include "aes.h"
using namespace crypt;

JNIEXPORT jstring JNICALL
Java_me_xbh_lib_impl_AesImpl_getRandomKey(JNIEnv *env) {
    return env->NewStringUTF(generateAlphaAndDigit(16).c_str());
}

JNIEXPORT jstring JNICALL
Java_me_xbh_lib_Md5_digest(JNIEnv *env, jclass clazz, jstring plainText) {
    return env->NewStringUTF(MD5(env->GetStringUTFChars(plainText, NULL)).toStr().c_str());
}

JNIEXPORT jstring JNICALL
Java_me_xbh_lib_impl_AesImpl_encrypt(JNIEnv *env, jclass clazz, jstring plainText, jstring key){

    AES aes((const byte *) env->GetStringUTFChars(key, NULL));
    string result = aes.encrypt(env->GetStringUTFChars(plainText, NULL));
    return env->NewStringUTF(result.c_str());
}

JNIEXPORT jstring JNICALL
Java_me_xbh_lib_impl_AesImpl_decrypt(JNIEnv *env, jclass clazz, jstring cipherText, jstring key){

    AES aes((const byte *) env->GetStringUTFChars(key, NULL));
    string result = aes.decrypt(env->GetStringUTFChars(cipherText, NULL));
    return env->NewStringUTF(result.c_str());
}
