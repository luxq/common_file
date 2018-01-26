// Last Update:2017-05-12 11:38:38
/**
 * @file get_meminfo.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-05-12
 */

#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;
 
std::string splitstring(std::string str, std::string split, int index)
{
    std::string::size_type pos;
    str+=split;//扩展字符串以方便操作
    int size=str.size();

    int count = 0;
    for(int i=0; i<size; i++)
    {
        pos=str.find(split,i);
        if(pos<size)
        {
            count++;
            std::string s=str.substr(i,pos-i);
            if(index == count)
                return s;
            i=pos+split.size()-1;
        }
    }
    return "";
}
void  split_str(string sign, string src_str, vector<string> &key_list)
{
    std::string strs = src_str + sign;
    size_t pos = strs.find(sign);
    size_t size = strs.size();
    while (pos != -1)
    {
        strs.trim();
        std::string dst_str = strs.substr(0,pos);
        key_list.push_back(dst_str);
        strs = strs.substr(pos+1,size);
        pos = strs.find(sign);
    }
}

int main(int argc, char *argv[])
{
    map<string,string> meminfo;

    ifstream ifstm("/proc/meminfo",ios::out|ios::binary);//打开配置文件
    if(!ifstm){
        return 1;
    }
    vector<string> v;//用来存储从文件中读取的内容
    string tmp;
    while(!ifstm.eof())
    {
        ifstm>>tmp;//一行一行的读取
        v.push_back(tmp); //将读取的信息存进vector里面 ,从尾部插入 
    }
    ifstm.close();
    vector<string>::iterator it;
    for(it = v.begin(); it != v.end(); ++it)
    {
        //调用函数将*it显示到界面
    }

}
