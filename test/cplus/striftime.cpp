// Last Update:2017-10-09 14:53:57
/**
 * @file striftime.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-10-09
 */

#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <vector>
#include <map>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <algorithm>


int main(int argc, char *argv[])
{
    time_t t;
    struct tm *p = NULL;
    t = 1507532407;
    p = localtime(&t);
    char s[128] = {0};
    strftime(s, 127, "%Y%m%d", p);
    printf("%d:%s\n", t, s);
    strftime(s, 127, "%H:%M:%S", p);
    printf("%d:%s\n", t, s);
    return 0;
}
