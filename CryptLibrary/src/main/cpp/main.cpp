//
// Created by lulu on 17-9-27.
//

#include <aes.h>
#include "main.h"
#include "md5.h"


JNIEXPORT jstring JNICALL
Java_me_xbh_lib_impl_AesImpl_getRandomKey(JNIEnv *env) {

    unsigned char* key = NULL;
    unsigned char* input = NULL;
    unsigned char* output = NULL;
//
//    AESModeOfOperation moo;
//
//    moo.set_mode(MODE_ECB);
//    moo.Encrypt(input, sizeof(input), output);
    return env->NewStringUTF(MD5("nihao").toStr().c_str());
}


JNIEXPORT jstring JNICALL
Java_me_xbh_lib_Md5_digest(JNIEnv *env, jclass clazz, jstring plainText) {
    return env->NewStringUTF(MD5(env->GetStringUTFChars(plainText, NULL)).toStr().c_str());
}