#include <qpushbutton.h>
#include <qlabel.h>
#include "inclcd.h"
#include "gamearea.h"
#include "humanplayer.h"
#include "machineplayer.h"

GameArea::GameArea(QWidget * parent, const char * name,Player::Type yellowType,Player::Type redType): QWidget(parent, name)
{
  dCanvas=new DropCanvas(this);
  
  dCanvasView= new DropCanvasView(dCanvas,this);

  dLayout=new QGridLayout(this,2,2);

  dLayout->addWidget(dCanvasView,0,1);

  lcdLayout=new QHBoxLayout();

  dLayout->addLayout(lcdLayout,1,1);


  redLabel=new QLabel("Red",this);
  redLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
  redLabel->setPaletteForegroundColor(red);
  redLabel->setPaletteBackgroundColor(QColor(236,202,202));

  yellowLabel=new QLabel("Yellow",this);
  yellowLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
  yellowLabel->setPaletteForegroundColor(QColor(142,141,60));
  yellowLabel->setPaletteBackgroundColor(QColor(243,242,131));

  lcdLayout->addWidget(redLabel);
  lcdLayout->addWidget(redScore=new IncLCD(2,this));
  redScore->setPaletteBackgroundColor(QColor(236,202,202));

  lcdLayout->addWidget(yellowLabel);
  lcdLayout->addWidget(yellowScore=new IncLCD(2,this));
  yellowScore->setPaletteBackgroundColor(QColor(243,242,131));


  if(yellowType==Player::HUMAN)
    yellowPlayer=new HumanPlayer(this,"yp",Configuration::YELLOW);
  else
    yellowPlayer=new MachinePlayer(this,"yp",Configuration::YELLOW);

  if(redType==Player::HUMAN)
    redPlayer=new HumanPlayer(this,"rp",Configuration::RED);
  else
    redPlayer=new MachinePlayer(this,"rp",Configuration::RED);


  makeRedPlayerConnections();
  makeYellowPlayerConnections();

  connect(dCanvas,SIGNAL(droppedRed(int)),this,SLOT(changeFocus()));
  connect(dCanvas,SIGNAL(droppedYellow(int)),this,SLOT(changeFocus()));

  connect(dCanvas,SIGNAL(yellowScored(int)),yellowScore,SLOT(increment(int)));
  connect(dCanvas,SIGNAL(redScored(int)),redScore,SLOT(increment(int)));


  setFocusProxy(yellowPlayer);
  redPlayer->hide();
  yellowPlayer->hide();

  if(yellowType==Player::COMPUTER)
    dynamic_cast<MachinePlayer *>(yellowPlayer)->performDrop();

}

GameArea::~GameArea()
{

}

void GameArea::makeYellowPlayerConnections()  //signal-slot connections in which 
                                              //yellow player is involved
{
  connect(yellowPlayer,SIGNAL(moveBy(int)),dCanvas,SLOT(moveBy(int)));
  connect(yellowPlayer,SIGNAL(move(int)),dCanvas,SLOT(move(int)));
  connect(yellowPlayer,SIGNAL(drop()),dCanvas,SLOT(performDrop()));

  connect(dCanvas,SIGNAL(movedYellow(int)),yellowPlayer,SLOT(moved(int)));

  connect(dCanvas,SIGNAL(droppedYellow(int)),yellowPlayer,SLOT(droppedYellow(int)));
  connect(dCanvas,SIGNAL(droppedRed(int)),yellowPlayer,SLOT(droppedRed(int)));
}

void GameArea::makeRedPlayerConnections()    //signal-slot connections in which 
                                             //red player is involved
{

  connect(redPlayer,SIGNAL(moveBy(int)),dCanvas,SLOT(moveBy(int)));
  connect(redPlayer,SIGNAL(move(int)),dCanvas,SLOT(move(int)));
  connect(redPlayer,SIGNAL(drop()),dCanvas,SLOT(performDrop()));

  connect(dCanvas,SIGNAL(movedRed(int)),redPlayer,SLOT(moved(int)));

  connect(dCanvas,SIGNAL(droppedYellow(int)),redPlayer,SLOT(droppedYellow(int)));
  connect(dCanvas,SIGNAL(droppedRed(int)),redPlayer,SLOT(droppedRed(int)));
}

void GameArea::changeFocus()
{
  if(focusProxy()==redPlayer)
    {
      setFocusProxy(yellowPlayer);
      yellowPlayer->setFocus();
    }
  else
    {
      setFocusProxy(redPlayer);
      redPlayer->setFocus();
    }
}

void GameArea::redHuman()  //Make the red player human
{
  if(dynamic_cast<HumanPlayer *>(redPlayer)) //Do nothing if already human 
    return;
  Player * hp=new HumanPlayer(this,0,Configuration::RED);
  *hp=*(dynamic_cast<Player *>(redPlayer));
  delete redPlayer;
  redPlayer=hp;
  makeRedPlayerConnections();
  if(dCanvas->getCurrentCoin()==Configuration::RED)
    {
      setFocusProxy(redPlayer);
      redPlayer->setFocus();
    }
}

void GameArea::redComputer() //Make the red player a computer player
{
 if(dynamic_cast<MachinePlayer *>(redPlayer))  //Do nothing if already a computer player
    return;
  Player * mp=new MachinePlayer(this,0,Configuration::RED);
  *mp=*(dynamic_cast<Player *>(redPlayer));
  delete redPlayer;
  redPlayer=mp;
  makeRedPlayerConnections();
  if(dCanvas->getCurrentCoin()==Configuration::RED)
    {
      setFocusProxy(redPlayer);
      redPlayer->setFocus();
      dynamic_cast<MachinePlayer *>(mp)->performDrop();
    }
}

void GameArea::yellowHuman()  //Make the yellow player human
{
  if(dynamic_cast<HumanPlayer *>(yellowPlayer))  //Do nothing if already human
    return;

  Player * tp=new HumanPlayer(this,0,Configuration::YELLOW);
  *tp=*(dynamic_cast<Player *>(yellowPlayer));
  delete yellowPlayer;
  yellowPlayer=tp;
  makeYellowPlayerConnections();
  if(dCanvas->getCurrentCoin()==Configuration::YELLOW)
    {
      setFocusProxy(yellowPlayer);
      yellowPlayer->setFocus();
    }
}

void GameArea::yellowComputer() //Make the yellow player a computer player
{
 if(dynamic_cast<MachinePlayer *>(yellowPlayer))  //Do nothing if already a computer player
    return;

  Player * mp=new MachinePlayer(this,0,Configuration::YELLOW);
  *mp=*(dynamic_cast<Player *>(yellowPlayer));
  delete yellowPlayer;
  yellowPlayer=mp;
  makeYellowPlayerConnections();
  if(dCanvas->getCurrentCoin()==Configuration::YELLOW)
    {
      setFocusProxy(yellowPlayer);
      yellowPlayer->setFocus();
      dynamic_cast<MachinePlayer *>(mp)->performDrop();
    }
}
