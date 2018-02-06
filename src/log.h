/*************************************************************************
	> File Name: log.h
	> Author: kayejohn
	> Mail: 1572831416@qq.com
	> Created Time: 2018年01月31日 星期三 09时21分28秒
 ************************************************************************/

#ifndef _LOG_H
#define _LOG_H
#include<stdio.h>
#include<stdlib.h>
#include<zlog.h>
#include<string.h>


#define ERROR 20
#define WARN 30
#define DEBUG  40
#define INFO 50




int write_log(zlog_category_t * plog,char *str,int flag);

zlog_category_t *creat_log();
#endif
