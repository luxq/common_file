// Last Update:2017-05-09 16:43:24
/**
 * @file std_string_test.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-05-09
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;
int main(int argc, char *argv[])
{
    int i = 100000;


    char p[100] = {0};
    {
        std::vector<string> str_v;
        while (i > 0)
        {
            {
                string num_str = "1";
                memset(p, 0, 100);
                sprintf(p, "%d%s", i, "pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp");
                num_str = p;
                i--;
                str_v.push_back(num_str);
            }

        }
    }
    printf("sleep\n");
    sleep(5);
    return 0;
}
