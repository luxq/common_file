// Last Update:2017-09-14 17:59:37
/**
 * @file sprinttest.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-03-30
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    char *ll = "18445238691818483411a";
    uint64_t l = strtol(ll,0,10);
    printf("ll is %s, l is 0x%lx.\n", ll, l);
    uint64_t ul = strtoul(ll,0,10);
    printf("ll is %s, l is 0x%lx.\n", ll, ul);
    char *i = "2147483647";
    uint32_t i_32 = strtol(i, 0, 10);
    printf("ll is %s, l is 0x%x.\n", ll, i_32);
    uint32_t iu_32 = strtoul(i, 0, 10);
    printf("ll is %s, l is 0x%x.\n", ll, iu_32);
    iu_32 = atoi(i);
    printf("ll is %s, l is 0x%x.\n", ll, iu_32);
    iu_32 = atol(i);
    printf("ll is %s, l is 0x%x.\n", ll, iu_32);
    //char tmp[3] = {0};
    //char s = 0x92;
    //memset(tmp, 0, sizeof(tmp));
    //sprintf(tmp, "%02x", 0x92);
    //printf("tmp = %s.\n",tmp);
    //memset(tmp, 0, sizeof(tmp));
    //sprintf(tmp, "%02x", s);
    //printf("tmp = %s.\n",tmp);
    return 0;
}
