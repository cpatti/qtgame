#ifndef __MACHINE_PLAYER_H_
#define __MACHINE_PLAYER_H_

#include "player.h"

class MachinePlayer : public Player
{
 public:
  MachinePlayer(QWidget * parent=0, const char * name=0,Configuration::State pCoin=Configuration::YELLOW);


 protected:
  void keyPressEvent(QKeyEvent * e);
  public slots:
    void moved(int);
  void performDrop();
    void droppedRed(int);
    void droppedYellow(int);

 private:
    int getNextDrop();

    double getLineValue(Configuration::State color,int columnNo,int xinc,int yinc);
    double choiceValue(int columnNo);

};

#endif
