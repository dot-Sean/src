#include <qapplication.h>
#include <qpushbutton.h>
#include <qfont.h>
#include <qvbox.h>

class MyWidget:public QWidget {
public:
    MyWidget(QWidget * parent = (QWidget *) 0,
     const char * name = (const char *) 0 );
};

MyWidget::MyWidget(
  QWidget * parent,
  const char * name ):
    QWidget(parent, name) {
    setMinimumSize(200, 120);
    setMaximumSize(200, 120);
  QPushButton * pbtnQuit = new QPushButton("Quit", this, "quit");
    pbtnQuit->setGeometry(62, 40, 75, 30);
    pbtnQuit->setFont(QFont("Times", 18, QFont::Bold));
    connect(pbtnQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

int
main (
  int argc,
  char * * argv ) {
  QApplication app(argc, argv);
  QVBox vbox;
    vbox.resize(600, 90);
    vbox.show();
  QPushButton btnHello( "Hello, World!", & vbox, "hoge");
    btnHello.setFont(QFont("CourierNew", 24, QFont::Bold));
    QObject::connect(& btnHello, SIGNAL(clicked()), & app, SLOT(quit()));
    btnHello.show();
  MyWidget mywidget(& vbox, "fuga");
    mywidget.show();
    app.setMainWidget(& vbox);
    return (app.exec());
}
