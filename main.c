/*************************************************************************
	> File Name:main.c 
	> Author:kayejohn 
	> Mail:1572831416@qq.com 
	> Created Time: 2018年01月25日 星期四 19时45分20秒
 ************************************************************************/

#include "server.h"


void deal_child(int sig)
{
    wait(NULL);
}
int main(int argc,char* argv[])
{
    
    int sockfd = creat_sock();
    if( sockfd == -1 )
    {
        perror("create socket faile\n");
        exit(EXIT_FAILURE);
    }
    
    int on;
    if( (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))) < 0 )
    {
        perror( " setsockopt err\n" );
        exit(EXIT_FAILURE);
    }
    
    signal(SIGCLD,deal_child);
    while( 1 )
    {
        int newfd = accept_sock(sockfd);
        
        pid_t pid;
        if( (pid = fork()) < 0)
        {
            perror("fork err\n");
            exit(EXIT_FAILURE);
        }
        else if( pid == 0  )
        {
            deal_request(newfd);
            close(newfd);
            exit(1);
        }
    }
    return 0;
}

