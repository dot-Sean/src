#include "testformimpl.h"

#include <qiconview.h>
#include <iostream>

using namespace std;

TestFormImpl::TestFormImpl (
  QWidget * parent,
  const char * name,
  WFlags fl ) :
  TestForm(parent, name, fl) {
    ;
}

TestFormImpl::~TestFormImpl () {
    ;
}

void
TestFormImpl::buttonAdd_clicked () {
    (void) new QIconViewItem(this->iconViewMain, "hoge");
}

void
TestFormImpl::buttonList_clicked () {
  QIconViewItem * pitem;
    for (
     pitem = this->iconViewMain->firstItem();
     pitem;
     pitem = pitem->nextItem() ) {
        cerr << pitem->text() << endl;
    }               
}
