/*************************************************************************
	> File Name: server.h
	> Author:kayejohn 
	> Mail:1572831416@qq.com 
	> Created Time: 2018年01月25日 星期四 19时41分22秒
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define LINK_NUM  5
#define BUFFZSIZE 1024
#define SERVER_PORT  80
#define SERVER_IP "192.168.93.128"
int  creat_sock();

#endif
