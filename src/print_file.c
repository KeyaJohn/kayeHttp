#include "server.h"
#include"log.h"

extern zlog_category_t *main_log;

void print_file(int sockfd,char path[])
{
    char buff[SIZE];
    if( access(path,F_OK) != 0 )
    {
        respond_err(sockfd);
    }
    FILE *fp = NULL;
    if( (fp = fopen(path,"r"))  == NULL )
    {
        printf("open file fail\n");
        write_log(main_log,strerror(errno),ERROR);
        return ;
    }
    while ( fgets(buff,SIZE,fp) != NULL )
    {
        printf("%s",buff);
        write_log(main_log,buff,INFO);
    }

}
