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
#include<zlog.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>

#include<sys/epoll.h>
#define MAX_EPOLL 1000

#include<sys/epoll.h>
#define MAX_EPOLL 1000
#define SIZE 255
#define LINK_NUM  5
#define BUFFSIZE 1024
#define SERVER_PORT  5500
#define SERVER_IP "192.168.93.128"

#define STDIN 0
#define STDOUT 1
#define STDERR 2


int main_epoll(int sockfd);


int  creat_sock();
void exec_cgi(int sockfd,char method[],char url[],char parm[],int len);
int accept_sock(int fd);
void deal_request(int fd);
void deal_request(int fd);
void get_method_url(int fd,char url[],char method[],char buff[]);
void get_str(int sockfd ,char buff[]);
void get_url_method_parm(int sockfd,char url[],char method[],char parm[],char buff[]);
void print_file(int sockfd,char path[]);
void respond_data(int sockfd,char *path);
void respond(int sockfd ,char url[]);
void respond_err( int sockfd );

void send_data(int sockfd,char buff[],int len);
int exit_is_file(char url[]);
void not_found(int sockfd);
void respond_GET(int fd,char url[]);
void respond_head(int sockfd);



#endif
