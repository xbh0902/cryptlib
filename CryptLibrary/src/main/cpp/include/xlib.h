//
// Created by lulu on 17-10-9.
//

#ifndef CRYPTLIB_XLIB_H
#define CRYPTLIB_XLIB_H
#define UTF_8 "UTF-8"

#include <iostream>
#include <jni.h>
#include <cstring>
#include <stdlib.h>

using namespace std;

char *jstring2char(JNIEnv *env, jstring jstr);

jstring char2jstring(JNIEnv *env, const char *pat);

#endif //CRYPTLIB_XLIB_H
