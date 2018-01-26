// Last Update:2017-12-20 11:53:49
/**
 * @file test_template.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-12-20
 */
template <class Type> Type bar(Type a, Type b)
{
    return a > b ? a : b;

}

template <class Type> Type bar(Type a, Type b)
{
    return a > b ? a : b;

}
template <class T1, class T2> void bar(T1, T2)
{
    ;
}
template <class C1, typename C2> void bar(C1, C2)
{
    ;
}
