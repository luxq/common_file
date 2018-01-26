// Last Update:2016-11-07 16:57:52
/**
 * @file stranssign.c
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2016-11-07
 */

#include <string>
#include <iostream>
using namespace std;
string strassigntoc(string& str ,int n , char  c)
{
    int i = 0; 
    string value ="";
    if(n > str.length())
    {
        return value;
    }
    while(str[n+i] != 0x0 && str[n+i] != c)
    {
        value += str[n+i];
        i++;
    }
    if(str[n+i] == 0x0) 
    {
        str = "";
    }
    else 
    {
        str.assign(str,n + i +1 , str.length()) ;
    }
    return value;
}

int main(int argc, char *argv[])
{
    string str="abcdefghijkmln";
    char ch = 'm';
    cout<<"str = "<<str<<endl;
    string ret = strassigntoc(&str, 5, ch);
    cout<<"ret = "<<ret<<endl;
    cout<<"str = "<<str<<endl;
    return 0;
}
