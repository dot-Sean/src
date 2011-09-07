#include <mylib.h>

#include <Python.h>

static PyObject *
mylibHello (
  PyObject * self,
  PyObject * args ) {
    myfunc();
    return (Py_BuildValue(""));
}

static PyMethodDef mylibMethods[] = {
    { "hello", (PyCFunction) mylibHello, METH_VARARGS, NULL },
    { NULL, NULL, NULL, NULL }
};

void
initmylib () {
    Py_InitModule("mylib", mylibMethods);
}
