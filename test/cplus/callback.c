// Last Update:2017-05-31 14:10:09
/**
 * @file callback.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-05-31
 */

#include <stdio.h>

typedef void (redisCallbackFn)(int status);
typedef struct _app
{
    redisCallbackFn *fn;
    int status;
}app;
redisCallbackFn *fn;

void setAppCallBack(app *p_ap, redisCallbackFn fn)
{
    if (p_ap != NULL)
        p_ap->fn = fn;
}


void callback (int status)
{
    printf("status = %d.\n",status);
}


int main(int argc, char *argv[])
{
    app ap;
    ap.status = 10;
    //ap.fn = callback;
    setAppCallBack(&ap, callback);

    ap.fn(ap.status);





    return 0;
}
