// Last Update:2017-01-07 11:24:55
/**
 * @file scanf.cpp
 * @brief i
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-01-07
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
    char *str = "01FF";
    int r = 0;
    sscanf(str, "%x", &r) ;
    printf("r = %x, %d\n",r, r);
    int a = 10, b = 20;
    printf("a++b = %d\n", a + + b);
    return r ;
}
