// Last Update:2017-12-22 14:36:33
/**
 * @file a.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-12-22
 */

#include <stdio.h>
class P{
    public:
        P():m(0) {}
        int add(int a) {
            return get() +a;
        }
        int get() const {
            return m;
        }
    private:
        int m;
};

int main(int argc, char *argv[])
{
    P rw;
    int ret = rw.add(10);
    ret = rw.get();
    printf("ret = %d.\n",ret);
    const P ro;
    //ro.add(10);
    ret = ro.get();
    return 0;
}
