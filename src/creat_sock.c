/*************************************************************************
	> File Name: server.c
	> Author:kayejohn 
	> Mail:1572831416@qq.com 
	> Created Time: 2018年01月25日 星期四 19时45分20秒
 ************************************************************************/
#include "server.h"
#include"log.h"

extern zlog_category_t * main_log;
int creat_sock()
{
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if( sockfd == -1  ) 
    {
        //perror("create socket\n");
        write_log(main_log,strerror(errno),ERROR);
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(SERVER_PORT);
    myaddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    int on = 1;
    if( (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))) < 0 )
    {
        //perror( " setsockopt err\n" );
        write_log(main_log,strerror(errno),ERROR);
        exit(EXIT_FAILURE);
    }
    int ret = bind(sockfd,(struct sockaddr*)&myaddr,sizeof(struct sockaddr));
    if( ret == -1 )
    {
        //perror("bind err\n");
        write_log(main_log,strerror(errno),ERROR);
        exit(EXIT_FAILURE);
    }
    listen(sockfd,LINK_NUM);
    
    return sockfd;
}












