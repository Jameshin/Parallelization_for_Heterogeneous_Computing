# save as cython_sum.pyx
def cython_sum(int n):
    cdef int total = 0
    cdef int i
    for i in range(n):
        total += i * i
    return total