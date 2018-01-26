// Last Update:2017-11-15 09:27:00
/**
 * @file mthread.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-11-15
 */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>

pthread_mutex_t mutex;
void mthread_func()
{
}


void thr_func(void *userdata)
{
}


int main(int argc, char *argv[])
{
    pthread_mutex_init(&mutex,NULL);
    return 0;
}
