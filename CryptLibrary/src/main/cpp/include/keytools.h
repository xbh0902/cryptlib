#ifndef CRYPTLIB_RANDOM_TOOL_H
#define CRYPTLIB_RANDOM_TOOL_H
#define UTF_8 "utf-8"
#include "xlib.h"
#include "md5.h"

string generateAlphaAndDigit(int lenght);

jstring getLocalKey(JNIEnv *env, jobject thiz, jobject context);


#endif //CRYPTLIB_RANDOM_TOOL_H
