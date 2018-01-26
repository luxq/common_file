// Last Update:2017-03-02 10:02:52
/**
 * @file formatstring.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-03-02
 */

#include <string>
#include <stdio.h>

int main(int argc, char *argv[])
{
    char buf[6] = {0};
    int i = 100000;
    sprintf(buf, "%05d",i);
    printf("buf = %s\n", buf);
    i = 1989890;
    sprintf(buf, "%05d",i);
    printf("buf = %s\n", buf);
    return 0;
}
