/*
 *$Id: _pygettext.c,v 1.1 2001/02/13 07:58:52 knaka Exp $
 *
 * Copyright(c) 2000 TurboLinux Koushi Takahashi <koushi@turbolinux.co.jp>
 *
 * This software may be freely redistributed under the terms of the GNU
 * public license.
 */

#include <Python.h>

#include <locale.h>
#include <libintl.h>

static PyObject * pygettext(PyObject * self, PyObject * args);
static PyObject * pybindtextdomain(PyObject * self, PyObject * args);
static PyObject * pytextdomain(PyObject * self, PyObject * args);

static PyMethodDef pygettextMethods[] = {
    { "_",              pygettext, 1 },
    { "gettext",        pygettext, 1 },
    { "bindtextdomain", pybindtextdomain, 2 },
    { "textdomain",     pytextdomain, 1 },
    { NULL, NULL }
};

static PyObject * pygettext(PyObject *self, PyObject * args) {
  char * message;
    if (! (PyArg_ParseTuple(args, "s", & message))) {
        return (NULL);
    }
    return (PyString_FromString(gettext(message)));
}

static PyObject * pybindtextdomain(PyObject *self, PyObject * args) {
  char * name;
  char * path;
    if (! (PyArg_ParseTuple(args, "ss", & name, & path))) {
        return (NULL);
    }
    return (PyString_FromString(bindtextdomain(name, path)));
}

static PyObject * pytextdomain(PyObject *self, PyObject * args) {
  char * name;
    if (! (PyArg_ParseTuple(args, "s", & name))) {
        return (NULL);
    }
    return (PyString_FromString(textdomain(name)));
}

void init_pygettext() {
  PyObject * d;
    d = Py_InitModule("_pygettext", pygettextMethods);
}
