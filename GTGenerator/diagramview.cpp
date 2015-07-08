#include "diagramview.h"
#include "diagramscene.h"
#include "diagramitem.h"

#include <QDebug>
#include <QApplication>
#include <QWheelEvent>

DiagramView::DiagramView(QWidget * parent ) : QGraphicsView(parent) {}

DiagramView::DiagramView(QGraphicsScene * scene, QWidget * parent) : QGraphicsView(scene, parent) {
    //this->scene = scene;
//    setInteractive(false);
//    setDragMode(QGraphicsView::RubberBandDrag);
	data = GTProjectData::Instance();
	scrollEnabled = true;
}

DiagramView::DiagramView(bool enabled, QGraphicsScene * scene, QWidget * parent) : QGraphicsView(scene, parent) {
    //this->scene = scene;
//    setInteractive(false);
//    setDragMode(QGraphicsView::RubberBandDrag);
	data = GTProjectData::Instance();
	scrollEnabled = enabled;	
}

void DiagramView::updateZoom() {
	QMatrix oldMatrix = matrix();
    resetMatrix();

    scale(data->scaleValue, data->scaleValue);
//        qDebug() << "oldMatrix.dx()" << oldMatrix.dx() << endl;
//        qDebug() << "oldMatrix.dy()" << oldMatrix.dy() << endl;
    translate(oldMatrix.dx(), oldMatrix.dy());

    //translate(100, 100);
    setFocus();
}

void DiagramView::wheelEvent(QWheelEvent * event)
{
   // qDebug() << "graphicsView wheelEvent" << endl;   

//    qDebug() << "interactive" << isInteractive() << endl;
//    setDragMode(QGraphicsView::ScrollHandDrag);
//    qDebug() << "dragMode()" << dragMode() << endl;

	qDebug() << "xWheel " << data->xWheel << endl;
	qDebug() << "scrollEnabled " << scrollEnabled << endl;

    if(event->modifiers() & Qt::ControlModifier) {

//        setInteractive(true);
//        setDragMode(RubberBandDrag);

//        if(xWheel==0) {
//            averagePoint = event->pos();
//            //qDebug() << "setting initialZoomPoint at " << initialZoomPoint << endl;
//        } else if(xWheel < 0) {
//            initialZoomPoint = QPoint(0,0);
//        }
        
		if(scrollEnabled) {
			centerCounter++;
			//qDebug() << "control pressed with wheel!" << endl;

			data->xWheel += event->delta()/40;
			//qDebug() << "Total Steps: "+QString::number(xWheel) << endl;
			data->scaleValue = (qreal)(1.0+data->zoomPercentage*data->xWheel);

			//qDebug() << "scale: " << scaleValue << endl;

			QMatrix oldMatrix = matrix();
			resetMatrix();

			scale(data->scaleValue, data->scaleValue);
	//        qDebug() << "oldMatrix.dx()" << oldMatrix.dx() << endl;
	//        qDebug() << "oldMatrix.dy()" << oldMatrix.dy() << endl;
			translate(oldMatrix.dx(), oldMatrix.dy());

			qDebug() << "xWheel " << data->xWheel << endl;
			qDebug() << "scrollEnabled " << scrollEnabled << endl;
			qDebug() << "data->scaleValue " << data->scaleValue << endl;

			//translate(100, 100);
			setFocus();
	//        qDebug() << "sceneRect() " << sceneRect() << endl;

			if(event->modifiers() & Qt::ShiftModifier) {
				//qDebug() << "plus shift!" << endl;
				centerOn(QPoint(0,0));
			}

			event->accept();
		}        
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
