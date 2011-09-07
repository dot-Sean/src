// file:///usr/lib/qt3/doc/html/index.html

#include <iostream>
#include <qapplication.h>
#include <qmessagebox.h>
#include <qstring.h>
#include <qregexp.h>

#include "testformimpl.h"

using namespace std;

int
main (
  int argc,
  char * * argv ) {
  QApplication app(argc, argv);
  QString str("abc 123 xyz");
  QRegExp re("[0-9]+");
    cerr << QString().sprintf("\"%1\" is at %2 of \"%3\"")
     .arg(re.pattern())
     .arg(str.find(re))
     .arg(str) << endl;
  QStringList list = QStringList::split(re, str);
  QStringList::Iterator it;
    for (it = list.begin(); it != list.end(); it ++) {
        cerr << QString().sprintf("d: \"%1\"").arg(* it) << endl;
    }
#if 0
  int rc;
    switch ((rc = QMessageBox::information(NULL /* parent */, "caption",
     "text", QMessageBox::Ok, QMessageBox::Cancel ))) {
        case (QMessageBox::Ok): {
            cerr << "QMessageBox::Ok" << endl;
            break;
        }
        case (QMessageBox::Cancel): {
            cerr << "QMessageBox::Cancel" << endl;
            break;
        }
        default: {
            cerr << "Other: " << rc << endl;
        }
    }
#endif
  TestFormImpl testformimpl;
    app.setMainWidget(& testformimpl);
    testformimpl.show();
    return (app.exec());
}
