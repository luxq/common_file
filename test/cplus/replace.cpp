// Last Update:2017-08-01 14:52:10
/**
 * @file replace.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-04-01
 */
#include <stdio.h>
#include <string>
#include <list>      
#include <map>       
#include <iostream>  
#include <algorithm> 
#include <functional>
#include <string.h>  
using namespace std;
string&   replace_all(string&   str,const   string&   old_value,const   string&   new_value)   
{
    while(true)   {
        string::size_type   pos(0);
        if((pos=str.find(old_value))!=string::npos)
            str.replace(pos,old_value.length(),new_value);
        else   
            break;
    }

    return   str;
}   
static void remove_all(std::string &str, char c)
{
    string::iterator new_end = remove_if(str.begin(), str.end(), bind2nd(equal_to<char>(),c));
    str.erase(new_end, str.end());
} 
void dn_tele_phone(string telephone)
{
    std::string src_phone = telephone;
    std::string result = "";
    if(src_phone.length() > -0)
    {
        //去除空格
        remove_all(src_phone, ' ');
        if(src_phone.length() < 10)
            return;
        if(src_phone.compare(0, 3, "+86") == 0)
        {
            src_phone = src_phone.substr(3,src_phone.length() - 3);
        }
        if(src_phone.length() == 10 && src_phone.compare(0,2,"10") == 0)
        {
            src_phone.insert(0,"0");
        }
        else if(src_phone.length() == 8)
        {
            src_phone.insert(0, "010");
        }
        result = src_phone;

        printf("result_phone = %s\n", result.c_str());
    }
}

int main(int argc, char *argv[])
{
    string src = "a\tb\\t";
    cout<<"src="<<src<<endl;
    replace_all(src,"\t","\\t");
    cout<<"src="<<src<<endl;
    replace_all(src,"\t","\\t");
    cout<<"src="<<src<<endl;
    dn_tele_phone("+8686887522");
    return 0;
}
