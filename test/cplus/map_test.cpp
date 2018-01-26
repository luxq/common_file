// Last Update:2016-12-24 13:48:39
/**
 * @file map_test.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2016-12-24
 */
#include <stdio.h>
#include <string.h>
#include <map>
#include <string>

#include <sys/time.h>
#include <iostream>
using namespace std;
struct timeval starttime;
struct timeval endtime;
#define PROFILE_START \
        gettimeofday(&starttime, NULL);

#define PROFILE_END \
        gettimeofday(&endtime, NULL);\
        std::cout<<"cost time = "<<(endtime.tv_sec * 1000000 + endtime.tv_usec - (starttime.tv_sec*1000000 + starttime.tv_usec))/1000 <<"ms"<<std::endl;\

struct cmp_str
{
    bool operator()(char const *a, char const *b)
    {
        return strcmp(a, b) < 0;
    }
};

struct StrCompare : public std::binary_function<const char*, const char*, bool> {
    public:
        bool operator() (const char* str1, const char* str2) const
        { return strcmp(str1, str2) < 0; }
};

int get(map<string, int> st, string s)
{
    return st[s];
}
int get_2(map<char *, int, StrCompare> st, char *p)
{
    return st[p];
}

int main(int argc, char *argv[])
{
    map<string, int> st;
    map<char *, int, StrCompare> ct;
    char buf[129] = {0};
    for(int i = 0; i<300; i++)
    {
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "%d", i);
        char *k = new char [strlen(buf)+1];
        sprintf(k, "%s", buf);
        st[buf] = i;
        ct[k] = i;
    }
    map<char *, int, StrCompare>::iterator it = ct.begin();
    int m = 0;
    while(it != ct.end())
    {
        m++;
        cout<<"m="<<m<<","<<it->first<<endl;
        it++;
    }
    cout<<"st['30'] = "<<st["30"]<<endl;
    cout<<"ct['30'] = "<<ct["30"]<<endl;
    PROFILE_START
    for(int j = 0; j < 500000; j++)
    {
        string p = "30";
        int d = get(st, p);
    }
    PROFILE_END
    PROFILE_START
    for(int l = 0; l < 500000; l++)
    {
        string p = "30";
        int d = get_2(ct, (char *)p.c_str());
    }
    PROFILE_END
    PROFILE_START
    for(int o = 0; o < 500000; o++)
    {
        char *p = "30";
        int d = get_2(ct, p);
    }
    PROFILE_END
    
    return 0;
}
