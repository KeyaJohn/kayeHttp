#include "server.h"
#include"log.h"
extern zlog_category_t * main_log; 

void respond_data(int sockfd,char *path)
{
    int  fp = open(path,O_RDONLY);
    if( fp  == -1  )
    {
        //perror("open file err\n");
        write_log(main_log,strerror(errno),ERROR);
        return ;
    }
   //如果在url中没路径名，则默认是index.html    
    char buff[SIZE];
    memset(buff,'\0',SIZE);

    int len;
    while( (len = read(fp,buff,SIZE)) > 0)
    {
      //  printf("%s %d",buff,len);

        send_data(sockfd,buff,len);
        memset(buff,'\0',SIZE);
    }
    printf("send succesfully\n") ;
    close(fp);
}
void respond(int sockfd ,char url[])
{
    char path[SIZE] = "./httpdoc";

    char *p = strcat(path,url);
   // printf("file path:%s length:%ld\n",p,(size_t)strlen(p));
    
    respond_head(sockfd);

    respond_data(sockfd,p);

}

void respond_err( int sockfd )
{
    respond_data(sockfd,"./httpdoc/err");
}

int exit_is_file(char url[])
{
    char path[SIZE];
    memset(path,'\0',SIZE);
    sprintf(path,"./httpdoc%s",url);
    //printf("%s",path);
    if( access(path,F_OK) == 0)
    {
        return 1;
    }
    return 0;
}
void not_found(int sockfd)
{
    char buff[SIZE];
    memset(buff,'\0',SIZE);
    strcpy(buff,"HTTP/1.0 404 NOT FOUND\r\n");
    send(sockfd,buff,strlen(buff),0);
    
   // strcpy(buff,"Server: jdbhttpd/0.1.0\r\n");
    //send(sockfd,buff,strlen(buff),0);
   
    strcpy(buff,"Content-Type: text/html\r\n") ;
    send(sockfd,buff,strlen(buff),0);
   
    strcpy(buff,"\r\n") ;
    send(sockfd,buff,strlen(buff),0);
}

void respond_GET(int fd,char url[])
{
     if( strcmp(url,"/") == 0 )
    {
        respond(fd,"/index.html");
    }
    else if ( exit_is_file(url)) 
    {         
        respond(fd,url);
    }
    else
    {
        not_found(fd);
        respond_err(fd);
    }

}
