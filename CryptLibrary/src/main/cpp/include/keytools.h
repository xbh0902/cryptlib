#ifndef CRYPTLIB_RANDOM_TOOL_H
#define CRYPTLIB_RANDOM_TOOL_H
#include "xlib.h"
#include "md5.h"

string generateAlphaAndDigit(int lenght);

string getLocalKey(JNIEnv *env, jobject thiz, jobject context);


#endif //CRYPTLIB_RANDOM_TOOL_H
