#include <qapplication.h>
#include <qpushbutton.h>

int 
main (
  int argc,
  char * * argv ) {
  QApplication app(argc, argv);
  QPushButton btnHello( "Hello, World!", 0);
    btnHello.resize(100, 30);
    app.setMainWidget(& btnHello);
    btnHello.show();
    return (app.exec());
}
