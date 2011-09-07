#include <stdio.h>
#include <Python.h>

int
main (
  int argc,
  char * * argv ) {
  PyObject * pobj;
    pobj = Py_None;
    Py_Initialize();
    PyRun_SimpleString("print 'hoge';");
    Py_Finalize();
    return (0);
}
