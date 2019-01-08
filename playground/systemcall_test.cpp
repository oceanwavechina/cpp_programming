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
	 * ���� <string.h> ���ͷ�ļ���
	 * 		#include <string.h>
	 * 		#include "wrap-preload.h"
	 * 	 	Ϊɶ�����ַ� �� ���� ִ�еĽ����ͬ�أ���
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
