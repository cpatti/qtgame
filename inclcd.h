#ifndef __INC_LCD
#define __INC_LCD

#include <qlcdnumber.h>

/*
An LCD number display which has increment and decrement slots
*/

class IncLCD : public QLCDNumber
{
  Q_OBJECT
private:
  int value;
public slots:
  void increment(int);
  void decrement(int);
 public:
  IncLCD(int numOfDigits=2,QWidget * parent=0);
};

#endif
