// Last Update:2017-07-21 10:22:48
/**
 * @file stltest.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-07-21
 */
#include <stdio.h>
#include <vector>
#include <map>
#include <string>
using namespace std;

bool get_map_value(map<string, string> &p_val)
{
    map<string, string> p_tmp;
    p_tmp.insert(make_pair("k1", "v1"));
    p_tmp.insert(make_pair("k2", "v2"));
    p_tmp.insert(make_pair("k3", "v3"));
    p_tmp.insert(make_pair("k4", "v4"));
    p_val = p_tmp;
    return true;
}


int main(int argc, char *argv[])
{
    map<string, string> p_val;
    get_map_value(p_val);
    map<string, string>::iterator it = p_val.begin();
    while(it != p_val.end())
    {
        printf("%s,%s\n", it->first.c_str(), it->second.c_str());
        it++;
    }

    return 0;
}
