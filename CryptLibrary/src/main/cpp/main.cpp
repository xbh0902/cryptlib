//
// Created by lulu on 17-10-12.
//

#include "rsa.h"
#include "main.h"
#include "md5.h"
#include "keytools.h"
#include "aes.h"

JNIEXPORT jstring JNICALL
Java_me_xbh_lib_core_cxx_Md5_digest(JNIEnv *env, jobject thiz, jstring plainText) {
    return env->NewStringUTF(MD5(env->GetStringUTFChars(plainText, NULL)).toStr().c_str());
}

JNIEXPORT jstring JNICALL
Java_me_xbh_lib_core_cxx_AesImpl_getRandomKey(JNIEnv *env) {
    return env->NewStringUTF(generateAlphaAndDigit(16).c_str());
}

JNIEXPORT jstring JNICALL
Java_me_xbh_lib_core_cxx_AesImpl_getLocalKey(JNIEnv *env, jobject thiz, jobject context){
    return env->NewStringUTF(getLocalKey(env, thiz, context).c_str());
}

JNIEXPORT jstring JNICALL
Java_me_xbh_lib_core_cxx_AesImpl_encode(JNIEnv *env, jobject thiz, jstring plainText, jstring key) {

    AES *aes = new AES;
    aes->setKey((const byte *) env->GetStringUTFChars(key, NULL));
    string result = aes->encrypt(env->GetStringUTFChars(plainText, NULL));
    delete aes;
    return env->NewStringUTF(result.c_str());
}

JNIEXPORT jstring JNICALL
Java_me_xbh_lib_core_cxx_AesImpl_decode(JNIEnv *env, jobject thiz, jstring cipherText, jstring key) {

    AES *aes = new AES;
    aes->setKey((const byte *) env->GetStringUTFChars(key, NULL));
    string result = aes->decrypt(env->GetStringUTFChars(cipherText, NULL));
    delete aes;
    return env->NewStringUTF(result.c_str());
}

JNIEXPORT jstring JNICALL
Java_me_xbh_lib_core_cxx_RsaImpl_getPublicKey(JNIEnv *env, jobject thiz, jint build) {

    RSAEncrypt *rsa = new RSAEncrypt;
    string result = rsa->getPublicKey(build);
    delete rsa;
    return env->NewStringUTF(result.c_str());
}

JNIEXPORT jstring JNICALL
Java_me_xbh_lib_core_cxx_RsaImpl_encryptByPublicKey(JNIEnv *env, jobject thiz, jstring plain,
                                                jstring key) {
    RSAEncrypt *rsa = new RSAEncrypt;
    string pubkey = env->GetStringUTFChars(key, NULL);
    string plainText = env->GetStringUTFChars(plain, NULL);

    string result = rsa->encrypt(plainText, pubkey);
    if (result.c_str() == NULL) {
        result = "NULL";
    }
    delete rsa;
    return env->NewStringUTF(result.c_str());
}

JNIEXPORT jstring JNICALL
Java_me_xbh_lib_core_cxx_RsaImpl_decryptByPublicKey(JNIEnv *env, jobject thiz, jstring cipher,
                                                jstring key) {
    RSAEncrypt *rsa = new RSAEncrypt;
    string pubkey = env->GetStringUTFChars(key, NULL);
    string cipherText = env->GetStringUTFChars(cipher, NULL);
    string result = rsa->decrypt(cipherText, pubkey);
    if (result.c_str() == NULL) {
        result = "NULL";
    }
    delete[] rsa;
    return env->NewStringUTF(result.c_str());
}