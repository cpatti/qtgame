#include <qmenubar.h>
#include <qaction.h>
#include <qmessagebox.h>
#include "dropmainwindow.h"

DropMainWindow::DropMainWindow(QWidget * parent, const char * name):QMainWindow(parent,name),gameArea(new GameArea(this,0,Player::HUMAN,Player::COMPUTER))
{
  setCaption("Drop");
  setCentralWidget(gameArea);
  setFocusProxy(gameArea);

  //Set up all the menus

  menuBar=new QMenuBar(this);
  p1=new QPopupMenu(this);
  helpMenu=new QPopupMenu(this);
  playerMenu=new QPopupMenu(this);
  redMenu=new QPopupMenu(this);
  yellowMenu=new QPopupMenu(this);

  newGameAction=new QAction("New Game",QKeySequence(),this);
  newGameAction->addTo(p1);
  connect(newGameAction,SIGNAL(activated()),this,SLOT(newGame()));

  menuBar->insertItem("Game",p1);

  redGroup=new QActionGroup(this);
  redGroup->setExclusive(TRUE); //Only one action in redGroup can be chosen at a time

  connect(redGroup,SIGNAL(selected(QAction *)),this,SLOT(redGroupSlot(QAction *)));

  yellowGroup=new QActionGroup(this);
  yellowGroup->setExclusive(TRUE); //Only one action in yellowGroup can be chosen at a time

  connect(yellowGroup,SIGNAL(selected(QAction *)),this,SLOT(yellowGroupSlot(QAction *)));

  redHuman=new QAction("Human",QKeySequence(),redGroup);
  redHuman->addTo(redMenu);
  redHuman->setToggleAction(TRUE);
  redComputer=new QAction("Computer",QKeySequence(),redGroup);
  redComputer->addTo(redMenu);
  redComputer->setToggleAction(TRUE);



  yellowHuman=new QAction("Human",QKeySequence(),yellowGroup);
  yellowHuman->addTo(yellowMenu);
  yellowHuman->setToggleAction(TRUE);
  yellowComputer=new QAction("Computer",QKeySequence(),yellowGroup);
  yellowComputer->addTo(yellowMenu);
  yellowComputer->setToggleAction(TRUE);

  yellowHuman->setOn(TRUE);
  redComputer->setOn(TRUE);

  menuBar->insertItem("Players",playerMenu);
  playerMenu->insertItem("Red",redMenu);

  playerMenu->insertItem("Yellow",yellowMenu);
  yellowMenu->setCheckable(true);

  menuBar->insertItem("Help",helpMenu);
  helpMenu->insertItem("Instructions");
  helpMenu->insertSeparator();
  aboutAction=new QAction("About",QKeySequence(),this);
  aboutAction->addTo(helpMenu);
  connect(aboutAction,SIGNAL(activated()),this,SLOT(about()));

}

void DropMainWindow::newGame()
{
  delete gameArea;
  Player::Type yellowType, redType;
  if(yellowHuman->isOn())
    yellowType=Player::HUMAN;
  else
    yellowType=Player::COMPUTER;

  if(redHuman->isOn())
    redType=Player::HUMAN;
  else
    redType=Player::COMPUTER;

  gameArea=new GameArea(this,0,yellowType,redType);
  setCentralWidget(gameArea);
  setFocusProxy(gameArea);
  gameArea->show();
  gameArea->setFocus();
}

void DropMainWindow::about()
{
  QMessageBox::information(this,"About Drop","Drop\nA Game Developed by Chaitanya Reddy Patti (reddychaitanya@gmail.com)",QMessageBox::Ok);
}

void DropMainWindow::redGroupSlot(QAction * act)
{
  if(act==redHuman)
    gameArea->redHuman();

  else if (act==redComputer)
    gameArea->redComputer();

}

void DropMainWindow::yellowGroupSlot(QAction * act)
{
  if (act==yellowHuman)
    gameArea->yellowHuman();

  else if (act==yellowComputer)
    gameArea->yellowComputer();
}
