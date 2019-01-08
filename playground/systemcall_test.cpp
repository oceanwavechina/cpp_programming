/*
 * custom_systemcall.cpp
 *
 *  Created on: May 5, 2017
 *      Author: liuyanan
 */


#include <stdio.h>

#define CISTEOM

#ifdef CISTEOM
	#include <unistd.h>

	/*
	 * 加了 <string.h> 这个头文件后：
	 * 		#include <string.h>
	 * 		#include "wrap-preload.h"
	 * 	 	为啥常量字符 和 变量 执行的结果不同呢？？
	 */
	#include <string.h>

	#include "wrap-preload.h"
#else
	#include <unistd.h>
	#include <string.h>
#endif

int main()
{
	const char* msg = "liuyanan";

	printf("strlen() of literal liuyanan is: %zu\n", strlen("liuyanan"));
    printf("strlen() of var %s is: %zu\n", msg, strlen(msg));

    printf("\n");

    write(0, "write()!", 8);
    printf("\n");

    puts("puts()!");

    return 0;
}
