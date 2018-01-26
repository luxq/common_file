// Last Update:2017-03-01 14:07:24
/**
 * @file ntimes.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-03-01
 */

#include <string>
#include <stdio.h>
#include <algorithm> 
using namespace std;

int main(int argc, char *argv[])
{
    
    string s = "abcbdbsbebdfbd";
    string f = "bbbbbbbbbbbbbb";
    int n = count(s.begin(),s.end(), 'd');
    printf("d times = %d.\n", n);
    n = count(f.begin(),f.end(), 'b');
    printf("b times = %d, f len = %d.\n", n, f.length());
    printf("sizeof(int) = %d\n", sizeof(int));


    return 0;
}
