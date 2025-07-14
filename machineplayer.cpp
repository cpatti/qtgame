#include <qvaluelist.h>
#include "machineplayer.h"

MachinePlayer::MachinePlayer(QWidget * parent, const char * name,Configuration::State pCoin):Player(parent, name,pCoin)
{
  setFocusPolicy(ClickFocus);
}

void MachinePlayer::keyPressEvent(QKeyEvent * e)
{
  e->ignore();
}

void MachinePlayer::moved(int)
{
  /* In case of a machine player,
     a move is performed => a drop
     has to be performed at the 
     destination column.
   */
  emit drop();
}

void MachinePlayer::droppedYellow(int columnNo)

  /*
    When a coin is dropped, update the internal 
    configuration appropriately and get the next 
    choice to be made in case the coin dropped is that
    of the opponent.
   */

{
  config->performDrop(columnNo,Configuration::YELLOW);
  if(playerCoin==Configuration::YELLOW)
    {

    }
  else
    {
      int choice=getNextDrop();

      emit move(choice);
    }
}

void MachinePlayer::droppedRed(int columnNo)

  /*
    When a coin is dropped, update the internal 
    configuration appropriately and get the next 
    choice to be made in case the coin dropped is that
    of the opponent.
   */

{
  config->performDrop(columnNo,Configuration::RED);
  if(playerCoin==Configuration::RED)
    {

    }
  else
    {
      int choice=getNextDrop();

      emit move(choice);
    }
}

void MachinePlayer::performDrop()
{
  int choice=getNextDrop();
  emit move(choice);
}

int MachinePlayer::getNextDrop() //Get the next best move
{
  bool found=false;
  double ret;
  int maxCol=-1;
  int searchDepth=6;
  for(int i=0;i<Configuration::WIDTH;i++)
    {
      if(config->canDrop(i))
	{
	  double cv=choiceValue(i);
	  config->performDrop(i,playerCoin);
	  QValueList<int> bestDrops;
	  for(int d=0;d<searchDepth;d++)
	    {
	      if(playerCoin==Configuration::RED)
		playerCoin=Configuration::YELLOW;
	      else
		playerCoin=Configuration::RED;
	  
	      bool nextFound=false;
	      double nextRet;
	      int nextMax;
	      for(int j=0;j<Configuration::WIDTH;j++)
		{
		  if(config->canDrop(j))
		    {
		      double nv=choiceValue(j);
		      if(nextFound==false)
			{
			  nextRet=nv;
			  nextFound=true;
			  nextMax=j;
			}
		      else if(nv>nextRet)
			{
			  nextRet=nv;
			  nextMax=j;
			}
		    }
		}
	      if(nextFound==true)
		{
		  if(d%2)
		    cv+=nextRet;
		  else
		    cv-=nextRet;
		  config->performDrop(nextMax,playerCoin);
		  bestDrops.push_front(nextMax);
		}
	    }
	  
	  for(int d=0;d<searchDepth;d++)
	    {
	      if(bestDrops.empty())
		break;

	      config->removeTopMost(bestDrops.front());
	      bestDrops.pop_front();
	    }

	  if(found==false)
	    {
	      ret=cv;
	      maxCol=i;
	      found=true;
	    }
	  else if(cv>ret)
	    {
	      ret=cv;
	      maxCol=i;
	    }
	  config->removeTopMost(i);
	}
    }

  if(found==false)
    return 0;

  return maxCol;
}

double MachinePlayer::getLineValue(Configuration::State color,int columnNo,int xinc,int yinc)
{
  int xval=columnNo;
  int yval=config->getPosInColumn(xval);
  double ret=0;
  int fullLine=4;
  for(int i=0;i<fullLine;i++)
    {

      int xpos=xval+xinc*i, ypos=yval+yinc*i;

      if((ypos >= Configuration::HEIGHT) || (ypos < 0))
	{

	  continue;
	}

      if((xpos >= Configuration::WIDTH) || (xpos < 0))
	{

	  continue;
	}


      int noneCount=0,toDoCount=0;
      bool notPresent=false;
      for(int j=0;j<fullLine;j++)
	{
	  int xposevl=xpos-j*xinc, yposevl=ypos-j*yinc;

	  
	  if((yposevl >= Configuration::HEIGHT) || (yposevl < 0))
	    {
	      notPresent=true;

	      break;
	    }


	  if((xposevl >= Configuration::WIDTH) || (xposevl < 0))
	    {
	      notPresent=true;

	      break;
	    }


	  Configuration::State posColor=config->getColor(xposevl,yposevl);

	  if(posColor!=color && posColor!=Configuration::NONE)
	    {

	      notPresent=true;

	      break;
	    }

	  if(posColor==Configuration::NONE)
	    {
	      
	      noneCount++;
	      toDoCount+=(yposevl-config->getPosInColumn(xposevl));
	    }

	}

      if(notPresent==true)
	continue;
      if(noneCount==1)
	ret+=2500;
      else if(noneCount==2)
	ret+=500;
      else if(noneCount==3)
	ret+=150;
      else if(noneCount==4)
	ret+=50;
      ret-=toDoCount;
    }
  return ret;
}

double MachinePlayer::choiceValue(int columnNo)
{
  double ret=0;

  ret+=getLineValue(Configuration::YELLOW,columnNo,1,1);
  ret+=getLineValue(Configuration::YELLOW,columnNo,-1,1);
  ret+=getLineValue(Configuration::YELLOW,columnNo,0,1);
  ret+=getLineValue(Configuration::YELLOW,columnNo,1,0);

  ret+=getLineValue(Configuration::RED,columnNo,1,1);
  ret+=getLineValue(Configuration::RED,columnNo,-1,1);
  ret+=getLineValue(Configuration::RED,columnNo,0,1);
  ret+=getLineValue(Configuration::RED,columnNo,1,0);

  return ret;
}
