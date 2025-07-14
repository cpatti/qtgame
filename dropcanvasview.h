#ifndef __DROPCANVASVIEW_H_
#define __DROPCANVASVIEW_H_

#include <qcanvas.h>

class DropCanvasView : public QCanvasView
{
 public:
  DropCanvasView(QWidget * parent=0, const char * name=0);
  DropCanvasView(QCanvas * canvas, QWidget * parent=0, const char * name=0);

 protected:
  void resizeEvent(QResizeEvent *); // We rewrite the resizeEvent so that the 
                                    // canvas is shown properly when this 
                                    // canvasview is resized.

};

#endif
