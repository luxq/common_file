// Last Update:2016-12-21 16:31:21
/**
 * @file type.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2016-12-10
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>   // std::cout
#include <vector>
#include <list>
#include <string>     // std::string, std::stoi
using namespace std;
int func_1(void)
{
    return 0;
}
string func_2(int i)
{
    return "";
}
void func_3(vector<int> v)
{
    func_2(v[0]);

}
typedef int(*pfunc)(void);

const string ZMQ_PLUGIN_ID = "1001";
int get_id()
{
    return atoi(ZMQ_PLUGIN_ID.c_str());
}
static string format_string(string str, int len)
{
    string ret;
    char buf[128] = {0};
    char *p = (char*)"0000000000000000";
    if(str.length() < len)
    {
        sprintf(buf, "%.*s%s", len-str.length(), p, str.c_str());
        ret = string(buf);
    }
    else if(str.length() > len)
    {
        ret = str.substr(str.length() - len, len);
    }
    else
    {
        ret = str;
    }
    return ret;

}
int main ()
{
    vector<list<int> > v_list;
    list<int> i1;
    pfunc p = func_1;
    uint64_t pi = (uint64_t)func_1;
    printf("func_1 = 0x%x\n", func_1);
    printf("p = 0x%x\n", p);
    printf("pi = 0x%x\n", pi);
    printf("get_id = %d.\n", get_id());

    time_t curtime = time(NULL);
    pid_t  pid = getpid();
    string device_id = "3";
    device_id = format_string(device_id, 3);
    string location_id = "110100";
    location_id = format_string(location_id, 6);
    int data_id = 100;
    char buf[128] = {0};
    
    sprintf(buf, "%010d%s%s%06d%05d", curtime, device_id.c_str(), location_id.c_str(), pid, data_id);
    printf("buf = %s\n", buf);

    uint64_t u64 = 2345566775434332222;
    printf("u64= %d\n", u64);
    printf("u64= %ld\n", u64);
    printf("u64= %llu\n", u64);

    return 0;
}
