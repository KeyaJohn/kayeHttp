#include "server.h"


void respond_head(int sockfd)
{
    char buff[SIZE];
    memset(buff,'\0',SIZE);
    strcpy(buff,"HTTP/1.0 200 OK\r\n");
    send(sockfd,buff,strlen(buff),0);
    
    strcpy(buff,"Server: jdbhttpd/0.1.0\r\n");
    send(sockfd,buff,strlen(buff),0);
   
    strcpy(buff,"Content-Type: text/html\r\n") ;
    send(sockfd,buff,strlen(buff),0);
   
    strcpy(buff,"\r\n") ;
    send(sockfd,buff,strlen(buff),0);
}