//
// Created by z on 2018/7/7.
//
//

//
#include "hook_utils.h"
//

#include "hook_dl.h"
#include "hook_libc.h"

//
#include <sys/socket.h>
#include <netdb.h>

int (*_socket)(int __af, int __type, int __protocol);
int __socket(int __af, int __type, int __protocol)
{
    LOGE("[socket] af: %d \t type: %d \t protocol: %d", __af, __type, __protocol);
    int ret = _socket(__af, __type, __protocol);
    LOGE("[socket] out: %d", ret);
    return ret;
}

ssize_t (*_send)(int __fd, const void *__buf, size_t __n, int __flags);
ssize_t __send(int __fd, const void *__buf, size_t __n, int __flags)
{

    LOGE("[socket] send in");
    ssize_t ret = _send(__fd, __buf, __n, __flags);
    LOGE("[socket] send out");

    return ret;
}

int (*_getaddrinfo)(const char *hostname, const char *service, const struct addrinfo *hints, struct addrinfo **result);
int __getaddrinfo(const char *hostname, const char *service, const struct addrinfo *hints, struct addrinfo **result)
{

    LOGE("[getaddrinfo] hostname: %s \t service: %s", hostname, service);
    return _getaddrinfo(hostname, service, hints, result);
}

int g_int = 0;
void *(*sys_memcpy)(void *dest, const void *src, size_t n);
void *my_memcpy(void *dest, const void *src, size_t n)
{
    g_int++;
    return sys_memcpy(dest, src, n);
}

__attribute__((constructor)) void HookZzNo1_init()
{

    LOGE(" \r\nANDROID_API: %d | build time:%d-%02d-%02d %s",
         __ANDROID_API__, __YEAR__, __MONTH__ + 1, __DAY__, __TIME__);

    LOGE(" \tPowered By: HookZz              \t\t%p", &ZzReplace);

    open_hook();  // dalvik √  art √
    fopen_hook(); // dalvik √  art √

    dlopen_hook();  // dalvik √  art √
    dlsym_hook();   // dalvik √  art √
    dlclose_hook(); // dalvik √  art √



    
    LOGE("ZzReplace memcpy: %d", ZzReplaceE(memcpy));

    char *s = "testStr";
    char d[20] = {0};
    int tmp1, tmp2 = 0;

    tmp1 = g_int;
    memcpy(d, s, strlen(s));
    tmp2 = g_int;
    LOGE("memcpy: %s %d %d", d, tmp1, tmp2);
}
