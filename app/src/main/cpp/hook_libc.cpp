#include "hook_libc.h"

/* hook fopen in libc.so */
/* ====================== BEGIN ======================  */
/* origin func */
void *(*sys_fopen)(const char *__file, int __mode);

/* new func */
void *my_fopen(const char *__file, int __mode)
{
    if (__file != NULL)
    {
        LOGE("[fopen] __mode: %d \t __file: %s", __mode, __file);
    }
    void *res = sys_fopen(__file, __mode);
    return res;
}

/* hook func */
void fopen_hook()
{
    int ret = ZzReplaceE(fopen);
    if (ret != RS_SUCCESS)
    {
        LOGE("ERROR: ZzReplace failed %d", ret);
        return;
    }
}
/* ======================  End  ======================  */

/* hook open in libc.so */
/* ====================== BEGIN ======================  */
/* origin func */
int (*sys_open)(const char *__file, int __oflag, ...);

/* new func */
int my_open(const char *__file, int __oflag, ...)
{
    if (__file != NULL)
    {
        LOGE("[open] __oflag: %d \t __file: %s", __oflag, __file);
    }
    va_list vl;
    va_start(vl, __oflag);
    int res = sys_open(__file, __oflag, vl); // 等于变长参数被改成了定参, 所以崩溃
    va_end(vl);
    LOGE("[open] out");
    return res;
}

void open_pre_call(RegisterContext *reg_ctx, const HookEntryInfo *info)
{
    char *path = (char *)reg_ctx->general.regs.r0; //->ZREG(0);
    int oflag = (int)reg_ctx->general.regs.r1;     //->ZREG(1);

    switch (oflag)
    {
    case O_RDONLY:
        LOGE("[FileMonitor|open|R] >>> %s\n", path);
        break;
    case O_WRONLY:
        LOGE("[FileMonitor|open|W] >>> %s\n", path);
        break;
    case O_RDWR:
        LOGE("[FileMonitor|open|RW] >>> %s\n", path);
        break;
    default:
        LOGE("[FileMonitor|open|%d] >>> %s\n", oflag, path);
        break;
    }
}

/* hook func */
void open_hook()
{
    //int ret = ZzReplaceE(open);
    int ret = ZzWrap((void *)open, open_pre_call, NULL);
    if (ret != RS_SUCCESS)
    {
        LOGE("ERROR: ZzWrap failed %d", ret);
        return;
    }
}
/* ======================  End  ======================  */