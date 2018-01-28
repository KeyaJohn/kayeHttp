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
#include <signal.h>
#include <pthread.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#define SIZE 255
#define LINK_NUM  5
#define BUFFSIZE 1024
#define SERVER_PORT  5500
#define SERVER_IP "192.168.93.128"
#define STDIN 0
#define STDOUT 1
#define STDERR 2
int  creat_sock();

int accept_sock(int fd);

void deal_request(int fd);
void get_method_url(int fd,char url[],char method[],char buff[]);
#endif
