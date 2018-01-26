// Last Update:2017-04-05 11:00:01
/**
 * @file clear_file.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-04-05
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>


int main(int argc, char *argv[])
{
    std::string filename = "";
    if(argc == 2)
    {
        filename = argv[1];
    }
    FILE *fp = fopen(filename.c_str(), "w");
    if(fp != NULL)
    {
        fclose(fp);
        printf("clear file finished.\n");
    }
    else
    {
        printf("open file %s failed.\n", filename.c_str());
    }
    return 0;
}
