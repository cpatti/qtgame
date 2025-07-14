#include <qmainwindow.h>
#include <qaction.h>
#include "gamearea.h"

/*

The main game window
-------------------- 

Contains all the menus and actions.
This will have the main game area (which comprises of the canvas and scores) 
as the central widget.

*/

class DropMainWindow : public QMainWindow
{
  Q_OBJECT

    QAction * newGameAction, * redHuman, * redComputer, * yellowHuman , *yellowComputer, *aboutAction;
  QActionGroup * redGroup, * yellowGroup;
  GameArea * gameArea;
  QMenuBar * menuBar;
  QPopupMenu *p1,*helpMenu, *playerMenu, *redMenu, *yellowMenu;

 public:
  DropMainWindow(QWidget * parent=0, const char * name=0);

 public slots:
    void newGame();
 void about();
 void redGroupSlot(QAction *);
 void yellowGroupSlot(QAction *);
};
