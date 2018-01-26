// Last Update:2016-12-09 16:44:14
/**
 * @file dynamic_func.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2016-12-09
 */

#include <stdio.h>
#include <string>
#include <map>
using namespace std;

int get_variable(string type, string name, string value)
{
    return 0;
}

template<int x, int y>
struct ADD
{
    enum {RESULT = (x > y) ? x+20:y+100};
};

int main(int argc, char *argv[])
{
    int a = ADD<2,3>::RESULT;
    printf("a = %d.\n", a);
    return 0;
}
