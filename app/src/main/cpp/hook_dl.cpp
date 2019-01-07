#include "hook_dl.h"

/* hook dlopen */
/* ====================== BEGIN ======================  */
/* 原函数 */
void *(*sys_dlopen)(const char *__file, int __mode);

/* 新函数 */
void *my_dlopen(const char *__file, int __mode)
{
    void *res = NULL;
    if (__file != NULL)
    {
        LOGE("[dlopen] __mode: %d \t __file: %s", __mode, __file);
    }

    res = sys_dlopen(__file, __mode);
    return res;
}
/* hook函数 */
void dlopen_hook()
{
    int ret = ZzReplaceE(dlopen);
    if (ret != RS_SUCCESS)
    {
        LOGE("ERROR: ZzReplace failed %d", ret);
        return;
    }
}

/* ======================  End  ======================  */

/* hook dlsym */
/* ====================== BEGIN ======================  */
/* 原函数 */
void *(*sys_dlsym)(void *__handle, const char *__symbol);

/* 新函数 */
void *my_dlsym(void *__handle, const char *__symbol)
{
    if (__symbol != NULL)
    {
        LOGE("[dlsym] __handle: %p \t __symbol: %s", __handle, __symbol);
    }
    void *res = sys_dlsym(__handle, __symbol);

    return res;
}
/* hook函数 */
void dlsym_hook()
{
    int ret = ZzReplaceE(dlsym);
    if (ret != RS_SUCCESS)
    {
        LOGE("ERROR: ZzReplace failed %d", ret);
        return;
    }
}
/* ======================  End  ======================  */

/* hook dlclose */
/* ====================== BEGIN ======================  */
/* 原函数 */
int (*sys_dlclose)(void *__handle);

/* 新函数 */
int my_dlclose(void *__handle)
{

    int res = sys_dlclose(__handle);
    LOGE("[dlclose] __handle: %p", __handle);
    return res;
}
/* hook函数 */
void dlclose_hook()
{
    int ret = ZzReplaceE(dlclose);
    if (ret != RS_SUCCESS)
    {
        LOGE("ERROR: ZzReplace failed %d", ret);
        return;
    }
}
/* ======================  End  ======================  */