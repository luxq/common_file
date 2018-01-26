// Last Update:2017-06-01 14:12:00
/**
 * @file coro.c
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-06-01
 */

#include <stdio.h>

typedef struct
{
    int i;
    int num;
    int state;
} task;

#define crBegin(state) \
    switch (state) { case 0:

#define crReturn(state, ret) \
        (state) = __LINE__; return (ret); case __LINE__:

#define crEnd() \
    }

int cb(task *t)
{
    crBegin(t->state);
    for (;;) {
        t->num = 1;
        for (t->i = 0; t->i < 20; t->i++) {
            crReturn(t->state, t->num);
            t->num += 1;
        }
    }
    crEnd();
}
int cb2(task *t)  
{  
    switch (t->state) {  
        case 0:  
            for (;;) {  
                t->num = 1;  
                for (t->i = 0; t->i < 20; t->i++) {  
                    t->state = __LINE__ + 2;  
                    return t->num;  
                    case __LINE__:  
                    t->num += 1;  
                }  
            }  
    }  
}  

int main()
{
    task t;
    int i;

    t.state = 0;

    for (i = 0; i < 100; i++) {
        printf("%d ", cb2(&t));
    }
    return 0;
}
