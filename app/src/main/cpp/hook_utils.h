#include <stdio.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <android/log.h>
#include <jni.h>

#include <string.h>

#include <dlfcn.h>

// /* hook 包含 */
#include "hookzz.h"


#include <signal.h>
#include <unistd.h>


#define ZzReplaceE(X)  ZzReplace(reinterpret_cast<void *>(X), reinterpret_cast<void *>(my_##X), reinterpret_cast<void **>(&sys_##X))

#ifndef ZREG_MACRO
#define ZREG_MACRO
#if defined(__LP64__)
#define ZREG(n) general.regs.x##n
#else
#define ZREG(n) general.regs.r##n
#endif
#endif

#ifndef LOGE
#define LOG_TAG "HookZzNo1"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#endif

#define __YEAR__ ((((__DATE__[7] - '0') * 10 + (__DATE__[8] - '0')) * 10 + (__DATE__[9] - '0')) * 10 + (__DATE__[10] - '0'))

#define __MONTH__ (__DATE__[2] == 'n' ? 0 : __DATE__[2] == 'b' ? 1 : __DATE__[2] == 'r' ? (__DATE__[0] == 'M' ? 2 : 3) : __DATE__[2] == 'y' ? 4 : __DATE__[2] == 'n' ? 5 : __DATE__[2] == 'l' ? 6 : __DATE__[2] == 'g' ? 7 : __DATE__[2] == 'p' ? 8 : __DATE__[2] == 't' ? 9 : __DATE__[2] == 'v' ? 10 : 11)

#define __DAY__ ((__DATE__[4] == ' ' ? 0 : __DATE__[4] - '0') * 10 + (__DATE__[5] - '0'))

#define __DATE_AS_INT__ (((YEAR - 2000) * 12 + MONTH) * 31 + DAY)


