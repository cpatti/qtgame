#ifndef __DROPCANVAS_H_
#define __DROPCANVAS_H_

#include <qcanvas.h>
#include "configuration.h"

// The canvas on which all the drawing is done.

class DropCanvas : public QCanvas
{
  Q_OBJECT

 public:

  DropCanvas(QObject * parent=0, const char * name =0);
  void advance();
  Configuration::State getCurrentCoin();

 public slots:

   bool performDrop();          // These slots are used to take `orders'
 bool moveBy(int noOfColumns);  // from other objects to move the coin 
 bool move(int columnNo);       // or drop the coin in a column

 signals:
 void droppedYellow(int);  //These signals are used 
 void droppedRed(int);     //to indicate happenings on the canvas to other
 void movedYellow(int);    //objects.
 void movedRed(int);
 void yellowScored(int);
 void redScored(int);
 private:
  void drawTable();

  QPixmap * tablePixMap;
  QBitmap * tableBitMap;
  QCanvasSprite * tableSprite;
  QCanvasEllipse * dropCoin;
  QCanvasRectangle * bottomRect;
  Configuration * config;

  double columnWidthRatio;
  double rowHeightRatio;
  double topMarginRatio;
  double leftMarginRatio;
  double coinWidthRatio;

  int currentColumn;
  int targetColumn;

  bool movingHorizontal;

  Configuration::State currentCoin;

  QColor yellowColor;
  QColor redColor;

  int scoreChange;
};

#endif
