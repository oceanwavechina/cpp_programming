/*
 * wrap-preload.h
 *
 *  Created on: May 5, 2017
 *      Author: liuyanan
 */

#ifndef WRAP_PRELOAD_H_
#define WRAP_PRELOAD_H_

#include <dlfcn.h>
#include <stdio.h>


ssize_t write(int fd, const void *buf, size_t count)
{
    printf("custom wrapped: %s\n", buf);
    //dlsym 调用系统函数执行该有的操作
    return count;
}

int puts(const char* str)
{
    printf("custom wrapped: %s\n", str);
}

size_t strlen(const char *s)
{
	printf("custom wrapped: ");
    return 100;
}



#endif /* WRAP_PRELOAD_H_ */
