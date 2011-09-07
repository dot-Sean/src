#include "gamebrd.h"

#include <qfont.h>
#include <qapplication.h>
#include <qlabel.h>
#include <qaccel.h>
#include <qpushbutton.h>
#include <qlcdnumber.h>
#include <qlayout.h>
#include <qvbox.h>

#include "lcdrange.h"
#include "cannon.h"

GameBoard::GameBoard (
  QWidget * parent,
  const char * name ):QWidget(parent, name) {
  QPushButton * btnQuit = new QPushButton("&Quit", this, "quit");
    btnQuit->setFont(QFont("Times", 18, QFont::Bold));
    connect(btnQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
  LCDRange * lcdAngle = new LCDRange("ANGLE", this, "angle");
    lcdAngle->setRange(5, 70);
  LCDRange * lcdForce  = new LCDRange("FORCE", this, "force");
    lcdForce->setRange(10, 50);
  QVBox * vbox = new QVBox(this, "cannonFrame");
    vbox->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);
    cannonField = new CannonField(vbox, "cannonField");
    connect(lcdAngle, SIGNAL(valueChanged(int)),
     cannonField, SLOT(setAngle(int)) );
    connect(cannonField, SIGNAL(angleChanged(int)),
     lcdAngle, SLOT(setValue(int)) );
    connect(lcdForce, SIGNAL(valueChanged(int)),
     cannonField, SLOT(setForce(int)) );
    connect(cannonField, SIGNAL(forceChanged(int)),
     lcdForce, SLOT(setValue(int)) );
    connect(cannonField, SIGNAL(hit()), this, SLOT(hit()));
    connect(cannonField, SIGNAL(missed()),
     this, SLOT(missed()) );
  QPushButton * btnShoot = new QPushButton("&Shoot", this, "shoot");
    btnShoot->setFont(QFont("Times", 18, QFont::Bold));
    connect(btnShoot, SIGNAL(clicked()), SLOT(fire()));
  QPushButton *restart = new QPushButton("&New Game", this, "newgame");
    restart->setFont(QFont("Times", 18, QFont::Bold));
    connect(restart, SIGNAL(clicked()), this, SLOT(newGame()));
    lcdHits = new QLCDNumber(2, this, "hits");
    shotsLeft = new QLCDNumber(2, this, "shotsleft");
  QLabel * hitsL = new QLabel("HITS", this, "hitsLabel");
  QLabel * shotsLeftL = new QLabel("SHOTS LEFT", this, "shotsleftLabel");
  QAccel * accel = new QAccel(this);
    accel->connectItem(accel->insertItem(Key_Enter), this, SLOT(fire()));
    accel->connectItem(accel->insertItem(Key_Return), this, SLOT(fire()));
    accel->connectItem(accel->insertItem(CTRL + Key_Q), qApp, SLOT(quit()));
  QGridLayout * grid = new QGridLayout(this, 2, 2, 10);
    grid->addWidget(btnQuit, 0, 0);
    grid->addWidget(vbox, 1, 1);
    grid->setColStretch(1, 10);
  QVBoxLayout * vboxLeft = new QVBoxLayout;
    grid->addLayout(vboxLeft, 1, 0);
    vboxLeft->addWidget(lcdAngle);
    vboxLeft->addWidget(lcdForce);
  QHBoxLayout * hboxTop = new QHBoxLayout;
    grid->addLayout(hboxTop, 0, 1);
    hboxTop->addWidget(btnShoot);
    hboxTop->addWidget(lcdHits);
    hboxTop->addWidget(hitsL);
    hboxTop->addWidget(shotsLeft);
    hboxTop->addWidget(shotsLeftL);
    hboxTop->addStretch(1);
    hboxTop->addWidget(restart);
    lcdAngle->setValue(60);
    lcdForce->setValue(25);
    lcdAngle->setFocus();
    newGame();
}


void GameBoard::fire()
{
    if ( cannonField->gameOver() || cannonField->isShooting() )
        return;
    shotsLeft->display( shotsLeft->intValue() - 1 );
    cannonField->shoot();
}


void GameBoard::hit()
{
    lcdHits->display( lcdHits->intValue() + 1 );
    if ( shotsLeft->intValue() == 0 )
        cannonField->setGameOver();
    else
        cannonField->newTarget();
}


void GameBoard::missed()
{
    if ( shotsLeft->intValue() == 0 )
        cannonField->setGameOver();
}


void GameBoard::newGame()
{
    shotsLeft->display( 15 );
    lcdHits->display( 0 );
    cannonField->restartGame();
    cannonField->newTarget();
}
