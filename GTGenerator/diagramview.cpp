#include "diagramview.h"
#include "diagramscene.h"
#include "diagramitem.h"

#include <QDebug>
#include <QApplication>
#include <QWheelEvent>

int xWheel = 0;	
const qreal zoomPercentage = 0.1;
const qreal zoomOffsetOrigin = 50;
const int centerResolution = 10;

DiagramView::DiagramView(QWidget * parent ) : QGraphicsView(parent) {}

DiagramView::DiagramView(QGraphicsScene * scene, QWidget * parent) : QGraphicsView(scene, parent) {
    //this->scene = scene;
//    setInteractive(false);
//    setDragMode(QGraphicsView::RubberBandDrag);
}

void DiagramView::wheelEvent(QWheelEvent * event)
{
   // qDebug() << "graphicsView wheelEvent" << endl;   

//    qDebug() << "interactive" << isInteractive() << endl;
//    setDragMode(QGraphicsView::ScrollHandDrag);
//    qDebug() << "dragMode()" << dragMode() << endl;

    if(event->modifiers() & Qt::ControlModifier) {

//        setInteractive(true);
//        setDragMode(RubberBandDrag);

//        if(xWheel==0) {
//            averagePoint = event->pos();
//            //qDebug() << "setting initialZoomPoint at " << initialZoomPoint << endl;
//        } else if(xWheel < 0) {
//            initialZoomPoint = QPoint(0,0);
//        }

//        qDebug() << "xWheel" << xWheel << endl;
        centerCounter++;
        //qDebug() << "control pressed with wheel!" << endl;

        xWheel += event->delta()/40;
        //qDebug() << "Total Steps: "+QString::number(xWheel) << endl;
        qreal scaleValue = 1+zoomPercentage*xWheel;

        //qDebug() << "scale: " << scaleValue << endl;

        QMatrix oldMatrix = matrix();
        resetMatrix();

        scale(scaleValue, scaleValue);
//        qDebug() << "oldMatrix.dx()" << oldMatrix.dx() << endl;
//        qDebug() << "oldMatrix.dy()" << oldMatrix.dy() << endl;
        translate(oldMatrix.dx(), oldMatrix.dy());

        //translate(100, 100);
        setFocus();
//        qDebug() << "sceneRect() " << sceneRect() << endl;

        if(event->modifiers() & Qt::ShiftModifier) {
            //qDebug() << "plus shift!" << endl;
            centerOn(QPoint(0,0));
        } else {
            //qDebug() << "center on:" << event->pos() << endl;
            //qDebug() << "width:" << width() << endl;
            //qDebug() << "height:" << height() << endl;

            //centerOn(event->pos().x()/scaleValue,event->pos().y()/scaleValue);
            //centerOn(QPoint(event->pos() - QPoint(event->pos().x()/scaleValue,event->pos().y()/scaleValue)));

//            if(xWheel%10 == 0) {
//                int signX = event->pos().x() < initialZoomPoint.x()?-1:1;
//                int signY = event->pos().y() < initialZoomPoint.y()?-1:1;

//                QPoint averagePoint = QPoint((0.95*initialZoomPoint.x() + signX*0.05*event->pos().x())/1, (0.95*initialZoomPoint.y() + signY*0.05*event->pos().y())/1);


//            }

            //centerOn(event->pos());
            //QRectF areaVisible = QRectF(event->pos().x()-100, event->pos().y()-100, event->pos().x()+100,event->pos().y()+100);

            //QRectF areaVisible = QRectF(event->pos().x()-100, event->pos().y()-100, 200, 200);
            //ensureVisible(areaVisible, 0 ,0);
            //fitInView(areaVisible);
//            QGraphicsView::scrollContentsBy(100, 100);

//            qDebug() << "initialZoomPoint" << initialZoomPoint << endl;
//            qDebug() << "event->pos()" << event->pos() << endl;
//            qDebug() << "averagePoint" << averagePoint << endl;



//            if(itemAt(event->pos())->flags()){
//                centerOn(QPoint(itemAt(event->pos())->boundingRect().x(), itemAt(event->pos())->boundingRect().y()));
//                qDebug() << "itemFound" << endl;
//            } else {

//    //            qDebug() << "QPoint(zoomOffsetOrigin*scaleValue,zoomOffsetOrigin*scaleValue)" << QPoint(zoomOffsetOrigin*scaleValue,zoomOffsetOrigin*scaleValue) << endl;
//    //            qDebug() << "event->pos()" << event->pos() << endl;
//    //            qDebug() << "event->pos() - QPoint(100,100)" << event->pos() - QPoint(event->pos().x()/scaleValue,event->pos().y()/scaleValue) << endl;
//                //centerOn(event->pos().x()/3,event->pos().y()/3);
//                //centerOn(event->pos());

//                if(centerCounter%centerResolution == 0) {
//                    centerCounter = 0;
//                }
//            }
        }

        //qDebug() << "Scaling to: " << 1+zoomPercentage*xWheel << 1+zoomPercentage*xWheel << endl;
        //QGraphicsView::wheelEvent(event);

        //QGraphicsView::wheelEvent(event);
        event->accept();
    } else {
        QGraphicsView::wheelEvent(event);
    }

//    if(event->modifiers() & Qt::ControlModifier)
//    {
//        QGraphicsView::wheelEvent(event);
//    }
//    //otherwise, do yours
//    else
//    {
//       if(event->delta() > 0)
//       {
//           scale(2,2);
//       }
//       else
//       {
//           scale(0.5,0.5);
//       }
//   }
}

void DiagramView::mouseMoveEvent(QMouseEvent * event) {
    //qDebug() << "mouseMoveEvent" << endl;

    QGraphicsView::mouseMoveEvent(event);
}

void DiagramView::mousePressEvent(QMouseEvent * event) {
//    if(event->modifiers() & Qt::ControlModifier) {
//        if(event->modifiers() & Qt::ShiftModifier) {
//            setDragMode(RubberBandDrag);
//            setInteractive(true);
//        }
//    } else
    if(event->modifiers() & Qt::ShiftModifier) {
        setDragMode(ScrollHandDrag);
        setInteractive(false);
    } else if(event->modifiers() & Qt::ControlModifier) {
        setDragMode(RubberBandDrag);
        setInteractive(true);
    } else {
        setDragMode(NoDrag);
        setInteractive(true);        
    }    

    QGraphicsView::mousePressEvent(event);
}

void DiagramView::mouseReleaseEvent(QMouseEvent * event) {

    if(!(event->modifiers() & Qt::ControlModifier)) {
        setDragMode(NoDrag);
        setInteractive(true);
    }

//    qDebug() << "mouseReleaseEvent" << endl;
//    lastX = event->x();
//    lastY = event->y();
//    qDebug() << "lastX: " << lastX << endl;
//    qDebug() << "lastY: " << lastY << endl;

//    //QGraphicsPolygonItem item;
//    DiagramItem *item;

//    item = new DiagramItem(NULL, NULL);
//    item->setBrush(Qt::transparent);
//    scene->addItem(item);

//    QPolygonF myPolygon;

//    myPolygon << QPointF(firstX, firstY)
//              << QPointF(lastX, firstY)
//              << QPointF(lastX, lastY)
//              << QPointF(firstX, lastY)
//              << QPointF(firstX, firstY);

//    item->setPolygon(myPolygon);
//    item->show();
    QGraphicsView::mouseReleaseEvent(event);
}

void DiagramView::scrollContentsBy(int dx, int dy) {
    //qDebug() << "scrollContentsBy: " << dx << ", " << dy << endl;
    QGraphicsView::scrollContentsBy(dx, dy);
}
