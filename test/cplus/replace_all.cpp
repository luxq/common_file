// Last Update:2017-04-12 15:06:15
/**
 * @file replace_all.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-04-12
 */
#include <stdio.h>
#include <string>
#include <list>
using namespace std;

string&   replace_all(string&   str,const   string&   old_value,const   string&   new_value)   
{
    while(true)   {
        string::size_type   pos(0);
        if(   (pos=str.find(old_value))!=string::npos   )
            str.replace(pos,old_value.length(),new_value);
        else   break;
    }
    return   str;
}   

int main(int argc, char *argv[])
{
    string src = "163imapshouMicrosoft office（pptx）163imapshouMicrosoft office（pptx）163imapshouMicrosoft office（pptx）[attachment]\n\npptx附件.pptx\ndownload: http://preview.mail.163.com/xdownload?filename";
    replace_all(src, "\n","\\n");
    printf("after:%s.\n", src.c_str());
    
    return 0;
}
