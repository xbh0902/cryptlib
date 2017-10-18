#include <rsa.h>
#include "main.h"
#include "md5.h"
#include "random_tool.h"
#include "aes.h"
#include <exception>

JNIEXPORT jstring JNICALL
Java_me_xbh_lib_Md5_digest(JNIEnv *env, jclass clazz, jstring plainText) {
    return env->NewStringUTF(MD5(env->GetStringUTFChars(plainText, NULL)).toStr().c_str());
}

JNIEXPORT jstring JNICALL
Java_me_xbh_lib_impl_AesImpl_getRandomKey(JNIEnv *env) {
    return env->NewStringUTF(generateAlphaAndDigit(16).c_str());
}

JNIEXPORT jstring JNICALL
Java_me_xbh_lib_impl_AesImpl_encode(JNIEnv *env, jclass clazz, jstring plainText, jstring key) {

    AES *aes = NULL;
    aes = new AES[1];
    aes->setKey((const byte *) env->GetStringUTFChars(key, NULL));
    string result = aes->encrypt(env->GetStringUTFChars(plainText, NULL));
    delete[] aes;
    return env->NewStringUTF(result.c_str());
}

JNIEXPORT jstring JNICALL
Java_me_xbh_lib_impl_AesImpl_decode(JNIEnv *env, jclass clazz, jstring cipherText, jstring key) {

    AES *aes = NULL;
    aes = new AES[1];
    aes->setKey((const byte *) env->GetStringUTFChars(key, NULL));
    string result = aes->decrypt(env->GetStringUTFChars(cipherText, NULL));
    delete[] aes;
    return env->NewStringUTF(result.c_str());
}

JNIEXPORT jstring JNICALL
Java_me_xbh_lib_impl_RsaImpl_getPublicKey(JNIEnv *env, jclass clazz, jint build) {

    RSAEncrypt *rsa = NULL;
    rsa = new RSAEncrypt[1];
    string result = rsa->getPublicKey(build);
    delete[] rsa;
    return env->NewStringUTF(result.c_str());
}

JNIEXPORT jstring JNICALL
Java_me_xbh_lib_impl_RsaImpl_encryptByPublicKey(JNIEnv *env, jclass clazz, jstring plain,
                                                jstring key) {
    RSAEncrypt *rsa = NULL;
    rsa = new RSAEncrypt[1];
    string pubkey = env->GetStringUTFChars(key, NULL);
    string plainText = env->GetStringUTFChars(plain, NULL);

    string result = rsa->encrypt(plainText, pubkey);
    if (result.c_str() == NULL) {
        result = "NULL";
    }
    delete[] rsa;
    return env->NewStringUTF(result.c_str());
}

JNIEXPORT jstring JNICALL
Java_me_xbh_lib_impl_RsaImpl_decryptByPublicKey(JNIEnv *env, jclass clazz, jstring cipher,

                                                jstring key) {
    RSAEncrypt *rsa = NULL;
    rsa = new RSAEncrypt[1];
    string pubkey = env->GetStringUTFChars(key, NULL);
    string cipherText = env->GetStringUTFChars(cipher, NULL);
    string result = rsa->decrypt(cipherText, pubkey);
    if (result.c_str() == NULL) {
        result = "NULL";
    }
    delete[] rsa;

    return env->NewStringUTF(result.c_str());
}