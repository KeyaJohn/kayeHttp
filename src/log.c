/*************************************************************************
	> File Name: test.c
	> Author: kayejohn
	> Mail: 1572831416@qq.com
	> Created Time: 2018年01月30日 星期二 15时31分10秒
 ************************************************************************/

#include"log.h"


zlog_category_t * main_log = NULL;

int write_log(zlog_category_t * plog,char *str,int flag)
{

    if( flag == ERROR  )
    {

        zlog_error(plog,str);
    }
    if( flag == DEBUG  )
    {
        zlog_debug(plog,str);
    }
    if( flag == WARN  )
    {
        zlog_warn(plog,str);
    }
    if( flag == INFO  )
    {
        zlog_info(plog,str);
    }
}

void del_log(zlog_category_t *plog)
{
    zlog_fini();
}

zlog_category_t *creat_log()
{
    int rc;
    zlog_category_t * plog = NULL;
    rc = zlog_init("test_hello.conf");
    if( rc )
    {
        perror("init failed\n");
        return NULL;
    }

    plog = zlog_get_category("my_cat");
    if( !plog )
    {
        printf("get cat fail\n");
        zlog_fini();
        return NULL;
    }
    
    return plog;
}

