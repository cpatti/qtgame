#include <qpixmap.h>
#include <qbitmap.h>
#include <qpainter.h>
#include <qcanvas.h>
#include "dropcanvas.h"
#include "configuration.h"

DropCanvas::DropCanvas(QObject * parent, const char * name):QCanvas(parent, name),columnWidthRatio(1.0/10.0), rowHeightRatio(1.0/10.0),topMarginRatio(1.5/10.0),leftMarginRatio(1.7/10.0),coinWidthRatio(1.0/12.0),currentColumn(Configuration::WIDTH/2), targetColumn(Configuration::WIDTH/2),movingHorizontal(false),currentCoin(Configuration::YELLOW), yellowColor(yellow),redColor(227,77,77)
{

  resize(500,400);

  drawTable();
  config=new Configuration();

}

void DropCanvas::drawTable()
{

  /*
    We draw the table as a rectangle and makes portions of it (where there are the 
    circular holes) transparent by using a QBitmap as its mask.
   */

  int ch=height(), cw=width();
  double colHeight=ch*rowHeightRatio, colWidth=cw*columnWidthRatio;
  double coinWidth=cw*coinWidthRatio;
  double topMargin=ch*topMarginRatio;
  double leftMargin=cw*leftMarginRatio;

  tablePixMap=new QPixmap(qRound(colWidth* Configuration::WIDTH),qRound(colHeight * Configuration::HEIGHT));
  tableBitMap=new QBitmap(tablePixMap->size(),true);
  tablePixMap->fill(QColor(243,170,111));
  tableBitMap->fill(color1);

  QPainter p(tableBitMap);
  

  for(int i=0;i<Configuration::HEIGHT;i++)
    {
      for(int j=0;j<Configuration::WIDTH;j++)
	{
	  double centerx=colWidth*(j);
	  double centery=colHeight*(i);
	  
	  p.setBrush(color0);
	  p.drawEllipse(qRound(centerx), qRound(centery), qRound(coinWidth), qRound(coinWidth));
	  
	}
    }

  p.end();

  tablePixMap->setMask(*tableBitMap);

  QCanvasPixmap * tcpixmap=new QCanvasPixmap(*tablePixMap,QPoint(0,0));
  QCanvasPixmapArray * tcpixmaparray = new QCanvasPixmapArray();
  tcpixmaparray->setImage(0,tcpixmap);

  tableSprite=new QCanvasSprite(tcpixmaparray,this);
  tableSprite->setX(leftMargin);
  tableSprite->setY(topMargin);
  tableSprite->setZ(1);
  tableSprite->show();

  bottomRect=new QCanvasRectangle(qRound(leftMargin - (colWidth * Configuration::WIDTH)*1/11.0 ), qRound(topMargin+ (colHeight * Configuration::HEIGHT))+2,qRound((colWidth * Configuration::WIDTH)* 13.0/11.0),qRound((3.0/4.0)*colHeight),this);
  bottomRect->setPen(NoPen);
  bottomRect->setBrush(QBrush(QColor(243,170,111)));
  bottomRect->show();

  dropCoin= new QCanvasEllipse(qRound(coinWidth)-1,qRound(coinWidth)-1,this);
  dropCoin->setBrush(currentCoin==Configuration::YELLOW? QBrush(yellowColor):QBrush(redColor));
  dropCoin->setX(leftMargin + coinWidth/2.0 +colWidth*currentColumn);
  dropCoin->setY(topMargin-colHeight + coinWidth/2.0 );
  dropCoin->show();

  setAdvancePeriod(100);

  update();

}

