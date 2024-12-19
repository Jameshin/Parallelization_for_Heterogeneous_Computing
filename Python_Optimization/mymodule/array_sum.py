import my_module
import time

# 테스트할 배열 생성
data = [float(i) for i in range(1000000)]

# Python 내장 sum 함수 시간 측정
start_time = time.time()
python_sum = sum(data)
print("Python sum:", python_sum)
print("Python sum time:", time.time() - start_time)

# C 모듈의 array_sum 함수 시간 측정
start_time = time.time()
c_sum = my_module.array_sum(data)
print("C array_sum:", c_sum)
print("C array_sum time:", time.time() - start_time)
