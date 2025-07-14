#include "inclcd.h"

IncLCD::IncLCD(int numOfDigits,QWidget * parent):QLCDNumber(numOfDigits,parent)
{
  value=0;
}

void IncLCD::increment(int inc)
{
  value=value+inc;
  QLCDNumber::display(value);
}

void IncLCD::decrement(int dec)
{
  value=value-dec;
  QLCDNumber::display(value);
}
