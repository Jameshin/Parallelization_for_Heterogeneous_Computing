#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <numpy/arrayobject.h>

// Numpy 배열 요소의 합을 계산하는 함수
static PyObject* array_sum(PyObject* self, PyObject* args) {
    PyArrayObject *input_array;
    if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &input_array)) {
        return NULL;
    }

    // Numpy 배열이 float64 타입인지 체크
    if (PyArray_TYPE(input_array) != NPY_FLOAT64) {
        PyErr_SetString(PyExc_TypeError, "Array must be of type float64.");
        return NULL;
    }

    double sum = 0.0;
    npy_intp size = PyArray_SIZE(input_array);
    double *data = (double*) PyArray_DATA(input_array);

    // 배열 요소 합산
    for (npy_intp i = 0; i < size; i++) {
        sum += data[i];
    }

    return PyFloat_FromDouble(sum);
}

// 메서드 정의
static PyMethodDef MyMethods[] = {
    {"array_sum", array_sum, METH_VARARGS, "Calculate the sum of a numpy array"},
    {NULL, NULL, 0, NULL}
};

// 모듈 정의
static struct PyModuleDef mymodule = {
    PyModuleDef_HEAD_INIT,
    "my_numpy_module",
    NULL,
    -1,
    MyMethods
};

// 모듈 초기화
PyMODINIT_FUNC PyInit_my_numpy_module(void) {
    import_array();  // Numpy 초기화 필수
    return PyModule_Create(&mymodule);
}
