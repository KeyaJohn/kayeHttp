
#include "server.h"
#include"log.h"

extern zlog_category_t * main_log;

void exec_cgi(int sockfd,char method[],char url[],char parm[],int len)
{
    int pipe1[2],pipe2[2];  
    char block[SIZE] ;
    memset(block,'\0',SIZE);
    char path[SIZE] = "./httpdoc/";
    puts(path);
     
    if( pipe( pipe1 ) < -1 )
    {
        //perror("pipe1 err\n");
        write_log(main_log,strerror(errno),ERROR);
        return ;
    }
     
    if( pipe( pipe2 ) < -1 )
    {
        //perror("pipe2 err\n");
        write_log(main_log,strerror(errno),ERROR);
        return ;
    }
    
     
    respond_head(sockfd);
    puts("sssssssssssss\n");
    
    pid_t pid;
    if( (pid = fork()) < 0 )
    {
        //perror("fork err\n");
        write_log(main_log,strerror(errno),ERROR);
        return ;
    }
     
    
    if(  pid == 0 )
    {
        dup2(pipe1[0],STDIN);
        dup2(pipe2[1],STDOUT);
        close(pipe1[1]);
        close(pipe2[0]);


        char meth_env[255];
        char query_env[255];
        char length_env[255];
        
        sprintf(meth_env, "REQUEST_METHOD=%s", method);
        putenv(meth_env);
        sprintf(length_env, "CONTENT_LENGTH=%d", len);
        putenv(length_env);
        
         int ret = read(STDIN,block,len); 
        if( ret < 0)
        {
            printf("read err\n");
            return ;
        }
        
        char *p = block + 6;
        
        strcat(path,p);
       // printf("%s\n",path) ;
    
        print_file(sockfd,path);
    //    execl(path,parm,NULL);
    }
    else 
    {
        close(pipe1[0]);
        close(pipe2[1]);
        
        int i = 0;
        char c;
        for(;i<len;i++)
        {
            int ret = recv(sockfd,&c,1,0);
            if( ret > 0  )
            {
                write(pipe1[1],&c,1);
            }
        }

        while( read(pipe2[0],&c,1)>0 )
        {
            send(sockfd,&c,1,0);
        }
        waitpid(pid,NULL,0);
    }
}
