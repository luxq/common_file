#great_module.pyx
cdef public great_function(a,index):
    return a[index]

cdef public char great_function_c(const char *a, int index):
    return a[index]
