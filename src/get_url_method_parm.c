

#include "server.h"
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

void get_url_method_parm(int sockfd,char url[],char method[],char parm[],char buff[])
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
    
    i = 0,j = 0;
    p++;
    while( *p != ' ')
    {
        if( *p == '?' )
        {
            p ++;
            while( *p != ' ')
            {
                parm[j++] = *p;
                p++;
            }
            break;
        }
        url[i++] = *p;
        p++;
    }

    url[i] = '\0';
    parm[j] = '\0';
    //printf( "method:%s length :%ld\n" ,method,strlen(method));
    //printf( "url:%s length :%ld\n" ,url,strlen(url));
    //printf( "parm:%s length :%ld\n" ,parm,strlen(parm));
}




