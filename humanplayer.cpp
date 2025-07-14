#include "humanplayer.h"

HumanPlayer::HumanPlayer(QWidget * parent, const char * name, Configuration::State pCoin):Player(parent, name,pCoin)
{
  setFocusPolicy(ClickFocus);
}

void HumanPlayer::keyPressEvent(QKeyEvent * e) //A human player uses the keyboard
                                               //to play
{
  switch(e->key())
    {
      
    case Key_Right:
      emit moveBy(1);
      break;

    case Key_Left:
      emit moveBy(-1);
      break;

    case Key_Down:
      emit drop();
      break;
      
    default:
      e->ignore();
    }

}

void HumanPlayer::moved(int)
{
}

void HumanPlayer::droppedRed(int colNo)
{
  config->performDrop(colNo,Configuration::RED);
}

void HumanPlayer::droppedYellow(int colNo)
{
  config->performDrop(colNo,Configuration::YELLOW);
}
