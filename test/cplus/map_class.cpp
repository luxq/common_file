// Last Update:2016-12-24 11:12:57
/**
 * @file map_class.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2016-12-05
 */
#include <stdio.h>
#include <string>
#include <map>
#include <hash_map>
#include <iostream>
using namespace std;
class person;
typedef std::map<string, person> map_person;
class person
{
    public:
        person()
        {
        }
        ~person()
        {
        }
    public:
        string name;
        string telnum;
        map_person pmap;
};


person get_person(string key)
{
    person p;
    p.name = "name_";
    p.name+=key;
    p.telnum = "telnum_";
    p.telnum += key;
    //printf("get_person/p = %p\n", &p);
    return p;
}

map_person get_map()
{
    map_person pmap;
    for (int i = 0; i < 10; i++)
    {
        person p;
        char buf[12] = {0};
        sprintf(buf, "kkk%d",i);
        string key = buf;
        p = get_person(key);
        pmap[key] = p;
    }
    printf("get_map/pmap = %p\n", &pmap);
    map_person::iterator it = pmap.begin();
    for(it;it != pmap.end(); it++)
    {
        person tmpp = it->second;
        //printf("main/second = %p\n", &(it->second));
        cout<<"key = "<<it->first<<", name = "<<tmpp.name<<", telnum = "<<tmpp.telnum<<endl;
    }
    return pmap;
}

int main(int argc, char *argv[])
{
    map_person pmap(get_map());
    printf("main/pmap = %p\n", &pmap);
    map_person::iterator it = pmap.begin();
    for(it;it != pmap.end(); it++)
    {
        person tmpp = it->second;
        //printf("main/second = %p\n", &(it->second));
        cout<<"key = "<<it->first<<", name = "<<tmpp.name<<", telnum = "<<tmpp.telnum<<endl;
    }
    __gnu_cxx::hash_map<string, string> inmap;
    __gnu_cxx::hash_map<string, string>::iterator itb = inmap.begin();
    
    
    return 0;
}
