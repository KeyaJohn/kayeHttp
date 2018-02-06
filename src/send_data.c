#include "server.h"
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
