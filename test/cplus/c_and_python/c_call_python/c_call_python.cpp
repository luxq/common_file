// Last Update:2017-04-26 10:58:48
/**
 * @file c_call_python.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-04-26
 */

#include <Python.h>

int call_great_function(int a)
{
    int res;
    PyObject *pModule, *pFunc;
    PyObject *pArgs, *pValue;
    //import 
    pModule = PyImport_Import(PyString_FromString("great_module"));

    //great_module.great_function
    pFunc = PyObject_GetAttrString(pModule, "great_function");

    //build args
    pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, PyInt_FromLong(a));

    //call 
    pValue = PyObject_CallObject(pFunc, pArgs);
    res = PyInt_AsLong(pValue);
    return res;
}

int main(int argc, char *argv[])
{
    Py_SetProgramName(argv[0]);
    Py_Initialize();
    PyRun_SimpleString("print 'Hello Python!'\n");
    printf("great_function result = %d\n",call_great_function(2));
    Py_Finalize();
    return 0;
}
