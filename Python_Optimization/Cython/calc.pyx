def cy_cdef_complex_calc():
    cdef unsigned long long result = 0
    cdef unsigned long long ii = 0
    for i in range(100000000):
        ii = i
        result += 2*ii + 3
    return result

def cy_complex_calc():
    result = 0
    for i in range(100000000):
        result += 2*i + 3
    return result