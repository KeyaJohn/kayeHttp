
#include "server.h"


void deal_request(int fd)
{
    char method[SIZE] ;
    char url[SIZE];
    int len;
    char buff[BUFFSIZE];
    char parm[SIZE];
    char head[BUFFSIZE];
    char length[SIZE];
    memset(method,'\0',SIZE);
    memset(parm, '\0',SIZE);
    memset(length,'\0',SIZE);
    memset(url,'\0',SIZE);
    memset(buff,'\0',SIZE);
    memset(head,'\0',SIZE);
    get_str(fd,buff);
     
    while(strncmp(head,"\r\n",2) != 0)
    {
        get_str(fd,head) ;
        if( strncmp(head,"Content-Length:",15) == 0 )
        {
            char *p = head + 16;
            char num[16] ;
            int i = 0;
            while ( *p != '\r' )
            {
                num[i++] = *p;
                p++;
            }
            num[i] = '\0';
            printf("num: %s\n",num);
            len = atoi(num);
            printf("len: %d\n",len);
        }
        printf("%s",head);
    }
    
    
    get_url_method_parm(fd,url,method,parm,buff);
    
    if( (strncmp(method,"GET",3) == 0 ) && (strlen(parm) == 0) )
    {
        respond_GET(fd,url);
    }
    else 
    {
        exec_cgi(fd,method,url,parm,len);
        
    }
}