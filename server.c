/*************************************************************************
	> File Name: server.c
	> Author:kayejohn 
	> Mail:1572831416@qq.com 
	> Created Time: 2018年01月25日 星期四 19时45分20秒
 ************************************************************************/
#include "server.h"
int creat_sock()
{
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if( sockfd == -1  ) 
    {
        perror("create socket\n");
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(SERVER_PORT);
    myaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    int ret = bind(sockfd,(struct sockaddr*)&myaddr,sizeof(struct sockaddr));
    if( ret == -1 )
    {
        perror("bind err\n");
        exit(EXIT_FAILURE);
    }
    
    listen(sockfd,LINK_NUM);
    
    return sockfd;
}

int accept_sock(int fd)
{
    struct sockaddr_in cli_addr;
    memset(&cli_addr,'\0',sizeof(struct sockaddr_in));
    int len = sizeof(struct sockaddr);

    int sockfd = accept(fd,(struct sockaddr*)&cli_addr,&len);
    if( sockfd == -1 )
    {
        perror("accept err\n");
        exit(EXIT_FAILURE);
    }

    return sockfd;
}
