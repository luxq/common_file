// Last Update:2017-11-24 13:31:20
/**
 * @file test_sleep.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-11-24
 */
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i = 0;
    while(1){
        i++;
        //sleep(1);
        if(i > 65535)
        {
            i = 0;
            sleep(1);
        }
    }
    return 0;
}
