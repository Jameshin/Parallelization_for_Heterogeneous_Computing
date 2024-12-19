# cython_square.pyx
import numpy as np
cimport numpy as np  # cimport로 numpy의 C 라이브러리를 사용

def square_elements(np.ndarray[np.float64_t, ndim=1] arr):
    cdef int i
    for i in range(arr.shape[0]):
        arr[i] = arr[i] ** 2