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
    int on;
    if( (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))) < 0 )
    {
        perror( " setsockopt err\n" );
        exit(EXIT_FAILURE);
    }
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
    printf("host :%s link successfully kaytHttp！\n",inet_ntoa(cli_addr.sin_addr));

    return sockfd;
}


void get_str(int sockfd ,char buff[])
{
    char c = '\0';
    int i = 0,j = 0;

    while( c != '\n' )
    {
        int len = recv(sockfd,&c,1,0);
        if( len > 0  )
        {
            buff[i++] = c;
        }
        else 
        {
            buff[i] = '\n';
        }
    }
    buff[i-1] = '\n';
    buff[i] = '\0';
//   printf("buff:%s ;length :%d\n",buff,(int )strlen(buff));
}

void get_url_method(int sockfd,char url[],char method[],char buff[])
{
    int i=0,j=0;
    char *p = buff;
    while( *p != ' ')
    {
        method[i] = *p;
        i++;
        p++;
    }
    method[i] = '\0';
    
    p++;
    while( *p != ' ' )
    {
        url[j++] = *p;
        p++;
    }
    url[j] = '\0';
    printf( "method:%s length :%d\n" ,method,(int )strlen(method));
    printf( "url:%s length :%d\n" ,url,(int )strlen(url));
}

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

void send_data(int sockfd,char buff[],int len)
{
    int r_len = 0;

    while( r_len < len )
    {
        int ret = send(sockfd,buff+r_len,len-r_len,0);
        if( ret < 0  )
        {
            if(errno == EAGAIN || errno == EINTR)
            {
                continue ;
            }
            perror("send err\n");
            return ;
        }
        r_len += len;
    }
}
void respond_data(int sockfd,char *path)
{
    int  fp = open(path,O_RDONLY);
    if( fp  == -1  )
    {
        perror("open file err\n");
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
        puts("sssssssssss\n") ;
        respond_err(fd);
    }

}
void deal_request(int fd)
{
    char method[SIZE] ;
    char url[SIZE];
    char buff[BUFFSIZE];
    char head[BUFFSIZE];
    memset(method,'\0',SIZE);
    memset(url,'\0',SIZE);
    memset(buff,'\0',SIZE);
    memset(head,'\0',SIZE);
    get_str(fd,buff);
    
    while(strncmp(head,"\r\n",2) != 0)
    {
        get_str(fd,head) ;
    }
    
    
    get_url_method(fd,url,method,buff);
    
    if( strncmp(method,"GET",3) == 0 )
    {
        respond_GET(fd,url);
    }
    else if( strncmp(method,"POST",3) == 0 )
    {
        
    }
   
}
