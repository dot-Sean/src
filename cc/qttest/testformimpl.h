#ifndef TESTFORM_IMPL_H
#define TESTFORM_IMPL_H

#include "testform.h"

class TestFormImpl : public TestForm {
    Q_OBJECT
public:
    TestFormImpl(
     QWidget* parent = 0,
     const char * name = 0,
     WFlags fl = WType_TopLevel );
    ~TestFormImpl();
public slots:
    virtual void buttonAdd_clicked();
    virtual void buttonList_clicked();
};

#endif // TESTFORM_IMPL_H
