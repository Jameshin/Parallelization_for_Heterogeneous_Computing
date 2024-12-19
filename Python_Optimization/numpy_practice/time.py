import numpy as np
from cython_square import square_elements  # 컴파일된 Cython 모듈 가져오기
import time

# 1. 예제 배열 생성
arr = np.random.rand(1000000)  # 100만 개의 요소를 가진 배열 생성

# 2. Python에서 제곱 계산 시간 측정
start_time = time.time()
arr **= 2
end_time = time.time()
print("Numpy only:", end_time - start_time, "seconds")

# 3. Cython 함수로 제곱 계산 시간 측정
arr = np.random.rand(1000000)  # 배열을 다시 초기화
start_time = time.time()
square_elements(arr)
end_time = time.time()
print("Cython with Numpy:", end_time - start_time, "seconds")