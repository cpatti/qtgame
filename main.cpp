#include <qapplication.h>
#include <qmainwindow.h>
#include <qmenubar.h>
#include "dropmainwindow.h"

int main(int argc, char * argv[])
{
  QApplication a(argc,argv);

  DropMainWindow * mw=new DropMainWindow();

  a.setMainWidget(mw);

  mw->show();

  return a.exec();
}
