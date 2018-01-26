// Last Update:2016-12-14 13:19:37
/**
 * @file test.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2016-12-13
 */

#include <zmq.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[])
{
    void *zmq_ctxt = zmq_init(1);
    void *zmq_sckt = zmq_socket(zmq_ctxt, ZMQ_PULL);

    //zmq_bind(zmq_sckt, "ipc:///tmp/DataRuleEngine");
    zmq_bind(zmq_sckt, "tcp://*:5557");
    int i = 0;
    while(true)
    {
        char buf[128] = {0};
        zmq_msg_t *msg = new zmq_msg_t;
        zmq_pollitem_t item[2];
        item[0].socket = zmq_sckt;
        item[0].fd = 0;
        item[0].events = ZMQ_POLLIN;

        zmq_poll(item, 1, 5);
        i++;
        if(item[0].revents & ZMQ_POLLIN)
        {
            zmq_msg_init(msg);
            zmq_recvmsg(zmq_sckt,msg, 0);
            if(msg != NULL)
            {
                printf("recv msg successful, msg len = %d.\n", zmq_msg_size(msg));

                //memcpy(buf, zmq_msg_data(msg), zmq_msg_size(msg));
                //printf("msg data = %s.\n", buf);
                zmq_msg_close(msg);
                delete msg;
            }
        }
        if(i % 2 == 0)
        {
        //    printf("time count 1s\n");
            i = 0;
        }
    }

    return 0;
}