void DropCanvas::advance() // We rewrite advance to control movement of the coin
{
  if(!dropCoin)
    return;

  int ch=height(), cw=width();
  double colHeight=ch*rowHeightRatio, colWidth=cw*columnWidthRatio;
  double coinWidth=cw*coinWidthRatio;
  double topMargin=ch*topMarginRatio;
  double leftMargin=cw*leftMarginRatio;

  /*
    movingHorizontal is the variable used to indicate that the coin
    is in horizontal motion (across the columns on top of them).
    
    We use the animation that comes with QCanvasItem to simulate
    the vertical motion. Hence `dropCoin->animated() is true' implies
    that the coin is in vertical motion (dropping down).
   */

  if(dropCoin->animated()==false)
    {
      if(movingHorizontal==true)
	{
	  if(targetColumn > currentColumn)
	    {
	      dropCoin->moveBy(colWidth,0);
	      currentColumn++;
	    }
	  else if(targetColumn < currentColumn)
	    {
	      dropCoin->moveBy(-colWidth,0);
	      currentColumn--;
	    }
	  else
	    {
	      movingHorizontal=false;
	      if(currentCoin==Configuration::YELLOW)
		emit movedYellow(currentColumn);
	      else
		emit movedRed(currentColumn);
	    }
	  
	  update();
	}
      return;
    }
  if(dropCoin->collisions(true).count()>1) //There can be atmost one other canvasitem(the table) with which
                                           //the coin collides. Otherwise, we have to stop its motion
                                           //since it could have touched the top of another coin or the 
                                           //bottom of the table.
    {

      dropCoin->setAnimated(false);

      dropCoin= new QCanvasEllipse(qRound(coinWidth)-1,qRound(coinWidth)-1,this);
      dropCoin->setBrush((currentCoin==Configuration::YELLOW)? redColor:yellowColor);

      dropCoin->setX(leftMargin + coinWidth/2.0 + (currentColumn)*colWidth);
      dropCoin->setY(topMargin-colHeight + coinWidth/2.0 );

      dropCoin->show();

      currentCoin= ((currentCoin==Configuration::YELLOW)? (Configuration::RED):(Configuration::YELLOW));
      if(currentCoin==Configuration::YELLOW)
	{
	  if(scoreChange!=0)
	    emit redScored(scoreChange);
	  emit droppedRed(currentColumn);
	}
      else
	{
	  if(scoreChange!=0)
	    emit yellowScored(scoreChange);
	  emit droppedYellow(currentColumn);
	}
    }
  else
      dropCoin->advance(1);

  update();
}


/*The main drop function*/
bool DropCanvas::performDrop()
{
  if(movingHorizontal || dropCoin->animated()) //We cannot do this if the coin is moving horizontally or
                                               //is already dropping down.
    return false;
  if(config->canDrop(currentColumn)==false)
    return false;
  if(currentCoin==Configuration::NONE)
    return false;

  int oldScore;

  if(currentCoin==Configuration::YELLOW)
    oldScore=config->getYellowScore();
  else
    oldScore=config->getRedScore();

  config->performDrop(currentColumn,currentCoin);

  int newScore;

  if(currentCoin==Configuration::YELLOW)
    newScore=config->getYellowScore();
  else
    newScore=config->getRedScore();

  scoreChange=newScore-oldScore;

  dropCoin->setYVelocity(10.0);
  dropCoin->show();
  update();

  return true;
}

bool DropCanvas::moveBy(int noOfColumns)
{
  if(movingHorizontal || dropCoin->animated())   //We cannot do this if the coin is moving horizontally or
                                                 //is dropping down.
    return false;

  if( (currentColumn+noOfColumns >= Configuration::WIDTH) || (currentColumn+noOfColumns < 0) )
    return false;
  targetColumn=currentColumn+noOfColumns;
  if(targetColumn==currentColumn)
    movingHorizontal=false;
  else
    movingHorizontal=true;

  return true;
}

bool DropCanvas::move(int columnNo)
{
 if(movingHorizontal || dropCoin->animated())  //We cannot do this if the coin is moving horizontally or
                                               //is already dropping down.
    return false;

 if( (columnNo >= Configuration::WIDTH) || (columnNo < 0) )
   return false;
 targetColumn=columnNo;
  /*  if(targetColumn==currentColumn)
    movingHorizontal=false;
    else*/
 movingHorizontal=true;

  return true;
}


Configuration::State DropCanvas::getCurrentCoin()
{
  return currentCoin;
}
