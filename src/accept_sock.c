#include "server.h"

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
    printf("host :%s link successfully kaytHttp！\n",inet_ntoa(cli_addr.sin_addr));

    return sockfd;
}
