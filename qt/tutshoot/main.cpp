#include <qapplication.h>

#include "gamebrd.h"

int
main (
  int argc,
  char * * argv ) {
    QApplication::setColorSpec(QApplication::CustomColor);
  QApplication app(argc, argv);
  GameBoard gb;
    gb.setGeometry(100, 100, 500, 355);
    app.setMainWidget(& gb);
    gb.show();
    return (app.exec());
}
