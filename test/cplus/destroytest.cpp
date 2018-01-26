// Last Update:2016-12-02 16:13:28
/**
 * @file destroytest.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2016-12-02
 */
#include <string>
#include <map>
#include <list>
#include <iostream>
using namespace std;
class A
{
    public:
        A()
        {
        }
        ~A()
        {
            cout<<"this is ~A()"<<endl;
        }
    public:
        string name;
        string type;
};
typedef std::map<string, A*> name_A_map;
class B
{
    public:
        list<A*> alist;
        name_A_map nameMap;
    public:
        B()
        {
        }
        ~B()
        {
            while(!alist.empty())
            {
                list<A*>::reference argv_ptr = alist.back();
                delete argv_ptr;
                alist.pop_back();
            }

            name_A_map::iterator it = nameMap.begin();
            for(;it != nameMap.end(); it++)
            {
                //cout<<"name :"<<a->name<<",type:"<<a->type<<endl;
                delete it->second;
                //nameMap.erase(it);

            }
            nameMap.clear();
        }
};

int main(int argc, char *argv[])
{
    B* b = new B();
    A *a = new A();
    a->name = "name";
    a->type = "type";
    A *a1 = new A();
    a1->name = "name1";
    a1->type = "type1";
    A *a2 = new A();
    a2->name = "name2";
    a2->type = "type2";
    b->alist.push_back(a);
    A *a3 = new A();
    a3->name = "name3";
    a3->type = "type3";

    b->nameMap["a1"] = a1;
    b->nameMap["a2"] = a2;
    b->nameMap["a3"] = a3;
    delete b;
    return 0;
}
