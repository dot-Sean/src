#include <stdio.h>

#include <Python.h>

#include <string.h>

typedef struct {
    PyObject_HEAD;
    char * string;
} MyPyObject;

/* ---------------------------------------------------------------- */
/* class methods for users */

static PyObject *
doSet (
  MyPyObject * self,
  PyObject * args ) {
  char * name;
    if (! (PyArg_ParseTuple(args, "s", & name))) {
        return ((void *) 0);
    }
    free((void *) self->string);
    self->string = (char *) malloc(sizeof (char) * (strlen(name) + 1));
    strcpy(self->string, name);
    return (PyString_FromString(name));
}

static PyObject *
doGet (
  PyObject * self,
  PyObject * args ) {
    return (PyString_FromString(((MyPyObject *) self)->string));
}

static PyObject *
doGetCptr (
  PyObject * self,
  PyObject * args ) {
    return (PyString_FromString(((MyPyObject *) self)->string));
}

/* ---------------------------------------------------------------- */
/* class methods for python system */

static PyMethodDef classMethods[] = {
    { "set",  (PyCFunction) doSet,  1, "set()"  },
    { "get",  (PyCFunction) doGet,  1, "get()"  },
    { "cptr", (PyCFunction) doGetCptr, 1, "cptr()" },
    { NULL, NULL }
};

static PyObject *
MyPyObject_getattr (
  PyObject * self,
  char * name ) {
    return Py_FindMethod(classMethods, (PyObject *) self, name);
}

static void
MyPyObject_dealloc (
  MyPyObject * self ) {
    if (self->string) {
        free(self->string);
    }
    // Do not free self
    //PyMem_DEL(self);
}

static int
MyPyObject_print (
  MyPyObject * self,
  FILE * pfile,
  int flags ) {
    fprintf(pfile, "MyPyObject: %s", self->string);
    return (0);
}

/* ---------------------------------------------------------------- */
/* class object */

/* /usr/include/python1.5/object.h(/typedef struct _typeobject/) */
static PyTypeObject MyPyObjectClass = {
    PyObject_HEAD_INIT(NULL)
    0,                                /*ob_size*/
    "MyPyObject",                     /*tp_name*/
    sizeof (MyPyObject),              /*tp_basicsize*/
    0,                                /*tp_itemsize*/
    (destructor) MyPyObject_dealloc,  /*tp_dealloc*/
    (printfunc) MyPyObject_print,     /*tp_print*/
    (getattrfunc) MyPyObject_getattr, /*tp_getattr*/
    (setattrfunc) 0,                  /*tp_setattr*/
    (cmpfunc) 0,                      /*tp_compare*/
    (reprfunc) 0,                     /*tp_repr*/
    0,                                /*tp_as_number*/
    0,                                /*tp_as_sequence*/
    0,                                /*tp_as_mapping*/
    (hashfunc) 0,                     /*tp_hash*/
    (ternaryfunc) 0,                  /*tp_call*/
    (reprfunc) 0,                     /*tp_str*/
    0L,
    0L,
    0L,
    0L,
    "MyPyObject document"
};

/* ---------------------------------------------------------------- */
/* constructor */

static PyObject *
createMyPyObject (
  PyObject * self_dummy,
  PyObject * args ) {
  MyPyObject * self;
  char * string;
    self = PyObject_NEW(MyPyObject, & MyPyObjectClass);
    if (! self) {
        return (NULL);
    }
    if (! (PyArg_ParseTuple(args, "|s", & string))) {
        return ((void *) 0);
    }
    self->string = strdup(string);
    return ((PyObject *) self);
}

/* ---------------------------------------------------------------- */

static PyMethodDef moduleMethods[] = {
    { "MyPyObject", (PyCFunction) createMyPyObject, METH_VARARGS, NULL },
    { NULL, NULL }
};

void
initmypyobject () {
  PyObject * module;
  PyObject * dict;
    module = Py_InitModule("mypyobject", moduleMethods);
    dict = PyModule_GetDict(module);
    PyDict_SetItemString(dict, "__version__", PyString_FromString("0.9"));
    fprintf(stderr, "initialized\n");
}
