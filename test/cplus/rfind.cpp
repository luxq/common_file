// Last Update:2017-02-23 13:19:41
/**
 * @file rfind.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-02-23
 */

#include <string>
#include <stdio.h>

int main(int argc, char *argv[])
{
    std::string str = "abckdeksdfe";
    size_t pos = str.rfind("d");
    if(pos != std::string::npos)
        printf("pos = %d.\n", (unsigned int)pos);
    std::string substr = str.substr(0,pos);
    printf("substr = %s\n",substr.c_str());
    return 0;
}
