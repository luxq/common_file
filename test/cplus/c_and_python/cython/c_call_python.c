// Last Update:2017-04-26 16:23:27
/**
 * @file c_call_python.c
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-04-26
 */
#include <Python.h>
#include "great_module.h"
void test_great_function()
{
    PyObject *tuple;
    printf("%s\n", PyString_AsString(
                great_function(
                    PyString_FromString("Hello"),
                    PyInt_FromLong(1)
                    )
                ));
    tuple = Py_BuildValue("(iis)", 1, 2, "three");
    printf("%d\n", PyInt_AsLong(
                great_function(
                    tuple,
                    PyInt_FromLong(1)
                    )
                ));
    printf("%s\n", PyString_AsString(
                great_function(
                    tuple,
                    PyInt_FromLong(2)
                    )
                ));
}
void test_great_function_c()
{
    char ch = (char)great_function_c("luxq", 0);
    printf("%c\n", ch);
}
int main(int argc, char *argv[])
{
    Py_Initialize();
    initgreat_module();

    test_great_function();
    test_great_function_c();

    Py_Finalize();
    return 0;
}
