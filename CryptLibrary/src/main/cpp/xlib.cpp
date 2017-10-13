//
// Tools
//
#include "xlib.h"

char *jstring2char(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    //1:先找到字节码文件
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF(UTF_8);
    //2:通过字节码文件找到方法ID
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    //3:通过方法id，调用方法
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    //4:得到数据的长度
    jsize alen = env->GetArrayLength(barr);
    //5：得到数据的首地址
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    //6:得到C语言的字符串
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);//"\0"
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);  //
    return rtn;
}


jstring char2jstring(JNIEnv *env, jbyteArray byteArray) {
    jclass string_cls = env->FindClass("java/lang/String");
    jmethodID new_string_mid = env->GetMethodID(string_cls, "<init>", "([BLjava/lang/String;)V");
    return reinterpret_cast<jstring>(env->NewObject(string_cls, new_string_mid, byteArray,
                                                    env->NewStringUTF(UTF_8)));
}

jbyteArray char2jbyteArray(JNIEnv *env, const char *bytes) {
    jclass string_cls = env->FindClass("java/lang/String");
    jmethodID get_bytes_mid = env->GetMethodID(string_cls, "getBytes", "(Ljava/lang/String;)[B");
    return reinterpret_cast<jbyteArray>(env->CallObjectMethod(env->NewStringUTF(bytes),
                                                              get_bytes_mid,
                                                              env->NewStringUTF(UTF_8)));
}