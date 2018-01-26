// Last Update:2017-12-18 16:47:56
/**
 * @file test_swap.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-12-18
 */

#include <stdio.h>
#include <vector>
using namespace std;


int main(int argc, char *argv[])
{
    vector<int> v1(5);
    vector<int> v2(8);
    int i =0;
    for(i = 0;i<=5;i++)
    {
        v1.push_back(i);
        v2.push_back(i);
    }
    for(i; i<= 8; i++)
    {
        v2.push_back(i);
    }
    vector<int>::iterator it1 = v1.begin();
    vector<int>::iterator it2 = v2.begin();

    for(i = 0; i <= 4; i++)
    {
        printf("it1[%d] = %d\n", i, *it1++);
        printf("it2[%d] = %d\n", i, *it2++);
    }
    //v1.swap(v2);
    int idx = i;
    for(; it1 != v1.end(); it1++, idx++)
    {
        printf("it1[%d] = %d\n", idx, *it1);
    }
    idx = i;
    for(; it2 != v2.end(); it2++, idx++)
    {
        printf("it2[%d] = %d\n", idx, *it2);
    }

    return 0;
}
