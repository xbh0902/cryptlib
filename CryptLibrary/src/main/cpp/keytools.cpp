//
// Created by lulu on 17-10-12.
//

#include "keytools.h"

string generateAlphaAndDigit(int lenght) {

    string result = "";
    if (lenght < 1) {
        return result;
    }
    int data = 0;
    for (int i = 0; i < lenght; ++i) {
        int index = rand() % 3;
        char *tmp = NULL;
        tmp = new char[20];
        switch (index) {

            case 0:
                data = rand() % 10;
                sprintf(tmp, "%d", data);
                result += tmp;
                break;
            case 1:
                data = rand() % 26 + 65;
                result += data;
                break;
            case 2:
                data = rand() % 26 + 97;
                result += data;
                break;
            default:
                break;
        }
        delete[] tmp;
    }
    return result;
}

//获取SerialNumber
jstring getSerialNumber(JNIEnv *env, jobject thiz, jobject mContext) {
    jclass cls_tm = (env)->FindClass("android/os/SystemProperties");
    if (cls_tm == 0) {
        return (env)->NewStringUTF("unknown");
    }
    jmethodID getDeviceId = (env)->GetStaticMethodID(cls_tm, "get",
                                                     "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");
    if (getDeviceId == 0) {
        return (env)->NewStringUTF("unknown");
    }
    jstring param1 = (env)->NewStringUTF("ro.serialno");
    jstring param2 = (env)->NewStringUTF("unknown");
    jobject deviceid = (env)->CallStaticObjectMethod(cls_tm, getDeviceId, param1, param2);
    return (jstring) deviceid;
}

//获取deviceid
jstring getDeviceID(JNIEnv *env, jobject thiz, jobject mContext) {
    jclass cls_context = (env)->FindClass("android/content/Context");
    if (cls_context == 0) {
        return (env)->NewStringUTF("unknown");
    }
    jmethodID getSystemService = (env)->GetMethodID(cls_context, "getSystemService",
                                                    "(Ljava/lang/String;)Ljava/lang/Object;");
    if (getSystemService == 0) {
        return (env)->NewStringUTF("unknown");
    }
    jfieldID TELEPHONY_SERVICE = (env)->GetStaticFieldID(cls_context, "TELEPHONY_SERVICE",
                                                         "Ljava/lang/String;");
    if (TELEPHONY_SERVICE == 0) {
        return (env)->NewStringUTF("unknown");
    }
    jobject str = (env)->GetStaticObjectField(cls_context, TELEPHONY_SERVICE);
    jobject telephonymanager = (env)->CallObjectMethod(mContext, getSystemService, str);
    if (telephonymanager == 0) {
        return (env)->NewStringUTF("unknown");
    }
    jclass cls_tm = (env)->FindClass("android/telephony/TelephonyManager");
    if (cls_tm == 0) {
        return (env)->NewStringUTF("unknown");
    }
    jmethodID getDeviceId = (env)->GetMethodID(cls_tm, "getDeviceId", "()Ljava/lang/String;");
    if (getDeviceId == 0) {
        return (env)->NewStringUTF("unknown");
    }
    jobject deviceid = (env)->CallObjectMethod(telephonymanager, getDeviceId);
    return (jstring) deviceid;
}

jstring getAppendedString(JNIEnv *env, jobject thiz, jstring s1, jstring s2) {

    const char *s1x = (env)->GetStringUTFChars(s1, NULL);
    const char *s2x = (env)->GetStringUTFChars(s2, NULL);

    char *sall = new char[strlen(s1x) + strlen(s2x) + 1];
    strcpy(sall, s1x);
    strcat(sall, s2x);

    jstring retval = (env)->NewStringUTF(sall);

    (env)->ReleaseStringUTFChars(s1, s1x);
    (env)->ReleaseStringUTFChars(s2, s2x);
    free(sall);

    return retval;
}

