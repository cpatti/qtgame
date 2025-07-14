#include "configuration.h"

Configuration::Configuration():table(WIDTH,Column(HEIGHT,NONE)),columnPositions(WIDTH,0),redScore(0),yellowScore(0)
{
}

bool Configuration::canDrop(int colNo) //Is the column full?
{
  if(!checkColumnNo(colNo))
    {
      throw PositionError();
    }

  if(columnPositions[colNo] >= HEIGHT)
    return false;
  return true;
}

int Configuration::checkScore(int colNo,int rowNo,int xinc,int yinc)
{
  State color=getColor(colNo,rowNo);
  int posScore=0;
  for(int i=0;i<FULL_LINE;i++)
    {
      int found=true;
      for(int j=0;j<FULL_LINE;j++)
	{
	  int xpos=colNo+xinc*(i-j), ypos=rowNo+yinc*(i-j);
	  if(!checkColumnNo(xpos) || !checkRowNo(ypos))
	    {
	      found=false;
	      break;
	    }
	  if(getColor(xpos,ypos)!=color)
	    {
	      found=false;
	      break;
	    }
	}
      if(found==true)
	posScore++;
    }
  return posScore;
}

bool Configuration::performDrop(int colNo,State color) //Drop coin in the specified column
{
  if(canDrop(colNo)==false)
    return false;
  
  int rowNo=columnPositions[colNo];
  table[colNo][columnPositions[colNo]]=color;
  columnPositions[colNo]++;
  

  int score=0;
  score+=checkScore(colNo,rowNo,0,1);
  score+=checkScore(colNo,rowNo,1,0);
  score+=checkScore(colNo,rowNo,1,1);
  score+=checkScore(colNo,rowNo,-1,1);

  if(color==RED)
    redScore+=score;
  else if(color==YELLOW)
    yellowScore+=score;

  return true;
}

void Configuration::removeTopMost(int colNo) //Remove the topmost coin in a column
{
  if(!checkColumnNo(colNo) )
    {
      throw PositionError();
    }
  if(columnPositions[colNo]>0)
    {
      int score=0;
      int rowNo=columnPositions[colNo]-1;
      score+=checkScore(colNo,rowNo,0,1);
      score+=checkScore(colNo,rowNo,1,0);
      score+=checkScore(colNo,rowNo,1,1);
      score+=checkScore(colNo,rowNo,-1,1);

      if(table[colNo][rowNo]==RED)
	redScore-=score;
      else
	yellowScore-=score;
      table[colNo][columnPositions[colNo]-1]=Configuration::NONE;
      columnPositions[colNo]--;
    }
}

Configuration::State Configuration::getColor(int colNo,int rowNo)
{
  if(!checkColumnNo(colNo) || !checkRowNo(rowNo))
    {
      throw PositionError();
    }

  return table[colNo][rowNo];
}

int Configuration::getPosInColumn(int colNo) 

  /*
    No. of coins in a column 
    This is also the row no. 
    in the column where the next
    coin that is dropped in that column
    would go.
  */

{
  if(!checkColumnNo(colNo))
    {
      throw PositionError();
    }
  return columnPositions[colNo];
}

bool Configuration::checkColumnNo(int colNo) //Sanity check
{
  return (colNo>=0 && colNo<WIDTH);
}

bool Configuration::checkRowNo(int rowNo) //Sanity check
{
  return (rowNo>=0 && rowNo<HEIGHT);
}

int Configuration::getYellowScore()
{
  return yellowScore;
}

int Configuration::getRedScore()
{
  return redScore;
}
