#ifndef __GAMEAREA_H_
#define __GAMEAREA_H_

#include <qwidget.h>
#include <qmainwindow.h>
#include <qcanvas.h>
#include <qlabel.h>
#include <qlayout.h>
#include "inclcd.h"
#include "configuration.h" 
#include "dropcanvas.h"
#include "dropcanvasview.h"
#include "player.h"

//This widget contains the canvas, the canvasview, the players and
//the scores. All the necessary signal-slot connections are 
//made in the constructor of this widget.

class GameArea : public QWidget
{
  Q_OBJECT

  public slots:
    void changeFocus();
  void redHuman();
  void redComputer();
  void yellowHuman();
  void yellowComputer();
 
 private:

  DropCanvas * dCanvas;
  DropCanvasView * dCanvasView;
  QGridLayout * dLayout;
  QHBoxLayout * lcdLayout;

  Player * yellowPlayer;
  Player * redPlayer;

  IncLCD * redScore;
  IncLCD * yellowScore;

  QLabel * redLabel;
  QLabel * yellowLabel;

  void makeRedPlayerConnections();
  void makeYellowPlayerConnections();

 public:
  GameArea(QWidget * parent=0, const char * name=0,Player::Type yellowType=Player::HUMAN,Player::Type redType=Player::COMPUTER);
  ~GameArea();
};

#endif
