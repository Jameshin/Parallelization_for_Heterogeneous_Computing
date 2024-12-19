# setup.py
from setuptools import setup, Extension

module = Extension("my_module_numpy", sources=["my_module_numpy.c"])

setup(
    name="my_module",
    version="1.0",
    description="Python interface for calculating array sum in C",
    ext_modules=[module],
)
