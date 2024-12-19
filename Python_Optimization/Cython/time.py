import time
from python_sum import python_sum
from cython_sum import cython_sum 

n = 10**7

# Python 버전 측정
start = time.time()
python_sum(n)
end = time.time()
print("Python version:", end - start, "seconds")

# Cython 버전 측정
start = time.time()
cython_sum(n)
end = time.time()
print("Cython version:", end - start, "seconds")