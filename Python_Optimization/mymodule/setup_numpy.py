# setup.py
from setuptools import setup, Extension
import numpy

module = Extension("my_numpy_module", sources=["my_numpy_module.c"],include_dirs=[numpy.get_include()])

setup(
    name="my_module",
    version="1.0",
    description="Python interface for calculating array sum in C",
    ext_modules=[module],
)