//获取公钥
jstring getPublicKey(JNIEnv *env, jobject thiz, jobject context) {
    jclass context_cls = env->GetObjectClass(context);
    jmethodID get_package_manager_mid = env->GetMethodID(context_cls, "getPackageManager",
                                                         "()Landroid/content/pm/PackageManager;");
    jmethodID get_package_name_mid = env->GetMethodID(context_cls, "getPackageName",
                                                      "()Ljava/lang/String;");
    env->DeleteLocalRef(context_cls);
    jobject pm_obj = env->CallObjectMethod(context, get_package_manager_mid);
    jclass pm_cls = env->FindClass("android/content/pm/PackageManager");
    jmethodID get_package_info_mid = env->GetMethodID(pm_cls, "getPackageInfo",
                                                      "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    jstring package_name = reinterpret_cast<jstring>(env->CallObjectMethod(
            context, get_package_name_mid));
    jfieldID flag_fid = env->GetStaticFieldID(pm_cls, "GET_SIGNATURES", "I");
    jint flag = env->GetStaticIntField(pm_cls, flag_fid);
    env->DeleteLocalRef(pm_cls);
    jobject pi_obj = env->CallObjectMethod(pm_obj, get_package_info_mid,
                                           package_name, flag);
    env->DeleteLocalRef(package_name);
    jclass pi_cls = env->FindClass("android/content/pm/PackageInfo");
    jfieldID signatures_fid = env->GetFieldID(pi_cls, "signatures",
                                              "[Landroid/content/pm/Signature;");
    env->DeleteLocalRef(pi_cls);
    jobject sig_obj = env->GetObjectField(pi_obj, signatures_fid);
    env->DeleteLocalRef(pi_obj);
    jobjectArray sigs = reinterpret_cast<jobjectArray>(sig_obj);

    jclass signature_cls = env->FindClass("android/content/pm/Signature");
    jmethodID to_byte_array_mid = env->GetMethodID(signature_cls, "toByteArray", "()[B");
    jbyteArray sig_bytes = reinterpret_cast<jbyteArray>(env->CallObjectMethod(
            env->GetObjectArrayElement(sigs, 0), to_byte_array_mid));
    jclass certificate_factory_cls = env->FindClass("java/security/cert/CertificateFactory");
    jmethodID get_certificate_instance_mid = env->GetStaticMethodID(certificate_factory_cls,
                                                                    "getInstance",
                                                                    "(Ljava/lang/String;)Ljava/security/cert/CertificateFactory;");
    jobject certificate_factory_obj = env->CallStaticObjectMethod(certificate_factory_cls,
                                                                  get_certificate_instance_mid,
                                                                  env->NewStringUTF("X509"));
    jmethodID generate_certificate_mid = env->GetMethodID(certificate_factory_cls,
                                                          "generateCertificate",
                                                          "(Ljava/io/InputStream;)Ljava/security/cert/Certificate;");
    env->DeleteLocalRef(certificate_factory_cls);
    jclass certificate_cls = env->FindClass("java/security/cert/Certificate");
    jclass byte_input_stream_cls = env->FindClass("java/io/ByteArrayInputStream");
    jmethodID new_sig_bytes_is_mid = env->GetMethodID(byte_input_stream_cls, "<init>", "([B)V");
    jobject sig_bytes_is = env->NewObject(byte_input_stream_cls, new_sig_bytes_is_mid, sig_bytes);
    env->DeleteLocalRef(sig_bytes);
    env->DeleteLocalRef(byte_input_stream_cls);
    jobject cert = env->CallObjectMethod(certificate_factory_obj, generate_certificate_mid,
                                         sig_bytes_is);
    env->DeleteLocalRef(sig_bytes_is);
    env->DeleteLocalRef(certificate_factory_obj);
    jmethodID get_pubic_key_mid = env->GetMethodID(certificate_cls, "getPublicKey",
                                                   "()Ljava/security/PublicKey;");
    env->DeleteLocalRef(certificate_cls);

    jobject publicKey = env->CallObjectMethod(cert, get_pubic_key_mid);
    jclass publicKey_cls = env->GetObjectClass(publicKey);
    jmethodID toString_mid = env->GetMethodID(publicKey_cls, "toString", "()Ljava/lang/String;");
    jstring publicKey_str = static_cast<jstring>(env->CallObjectMethod(publicKey, toString_mid));
    env->DeleteLocalRef(cert);
    env->DeleteLocalRef(publicKey_cls);
    env->DeleteLocalRef(publicKey);

    jclass string_cls = env->GetObjectClass(publicKey_str);
    jmethodID indexOf_mid = env->GetMethodID(string_cls, "indexOf", "(Ljava/lang/String;)I");
    jstring param = env->NewStringUTF("modulus");
    jint aa = env->CallIntMethod(publicKey_str, indexOf_mid, param);
    jstring param2 = env->NewStringUTF("publicExponent");
    jint bb = env->CallIntMethod(publicKey_str, indexOf_mid, param2);

    jmethodID substring_mid = env->GetMethodID(string_cls, "substring", "(II)Ljava/lang/String;");

    jstring publicKey2_str = static_cast<jstring>(env->CallObjectMethod(publicKey_str,
                                                                        substring_mid, aa + 8,
                                                                        bb - 1));

    return publicKey2_str;
}

