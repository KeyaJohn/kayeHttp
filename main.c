/*************************************************************************
	> File Name:main.c 
	> Author:kayejohn 
	> Mail:1572831416@qq.com 
	> Created Time: 2018年01月25日 星期四 19时45分20秒
 ************************************************************************/

#include "server.h"


int main(int argc,char* argv[])
{
    
    int sockfd = creat_sock();
    if( sockfd == -1 )
    {
        perror("create socket faile\n");
        exit(EXIT_FAILURE);
    }
    
    while( 1 )
    {
        printf("等待客户端进行连接!\n");
        
        int newfd = accept_sock(sockfd);
        
        deal_request(sockfd);
        
    }
    return 0;
}

