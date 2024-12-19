# setup.py
from setuptools import setup
from Cython.Build import cythonize
import numpy as np

setup(
    ext_modules=cythonize("cython_square.pyx"),
    include_dirs=[np.get_include()]  # numpy 헤더 파일 경로 포함
)