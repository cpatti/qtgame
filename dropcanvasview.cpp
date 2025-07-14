#include <iostream>
#include <qpainter.h>

#include "dropcanvas.h"
#include "dropcanvasview.h"

DropCanvasView::DropCanvasView(QWidget * parent, const char * name) : QCanvasView(parent, name)
{
  setFocusPolicy(ClickFocus);
  setVScrollBarMode(AlwaysOff);
  setHScrollBarMode(AlwaysOff);
  setMinimumSize(40,40);
}

DropCanvasView::DropCanvasView(QCanvas * canvas, QWidget * parent, const char * name) : QCanvasView(canvas,parent, name)
{
  setFocusPolicy(ClickFocus);
  setVScrollBarMode(AlwaysOff);
  setHScrollBarMode(AlwaysOff);
  setMinimumSize(40,40);
}

void DropCanvasView::resizeEvent(QResizeEvent * e)
{
  double nw=e->size().width()-4;
  double nh=e->size().height()-4;

  QWMatrix qwm;
  setWorldMatrix(qwm.scale(nw/canvas()->width(),nh/canvas()->height())); 

  //In case of a resize, scale the worldmatrix appropriately.

}
