#ifndef __CONFIGURATION_H_
#define __CONFIGURATION_H_

#include <qvaluevector.h>

class Configuration
{
 public:
  enum State {YELLOW, RED, NONE}; 

  /* A slot in the table can either be occupied by a yellow coin or a red coin or it 
   can be empty*/
  
  static const int HEIGHT=6;
  static const int WIDTH=7;

  static const int FULL_LINE=4;

  typedef QValueVector<State> Column;
  
  class PositionError {};

  class GravityError {};

 private:

  QValueVector<Column> table; // The table comprises of many columns
  QValueVector<int> columnPositions; // This vector stores the number of coins 
                                     // present in each of the columns

  int redScore;
  int yellowScore;

  bool checkColumnNo(int colNo);
  bool checkRowNo(int rowNo);

  int checkScore(int colNo,int rowNo,int xinc,int yinc);
  
 public:
  Configuration();
  bool canDrop(int colNo);
  bool performDrop(int colNo, State color);
  State getColor(int colNo,int rowNo);
  void removeTopMost(int colNo);

  int getPosInColumn(int colNo);

  int getYellowScore();
  int getRedScore();

};

#endif
