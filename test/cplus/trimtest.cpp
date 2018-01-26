// Last Update:2016-11-19 11:48:21
/**
 * @file trim.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2016-11-19
 */
#include <string>
#include <iostream>
using namespace std;

static string& trim(string &s)
{
    if (s.empty())
    {  
        return s;  
    }  
	int i = 0;
	while(i < s.size() &&
			(s[i] == ' ' || s[i] == '\t'))
	{
		s.erase(i,1);
		//i++;
        cout<<"i = "<<i<<", size() = "<<s.size()<<endl;
	}
//    s.erase(0,s.find_first_not_of(" "));  
//    s.erase(s.find_last_not_of(" ") + 1);  
    return s;  
}

#define STR ""\
    ""

int main(int argc, char *argv[])
{
    
    string str = "        ";
    str = trim(str);
    cout<<"str.length() = "<<str.length()<<endl;

    return 0;
}
