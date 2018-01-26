// Last Update:2017-08-23 11:44:44
/**
 * @file extest1.c
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-08-23
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Python.h"

int fac(int n)
{
    if (n < 2) return (1);
    return (n)*fac(n-1);
}
static PyObject *Extend_fac(PyObject *self, PyObject *args)
{
    int res;
    int num;
    PyObject* retval;
    res = PyArg_ParseTuple(args, "i", &num);
    if (!res) {
        return NULL;
    }
    res = fac(num);
    retval = (PyObject*)Py_BuildValue("i", res);
}

char *reverse(char *s)
{
    register char t, *p = s, *q = (s + (strlen(s) - 1));
    while (p < q)
    {
        t = *p;
        *p++ = *q;
        *q-- = t;
    }
    return s;
}
static PyObject *Extend_doppel(PyObject *self, PyObject *args)
{
    char *orig_str;
    char *dup_str;
    PyObject *retval;

    if(!PyArg_ParseTuple(args, "s", &orig_str)) return NULL;
    dup_str = reverse(strdup(orig_str));
    retval = (PyObject*)Py_BuildValue("ss", orig_str, dup_str);

    free(dup_str);
    return retval;
}

static PyMethodDef
ExtestMethods[] = {
    {"fac", Extend_fac, METH_VARARGS },
    {"doppel", Extend_doppel, METH_VARARGS },
    {NULL, NULL },
};

void initExtest()
{
    Py_InitModule("Extest", ExtestMethods);
}

int main()
{
    char s[1024];
    printf("4!==%d\n", fac(4));
    printf("8!==%d\n", fac(8));
    printf("5!==%d\n", fac(5));
    strcpy(s, "abcdef");
    printf("reverse 'abcdef', we get '%s'\n", reverse(s));
    strcpy(s, "madam");
    printf("reverse 'madam', we get '%s'\n", reverse(s));
    return 0;

}
