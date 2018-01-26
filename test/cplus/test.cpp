// Last Update:2016-11-12 11:28:07
/**
 * @file test.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2016-11-12
 */

#include "virbaseClass.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <dlfcn.h>
#include <iostream>
using namespace std;
typedef PB_Base* (*pAttachFunc)();

int main(int argc, char *argv[])
{

    void * handle = dlopen("./libcanMsg.so",RTLD_NOW);
    if(handle==NULL)
    {
        printf("open %s error \n%s\n", "./libcanMsg.so", dlerror());
        exit(1);
    }
    pAttachFunc attach = NULL;
    attach = (pAttachFunc)dlsym(handle,"attach");
    if(attach == NULL)
    {
        printf("open attach  error %s\n" , dlerror());
        dlclose(handle);
        exit(1);
    }
    string s;
    string name = "fdname";
    PB_Base *pb = attach();
    pb->pb_getFieldValue(name, (void*)&s);
    cout<<"get string = "<< s<<endl;



    return 0;
}
