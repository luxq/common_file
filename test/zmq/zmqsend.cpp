// Last Update:2016-12-14 09:25:37
/**
 * @file zmqsend.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2016-12-13
 */

#include <zmq.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void *context = NULL;
void *socket = NULL;
int sendv(char *buf, int len)
{
    int ret = 0;
    zmq_msg_t msg;
    zmq_msg_init_size(&msg, len);
    memcpy(zmq_msg_data(&msg), buf, len);
    printf("begin to send.\n");
    ret = zmq_sendmsg(socket, &msg, ZMQ_NOBLOCK);
    printf("after send.\n");
    zmq_msg_close(&msg);
    return ret;
}
int main (void)
{
    context = zmq_init(1);
    socket = zmq_socket(context, ZMQ_PUSH);
    //zmq_connect(socket, "ipc:///tmp/DataRuleEngine");
    zmq_connect(socket, "tcp://172.19.22.111:5557");
    int ret = 0;
    while(true)
    {
        char *buf = "abc";
        ret = sendv(buf, strlen(buf));
        printf("send data ret = %d.\n", ret);
        sleep(3);
    }
    return 0;
}

