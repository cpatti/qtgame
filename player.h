#ifndef __PLAYER_H_
#define __PLAYER_H_

#include <qwidget.h>
#include "configuration.h"

/*
  Right now, there are only two types of players: Human and Computer
  Both the types inherit this class. 
  Every player has a configuration (config) and a color (playerCoin).
 */

class Player : public QWidget
{
  Q_OBJECT


    public:
  enum Type{HUMAN,COMPUTER};
 protected:
  Configuration * config;
  Configuration::State playerCoin;

  public slots:
    virtual void moved(int)=0;
    virtual void droppedRed(int)=0;
    virtual void droppedYellow(int)=0;
    /*
      The above slots are used to get information about the happenings on the canvas. 
      They used to update the internal state of the player(things like updating the configuration)
      and to start contemplating the next move ( in the case of machine player).
    */


 signals:
    void move(int); //Send the signal to move the coin to a particular column
    void moveBy(int); //Send the signal to move the coin by a particular number of columns
    void drop(); //Send the signal to drop the coin in the current column

 public:
    Player(QWidget * parent=0, const char * name=0,Configuration::State pCoin=Configuration::YELLOW);
    Player(const Player &);
    Player & operator=(const Player &);
};

#endif
