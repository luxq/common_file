// Last Update:2018-01-03 10:12:14
/**
 * @file print_tree.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2018-01-03
 */
#include <stdio.h>


int main(int argc, char *argv[])
{
    int i = 0; 
    for(i=0; i < 8; i++)
    {
        if(i%2)
            printf("%d", i);
        else
            printf(" ");
    }
    printf("\n");
    for(i=0; i < 8; i++)
    {
        if(i%2)
            printf("/");
        else
            printf("\\");
    }
    printf("\n");
    for(i=0; i < 8; i++)
    {
        printf("%d", i);
    }
    printf("\n");
    return 0;
}
