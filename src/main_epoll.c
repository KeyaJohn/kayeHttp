/*************************************************************************
	> File Name: main_epoll.c
	> Author: kayejohn
	> Mail: 1572831416@qq.com
	> Created Time: 2018年01月31日 星期三 19时57分08秒
 ************************************************************************/

#include"server.h"

int main_epoll(int sockfd)
{
   struct epoll_event evs[MAX_EPOLL],ev;
   ev.events = EPOLLIN;
   ev.data.fd = sockfd;

   int clifd; 
   struct sockaddr_in cli_addr;
   int epfd = epoll_create(MAX_EPOLL);
   if( epfd < 0 )
   {
       perror("epoll create err\n");
       return -1;
   }

   int ret = epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&ev);
   if( ret == -1 )
   {
       perror("epoll ctl err\n");
       exit(EXIT_FAILURE);
   }

    while(1)
    {
        int nfds = epoll_wait(epfd,evs,10,3000);
     //   printf("%d\n",nfds);
        if( nfds  < 0 )
        {
            printf("epoll wait err\n");
            continue;
        }
        else if( nfds == 0 )
        {
            printf("time out \n");
            continue;
        }
        int i = 0;
        int len;
        for(;i<nfds;i++)
        {
            if( evs[i].data.fd == sockfd )
            {
                int cli_fd = accept(sockfd,(struct sockaddr*)&cli_addr,&len);
                if( cli_fd < 0  )
                {
                    perror("accept err\n");
                    exit(EXIT_FAILURE);
                }
                ev.data.fd = cli_fd;
                ev.events = EPOLLIN;
                epoll_ctl(epfd,EPOLL_CTL_ADD,cli_fd,&ev);
            }
            else if( evs[i].events & EPOLLIN )
            {
                
                deal_request(evs[i].data.fd);
               // epoll_ctl(epfd,EPOLL_CTL_ADD ,evs[i].data.fd,&ev);
                //close(evs[i].data.fd);
                continue;
                //printf("buff : %s\n",buff);

                
            }
            else
            {
                epoll_ctl(epfd,EPOLL_CTL_ADD ,evs[i].data.fd,&ev);
                close(evs[i].data.fd);
            }
        }
    }

} 
