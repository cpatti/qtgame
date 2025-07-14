#ifndef __HUMAN_PLAYER_H_
#define __HUMAN_PLAYER_H_

#include "player.h"

class HumanPlayer : public Player
{
 public:
  HumanPlayer(QWidget * parent=0, const char * name=0,Configuration::State pCoin=Configuration::YELLOW);

 protected:
  void keyPressEvent(QKeyEvent * e);
  public slots:
    void moved(int);
    void droppedRed(int);
    void droppedYellow(int);

};

#endif