//获取包名
jstring getPackageName(JNIEnv *env, jobject thiz, jobject context) {

    jclass native_clazz = env->GetObjectClass(context);

    // 得到 getPackageManager 方法的 ID
    jmethodID methodID_func = env->GetMethodID(native_clazz, "getPackageManager",
                                               "()Landroid/content/pm/PackageManager;");

    // 获得应用包的管理器
    jobject package_manager = env->CallObjectMethod(context, methodID_func);

    // 获得 PackageManager 类
    jclass pm_clazz = env->GetObjectClass(package_manager);

    // 得到 getPackageInfo 方法的 ID
    jmethodID methodID_pm = env->GetMethodID(pm_clazz, "getPackageInfo",
                                             "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");

    //获取包名
    jmethodID methodID_packagename = env->GetMethodID(native_clazz, "getPackageName",
                                                      "()Ljava/lang/String;");
    jstring name_str = static_cast<jstring>(env->CallObjectMethod(context, methodID_packagename));

    return name_str;
}

jstring toHex(JNIEnv *env, jbyteArray digested_bytes) {
    jclass big_integer_cls = env->FindClass("java/math/BigInteger");
    jmethodID new_big_integer_mid = env->GetMethodID(big_integer_cls, "<init>", "(I[B)V");
    jobject big_integer_obj = env->NewObject(big_integer_cls, new_big_integer_mid, 1,
                                             digested_bytes);
    env->DeleteLocalRef(digested_bytes);
    jmethodID to_String_mid = env->GetMethodID(big_integer_cls, "toString",
                                               "(I)Ljava/lang/String;");
    env->DeleteLocalRef(big_integer_cls);
    return reinterpret_cast<jstring>(env->CallObjectMethod(big_integer_obj, to_String_mid, 16));
}

jbyteArray getDigestedBytes(JNIEnv *env, jbyteArray complex_bytes) {
    static jobject satic_message_digest_obj = __null;
    jclass message_digest_cls = env->FindClass("java/security/MessageDigest");
    jmethodID get_instance_mid = env->GetStaticMethodID(message_digest_cls, "getInstance",
                                                        "(Ljava/lang/String;)Ljava/security/MessageDigest;");
    if (satic_message_digest_obj == __null) {
        jobject local_message_digest_obj = env->CallStaticObjectMethod(message_digest_cls,
                                                                       get_instance_mid,
                                                                       env->NewStringUTF("MD5"));
        satic_message_digest_obj = env->NewGlobalRef(local_message_digest_obj);
        env->DeleteLocalRef(local_message_digest_obj);
    }
    jmethodID digest_mid = env->GetMethodID(message_digest_cls, "digest", "([B)[B");
    env->DeleteLocalRef(message_digest_cls);
    return reinterpret_cast<jbyteArray>(env->CallObjectMethod(satic_message_digest_obj, digest_mid,
                                                              complex_bytes));
}

jbyteArray toBytes(JNIEnv *env, jstring string) {
    jclass string_cls = env->FindClass("java/lang/String");
    jmethodID get_bytes_mid = env->GetMethodID(string_cls, "getBytes", "(Ljava/lang/String;)[B");
    return reinterpret_cast<jbyteArray>(env->CallObjectMethod(string, get_bytes_mid,
                                                              env->NewStringUTF(UTF_8)));
}

jstring getMD5(JNIEnv *env, jstring jInfo) {
    jbyteArray digested_bytes = getDigestedBytes(env, toBytes(env, jInfo));
    return toHex(env, digested_bytes);
}

jstring getLocalKey(JNIEnv *env, jobject thiz, jobject context) {

    jstring imei = getAppendedString(env, thiz, getDeviceID(env, thiz, context),
                                     getSerialNumber(env, thiz, context));
    jstring sign = getPublicKey(env, thiz, context);
    jstring imei_sign = getAppendedString(env, thiz, imei, sign);
    jstring imei_sign_package = getAppendedString(env, thiz, imei_sign,
                                                  getPackageName(env, thiz, context));
    //请再加入自己的移位或替换 或其他加密算法,例如我又append了一次imei
    imei_sign_package = getAppendedString(env, thiz, imei_sign_package, imei);
    return getMD5(env, imei_sign_package);
}


