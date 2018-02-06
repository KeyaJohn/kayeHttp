/*************************************************************************
	> File Name:main.c 
	> Author:kayejohn 
	> Mail:1572831416@qq.com 
	> Created Time: 2018年01月25日 星期四 19时45分20秒
 ************************************************************************/

#include "server.h"
#include"log.h"

extern zlog_category_t *main_log ;

//预防僵死进程
void deal_child(int sig)
{
    wait(NULL);
}
//设置非阻塞
void setnoblocking(int fd)
{
    int flags = 0;

    if( (flags = fcntl(fd,F_GETFL,0)) < 0 )
    {
        perror("fcntl err\n");
        return ;
    }

    flags |= O_NONBLOCK;
    if( (fcntl(fd,F_SETFL,flags)) < 0 )
    {
        perror("fcntl err\n");
        return ;
    }
}

int main(int argc,char* argv[])
{
    main_log = creat_log();
    
    int sockfd = creat_sock();

    if( sockfd == -1 )
    {
        //perror("create socket faile\n");
        write_log(main_log,strerror(errno),ERROR);
        exit(EXIT_FAILURE);
    }
    
    int on = 1;
    if( (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))) < 0 )
    {
        //perror( " setsockopt err\n" );
        write_log(main_log,strerror(errno),ERROR);
        exit(EXIT_FAILURE);
    }
   
    signal(SIGCLD,deal_child);

    while( 1 )
    {
        int newfd = accept_sock(sockfd);
        if( newfd == -1 )
        {
            perror("accepr err\n");
        }
        
        setnoblocking(newfd);
        pid_t pid;
        if( (pid = fork()) < 0)
        {
            write_log(main_log,strerror(errno),ERROR);
            exit(EXIT_FAILURE);
        }
        else if( pid == 0  )
        {
            deal_request(newfd);
            close(newfd);
            exit(1);
        }
    }
    //main_epoll(sockfd);
    

    return 0;
}

