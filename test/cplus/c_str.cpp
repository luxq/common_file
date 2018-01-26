// Last Update:2017-10-12 10:49:44
/**
 * @file c_str.cpp
 * @brief 
 * oooooooo
 * ooo
 * @author luxueqian
 * @version 0.1.00
 * @date 2016-12-24
 */
#include <string>
#include <sys/time.h>
#include <iostream>
#include <algorithm>
struct timeval starttime;
struct timeval endtime;
#define PROFILE_START \
        gettimeofday(&starttime, NULL);

#define PROFILE_END \
        gettimeofday(&endtime, NULL);\
        std::cout<<"cost time = "<<(endtime.tv_sec * 1000000 + endtime.tv_usec - (starttime.tv_sec*1000000 + starttime.tv_usec))/1000 <<"ms"<<std::endl;\

void test_lower()
{
    std::string S = "A01001";
    std::string lower;
    lower.resize(S.size());
    transform(S.begin(), S.end(), lower.begin(), ::tolower);
}

int main(int argc, char *argv[])
{

    PROFILE_START
    for(int i = 0; i< 10000; i++)
    {
        test_lower();
    }
    PROFILE_END
    char *p_value = NULL;
    std::string empty = std::string(p_value);
    std::cout<<"empty:"<<empty<<std::endl;
    std::string str = (char*)NULL;
    if(str == "")
    {
        std::cout<<"str is empty string."<<std::endl;
    }
    else{
        std::cout<<"str is not empty string."<<std::endl;
    }
    
    return 0;
}
