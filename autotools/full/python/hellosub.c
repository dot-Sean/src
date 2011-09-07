#include <hello.h>

#include <Python.h>

static PyObject *
hellosub (
  PyObject * self,
  PyObject * args ) {
    hello();
    return (Py_BuildValue(""));
}

static PyMethodDef hellosubMethods[] = {
    { "hellosub", (PyCFunction) hellosub, METH_VARARGS, NULL },
    { NULL, NULL, NULL, NULL }
};

void
inithellosub () {
    Py_InitModule("hellosub", hellosubMethods);
}
