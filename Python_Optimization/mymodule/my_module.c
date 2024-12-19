#include <Python.h>

// 배열 요소의 합을 계산하는 함수
static PyObject* array_sum(PyObject* self, PyObject* args) {
    PyObject *input_list;
    if (!PyArg_ParseTuple(args, "O", &input_list))
        return NULL;

    Py_ssize_t size = PyList_Size(input_list);
    double sum = 0.0;

    for (Py_ssize_t i = 0; i < size; i++) {
        PyObject *item = PyList_GetItem(input_list, i);
        if (PyFloat_Check(item)) {
            sum += PyFloat_AsDouble(item);
        }
    }

    return PyFloat_FromDouble(sum);
}

// 메서드 정의
static PyMethodDef MyMethods[] = {
    {"array_sum", array_sum, METH_VARARGS, "Calculate the sum of a list"},
    {NULL, NULL, 0, NULL}
};

// 모듈 정의
static struct PyModuleDef mymodule = {
    PyModuleDef_HEAD_INIT,
    "my_module",
    NULL,
    -1,
    MyMethods
};

// 모듈 초기화
PyMODINIT_FUNC PyInit_my_module(void) {
    return PyModule_Create(&mymodule);
}
