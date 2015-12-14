#include <QtGui>

#include "diagramscene.h"
#include "diagramitem.h"
#include "taggingwidget.h"
#include <QDebug>

int margin = 5;
qreal penWidth = 1.3;

DiagramItem::DiagramItem(int index, QTableWidget *table, QListWidget *list, QGraphicsItem *parent, QGraphicsScene *scene) : QGraphicsPolygonItem(parent, scene)
{
	data = GTProjectData::Instance();

    itemIndex = index;
    roiTable = table;
    roiList = list;
    //scenesInfos = infos;
    //currentSceneInfoIndex = infoIndex;

    setBrush(Qt::transparent);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setAcceptDrops(true);
    setAcceptHoverEvents(true);
	setToolTip(data->currentLabelString);

    color = data->currentLabelColor;
    setPen(QPen(QBrush(color), penWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));

    QFont tooltipFont = QFont("Newyork", 18);
    QToolTip::setFont(tooltipFont);
}

DiagramItem::DiagramItem(DiagramROI diag_roi, int index, QTableWidget *table, QListWidget *list, QGraphicsItem *parent, QGraphicsScene *scene) : QGraphicsPolygonItem(parent, scene)
{
	data = GTProjectData::Instance();
	roi = &diag_roi;

    itemIndex = index;
    roiTable = table;
    roiList = list;
    //scenesInfos = infos;
    //currentSceneInfoIndex = infoIndex;

    setBrush(Qt::transparent);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setAcceptDrops(true);
    setAcceptHoverEvents(true);
    setToolTip(diag_roi.getLabel());

//    if(roi.labeled) {
//        color = roi.color;
//    } else {
//        color = Qt::white;
//    }

    color = diag_roi.getColor();

    setPen(QPen(QBrush(color), penWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    //setPos(QPointF(roi.tpx, roi.tpy));   

    polygon.clear();
    polygon << QPointF(diag_roi.getTpx(), diag_roi.getTpy())
              << QPointF(diag_roi.getBrx(), diag_roi.getTpy())
              << QPointF(diag_roi.getBrx(), diag_roi.getBry())
              << QPointF(diag_roi.getTpx(), diag_roi.getBry())
              << QPointF(diag_roi.getTpx(), diag_roi.getTpy());

    setPolygon(polygon);

    QFont tooltipFont = QFont("Newyork", 18);
    QToolTip::setFont(tooltipFont);
}

void DiagramItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event) {
    //qDebug() << "mouseDoubleClickEvent" << endl;
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void DiagramItem::mousePressEvent(QGraphicsSceneMouseEvent * event) {   
    //QToolTip::showText(pos().toPoint(), toolTip());

//    initCoords = true;
    //qDebug() << "mousePressEvent initCoords" << initCoords << endl;

//    qDebug() << "item mousePressEvent" << endl;
//    if(isSelected()) {
//       // qDebug() << "selected!" << endl;
//    }
//    lastSceneXPos = event->scenePos().x();
//    lastSceneYPos = event->scenePos().y();

    //QPolygonF itemBR = boundingRect();
    QPolygonF sceneBR = mapToScene(boundingRect());
    //QPoint current_mTopLeftPoint = QPoint(scenePos().x() - boundingRect().x()/2, pos().y() - boundingRect().y()/2);
    current_mTopLeftPoint = sceneBR.at(0).toPoint();
    //QPoint current_mBottomRightPoint = QPoint(scenePos().x() + boundingRect().x()/2, pos().y() + boundingRect().y()/2);
    current_mBottomRightPoint = sceneBR.at(2).toPoint();

    initialResizePoint = current_mTopLeftPoint;

    //qDebug() << "setting table selection" << endl;
    roiTable->selectRow(itemIndex);

//    qDebug() << "scenePos() " << scenePos() << endl;
//    qDebug() << "current_mTopLeftPoint " << current_mTopLeftPoint << endl;


//    qDebug() << "starting to resize on current_mTopLeftPoint " << current_mTopLeftPoint << endl;
//    qDebug() << "starting to resize on current_mBottomRightPoint " << current_mBottomRightPoint << endl;

    QPointF eventPoint = mapToScene(event->pos());

    if ( (eventPoint.x() >= current_mBottomRightPoint.x() - margin &&
             eventPoint.x() <= current_mBottomRightPoint.x() &&
             eventPoint.y() >= current_mBottomRightPoint.y() - margin &&
             eventPoint.y() <= current_mBottomRightPoint.y() ) ) {
        selectionResizingStart = 1;
    } else if ((eventPoint.x() >= current_mTopLeftPoint.x() &&
               eventPoint.x() <= current_mTopLeftPoint.x() + margin &&
               eventPoint.y() >= current_mTopLeftPoint.y() &&
               eventPoint.y() <= current_mTopLeftPoint.y() + margin ))
    {
//            qDebug() << "Qt::SizeFDiagCursor" << endl;
        selectionResizingStart = 2;
    }
    else if ( (eventPoint.x() >= current_mBottomRightPoint.x() - margin &&
             eventPoint.x() <= current_mBottomRightPoint.x() &&
             eventPoint.y() >= current_mTopLeftPoint.y() &&
             eventPoint.y() <= current_mTopLeftPoint.y() + margin ) ) {
        selectionResizingStart = 3;
    } else if ( (eventPoint.x() >= current_mTopLeftPoint.x() &&
               eventPoint.x() <= current_mTopLeftPoint.x() + margin &&
               eventPoint.y() >= current_mBottomRightPoint.y() - margin &&
               eventPoint.y() <= current_mBottomRightPoint.y() ))
    {
//            qDebug() << "Qt::SizeBDiagCursor" << endl;
        selectionResizingStart = 4;
    }
    else if ( (eventPoint.x() >= current_mTopLeftPoint.x() + margin &&
             eventPoint.x() <= current_mBottomRightPoint.x() - margin &&
             eventPoint.y() >= current_mTopLeftPoint.y() &&
             eventPoint.y() <= current_mTopLeftPoint.y() + margin ) ) {
        selectionResizingStart = 5;
    } else if( (eventPoint.x() >= current_mTopLeftPoint.x() + margin &&
               eventPoint.x() <= current_mBottomRightPoint.x() - margin &&
               eventPoint.y() >= current_mBottomRightPoint.y() - margin &&
               eventPoint.y() <= current_mBottomRightPoint.y() ))
    {
//            qDebug() << "Qt::SizeVerCursor" << endl;
        selectionResizingStart = 6;
    }
    else if ( (eventPoint.x() >= current_mTopLeftPoint.x() &&
             eventPoint.x() <= current_mTopLeftPoint.x() + margin &&
             eventPoint.y() >= current_mTopLeftPoint.y() + margin &&
             eventPoint.y() <= current_mBottomRightPoint.y() - margin ) ) {
        selectionResizingStart = 7;
    } else if ( (eventPoint.x() >= current_mBottomRightPoint.x() - margin &&
               eventPoint.x() <= current_mBottomRightPoint.x() &&
               eventPoint.y() >= current_mTopLeftPoint.y() + margin &&
               eventPoint.y() <= current_mBottomRightPoint.y() - margin ))
    {
//            qDebug() << "Qt::SizeHorCursor" << endl;
        selectionResizingStart = 8;
    }
    else
    {
//            qDebug() << "Qt::ArrowCursor" << endl;
        selectionResizingStart = 0;
    }

    //qDebug() << "scenePos()" << scenePos() << endl;

    //qDebug() << "event->scenePos()" << event->scenePos() << endl;

    //setX(100);
    //setY(100);

//    qreal startX = scenePos().x();
//    qreal startY = scenePos().y();

//    qreal currentX = pos().x();
//    qreal currentY = pos().y();

//    qDebug() << "boundingRect().width()" << boundingRect().width() << endl;
//    qDebug() << "boundingRect().height()" << boundingRect().height() << endl;

//    //setX(currentX+100);
//    //setY(currentY+100);

//    qreal initW = boundingRect().width();
//    qreal initH = boundingRect().height();

//    qreal initX = startX - initW/2;
//    qreal initY = startY - initH/2;

//    qreal finalX = currentX;
//    qreal finalY = currentY;

//    qreal finalW = finalX - initX;
//    qreal finalH = finalY - initY;


//    scale(finalW/initW, finalH/initH);

    //scale();   
    QGraphicsItem::mousePressEvent(event);
}

void DiagramItem::mouseMoveEvent(QGraphicsSceneMouseEvent * event) {

//    qDebug() << "mouseMoveEvent on item!" << endl;
    //    qDebug() << "selectionResizingStart" << selectionResizingStart << endl;

    QPolygonF polygon;
    QPointF eventPointF = mapToScene(event->pos());
    QPoint eventPoint = QPoint((int)eventPointF.x(), (int)eventPointF.y());

//    if(initCoords) {
//        QPolygonF sceneBR = mapToScene(boundingRect());
////        qDebug() << "current_mTopLeftPoint" << current_mTopLeftPoint << endl;
//        current_mTopLeftPoint = sceneBR.at(0).toPoint();
////        qDebug() << "current_mTopLeftPoint" << current_mTopLeftPoint << endl;
//        initCoords = false;
////        qDebug() << "mouseMoveEvent initCoords" << initCoords << endl;
//    }

//    qDebug() << "current_mTopLeftPoint" << current_mTopLeftPoint << endl;

    //QPointF eventPoint = event->scenePos();

    switch(selectionResizingStart) {
    case 1:
//        mBottomRightPoint = event->pos();
//        qDebug() << "resizing with current_mTopLeftPoint " << current_mTopLeftPoint << endl;
//        qDebug() << "resizing with resize on current_mBottomRightPoint " << current_mBottomRightPoint << endl;
//        QPoint current_mTopLeftPoint = QPoint(scenePos().x() - boundingRect().x()/2, pos().y() - boundingRect().y()/2);
//        current_mTopLeftPoint = sceneBR.at(0).toPoint();

        polygon.clear();

        polygon << QPointF(current_mTopLeftPoint.x(), current_mTopLeftPoint.y())
                  << QPointF(eventPoint.x(), current_mTopLeftPoint.y())
                  << QPointF(eventPoint.x(), eventPoint.y())
                  << QPointF(current_mTopLeftPoint.x(), eventPoint.y())
                  << QPointF(current_mTopLeftPoint.x(), current_mTopLeftPoint.y());

//        setPen(QPen(QBrush(color), penWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        setPolygon(polygon);
        setX(0);
        setY(0);
        show();

        updateItemRow((int)boundingRect().width(), (int)boundingRect().height(), current_mTopLeftPoint.x(), current_mTopLeftPoint.y(), (int)eventPoint.x(), (int)eventPoint.y(), false);

        break;

    case 2:
//        mTopLeftPoint = event->pos();
        polygon.clear();

        polygon << QPointF(eventPoint.x(), eventPoint.y())
                  << QPointF(current_mBottomRightPoint.x(), eventPoint.y())
                  << QPointF(current_mBottomRightPoint.x(), current_mBottomRightPoint.y())
                  << QPointF(eventPoint.x(), current_mBottomRightPoint.y())
                  << QPointF(eventPoint.x(), eventPoint.y());

//        setPen(QPen(QBrush(color), penWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        setPolygon(polygon);
        setX(0);
        setY(0);
        show();
        updateItemRow((int)boundingRect().width(), (int)boundingRect().height(), (int)eventPoint.x(), (int)eventPoint.y(), current_mBottomRightPoint.x(), current_mBottomRightPoint.y(), false);

        break;

    case 3:
//        mBottomRightPoint.setX(event->pos().x());
//        mTopLeftPoint.setY(event->pos().y());

        polygon.clear();

        polygon << QPointF(current_mTopLeftPoint.x(), eventPoint.y())
                  << QPointF(eventPoint.x(), eventPoint.y())
                  << QPointF(eventPoint.x(), current_mBottomRightPoint.y())
                  << QPointF(current_mTopLeftPoint.x(), current_mBottomRightPoint.y())
                  << QPointF(current_mTopLeftPoint.x(), eventPoint.y());

//        setPen(QPen(QBrush(color), penWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        setPolygon(polygon);
        setX(0);
        setY(0);
        show();
        updateItemRow((int)boundingRect().width(), (int)boundingRect().height(), current_mTopLeftPoint.x(), (int)eventPoint.y(), (int)eventPoint.x(), current_mBottomRightPoint.y(), false);

        break;

    case 4:
//        mBottomRightPoint.setY(event->pos().y());
//        mTopLeftPoint.setX(event->pos().x());

        polygon.clear();

        polygon << QPointF(current_mBottomRightPoint.x(), current_mTopLeftPoint.y())
                  << QPointF(current_mBottomRightPoint.x(), eventPoint.y())
                  << QPointF(eventPoint.x(), eventPoint.y())
                  << QPointF(eventPoint.x(), current_mTopLeftPoint.y())
                  << QPointF(current_mBottomRightPoint.x(), current_mTopLeftPoint.y());

//        setPen(QPen(QBrush(color), penWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        setPolygon(polygon);
        setX(0);
        setY(0);
        show();
        updateItemRow((int)boundingRect().width(), (int)boundingRect().height(), current_mBottomRightPoint.x(), current_mTopLeftPoint.y(), (int)eventPoint.x(), (int)eventPoint.y(), false);

        break;

    case 5:
//        mTopLeftPoint.setY(event->pos().y());

        polygon.clear();

        polygon << QPointF(current_mTopLeftPoint.x(), eventPoint.y())
                  << QPointF(current_mBottomRightPoint.x(), eventPoint.y())
                  << QPointF(current_mBottomRightPoint.x(), current_mBottomRightPoint.y())
                  << QPointF(current_mTopLeftPoint.x(), current_mBottomRightPoint.y())
                  << QPointF(current_mTopLeftPoint.x(), eventPoint.y());

//        setPen(QPen(QBrush(color), penWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        setPolygon(polygon);
        setX(0);
        setY(0);
        show();
        updateItemRow((int)boundingRect().width(), (int)boundingRect().height(), current_mTopLeftPoint.x(), (int)eventPoint.y(), current_mBottomRightPoint.x(), current_mBottomRightPoint.y(), false);

        break;

    case 6:
//        mBottomRightPoint.setY(event->pos().y());

        polygon.clear();

        polygon << QPointF(current_mTopLeftPoint.x(), current_mTopLeftPoint.y())
                  << QPointF(current_mBottomRightPoint.x(), current_mTopLeftPoint.y())
                  << QPointF(current_mBottomRightPoint.x(), eventPoint.y())
                  << QPointF(current_mTopLeftPoint.x(), eventPoint.y())
                  << QPointF(current_mTopLeftPoint.x(), current_mTopLeftPoint.y());

//        setPen(QPen(QBrush(color), penWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        setPolygon(polygon);
        setX(0);
        setY(0);
        show();
        updateItemRow((int)boundingRect().width(), (int)boundingRect().height(), current_mTopLeftPoint.x(), current_mTopLeftPoint.y(), current_mBottomRightPoint.x(), (int)eventPoint.y(), false);

        break;

    case 7:
//        mTopLeftPoint.setX(event->pos().x());
        polygon.clear();

        polygon << QPointF(eventPoint.x(), current_mTopLeftPoint.y())
                  << QPointF(current_mBottomRightPoint.x(), current_mTopLeftPoint.y())
                  << QPointF(current_mBottomRightPoint.x(), current_mBottomRightPoint.y())
                  << QPointF(eventPoint.x(), current_mBottomRightPoint.y())
                  << QPointF(eventPoint.x(), current_mTopLeftPoint.y());

//        setPen(QPen(QBrush(color), penWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        setPolygon(polygon);
        setX(0);
        setY(0);
        show();
        updateItemRow((int)boundingRect().width(), (int)boundingRect().height(), (int)eventPoint.x(), current_mTopLeftPoint.y(), current_mBottomRightPoint.x(), current_mBottomRightPoint.y(), false);

        break;

    case 8:
//        mBottomRightPoint.setX(event->pos().x());
        polygon.clear();

        polygon << QPointF(current_mTopLeftPoint.x(), current_mTopLeftPoint.y())
                  << QPointF(eventPoint.x(), current_mTopLeftPoint.y())
                  << QPointF(eventPoint.x(), current_mBottomRightPoint.y())
                  << QPointF(current_mTopLeftPoint.x(), current_mBottomRightPoint.y())
                  << QPointF(current_mTopLeftPoint.x(), current_mBottomRightPoint.y());

//        setPen(QPen(QBrush(color), penWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        setPolygon(polygon);
        setX(0);
        setY(0);
        show();
        updateItemRow((int)boundingRect().width(), (int)boundingRect().height(), current_mTopLeftPoint.x(), current_mTopLeftPoint.y(), (int)eventPoint.x(), current_mBottomRightPoint.y(), false);

        break;

    default:
//        mBottomRightPoint = event->pos();
//        polygon << QPointF(firstX, firstY)
//                  << QPointF(lastX, firstY)
//                  << QPointF(lastX, lastY)
//                  << QPointF(firstX, lastY)
//                  << QPointF(firstX, firstY);
//        qDebug() << "default mouseMoveEvent" << endl;
        QPolygonF sceneBR = mapToScene(boundingRect());

        updateItemRow((int)boundingRect().width(), (int)boundingRect().height(), (int)sceneBR.at(0).toPoint().x(), (int)sceneBR.at(0).toPoint().y(), (int)sceneBR.at(2).toPoint().x(), (int)sceneBR.at(2).toPoint().y(), false);
        QGraphicsItem::mouseMoveEvent(event);
        break;
    }
    //show();

    //qDebug() << "mouseMoveEvent" << endl;
    //qDebug() << "this->pos() " << this->pos() << endl;
    //qDebug() << "event->pos() " << event->pos() << endl;

    //qDebug() << "scenePos()" << scenePos() << endl;

    //qDebug() << "event->scenePos()" << event->scenePos() << endl;

//    polygon.clear();

//    polygon << QPointF(scenePos().x(), scenePos().y())
//              << QPointF(event->scenePos().x(), scenePos().y())
//              << QPointF(event->scenePos().x(), event->scenePos().y())
//              << QPointF(scenePos().x(), event->scenePos().y())
//              << QPointF(scenePos().x(), scenePos().y());

//    polygon << QPointF(lastSceneXPos, lastSceneYPos)
//              << QPointF(event->scenePos().x(), lastSceneYPos)
//              << QPointF(event->scenePos().x(), event->scenePos().y())
//              << QPointF(lastSceneXPos, event->scenePos().y())
//              << QPointF(lastSceneXPos, lastSceneYPos);

//    polygon << QPointF(100, 100)
//              << QPointF(event->scenePos().x(), 100)
//              << QPointF(event->scenePos().x(), event->scenePos().y())
//              << QPointF(100, event->scenePos().y())
//              << QPointF(100, 100);

//    //setBrush(Qt::transparent);

//    setPolygon(polygon);

//    setX(100);
//    setY(100);
}

void DiagramItem::mouseReleaseEvent(QGraphicsSceneMouseEvent * event) {    

    QPolygonF sceneBR = mapToScene(boundingRect());
    //QPoint current_mTopLeftPoint = QPoint(scenePos().x() - boundingRect().x()/2, pos().y() - boundingRect().y()/2);
    current_mTopLeftPoint = sceneBR.at(0).toPoint();
    //QPoint current_mBottomRightPoint = QPoint(scenePos().x() + boundingRect().x()/2, pos().y() + boundingRect().y()/2);
    current_mBottomRightPoint = sceneBR.at(2).toPoint();

    //qDebug() << "boundingRect()" << boundingRect() << endl;

    //setPen(QPen(QBrush(color), penWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));

    updateItemRow((int)boundingRect().width(), (int)boundingRect().height(), current_mTopLeftPoint.x(), current_mTopLeftPoint.y(), current_mBottomRightPoint.x(), current_mBottomRightPoint.y(), true);
//        qDebug() << "roi table[4]: " << bryItem->text() << endl;

    //qDebug() << "mouseReleaseEvent" << endl;
    if(isSelected()) {
//        qDebug() << "hoverMoveEvent" << endl;

//        qDebug() << "eventPoint " << eventPoint << endl;
//        qDebug() << "current_mTopLeftPoint " << current_mTopLeftPoint << endl;
//        qDebug() << "current_mBottomRightPoint " << current_mBottomRightPoint << endl;


    }

//    QPolygonF polygon;
//    QPointF eventPoint = mapToScene(event->pos());

//    if(selectionResizingStart == 1) {
//        polygon << QPointF(current_mTopLeftPoint.x(), current_mTopLeftPoint.y())
//                  << QPointF(eventPoint.x(), current_mTopLeftPoint.y())
//                  << QPointF(eventPoint.x(), eventPoint.y())
//                  << QPointF(current_mTopLeftPoint.x(), eventPoint.y())
//                  << QPointF(current_mTopLeftPoint.x(), current_mTopLeftPoint.y());

//        setPolygon(polygon);
//        setX(0);
//        setY(0);
//        show();
//    }


//    initCoords = false;
//    selectionResizingStart = 0;

//    QPointF eventPoint = mapToScene(event->pos());

//    QPolygonF itemBR = boundingRect();
//    QPolygonF sceneBR = mapToScene(boundingRect());

////    qDebug() << "itemBR" << itemBR << endl;
////    qDebug() << "sceneBR" << sceneBR << endl;

//    //QPoint current_mTopLeftPoint = QPoint(scenePos().x() - boundingRect().x()/2, pos().y() - boundingRect().y()/2);
//    current_mTopLeftPoint = sceneBR.at(0).toPoint();
//    //QPoint current_mBottomRightPoint = QPoint(scenePos().x() + boundingRect().x()/2, pos().y() + boundingRect().y()/2);
//    current_mBottomRightPoint = sceneBR.at(2).toPoint();

    QGraphicsItem::mouseReleaseEvent(event);
}

void DiagramItem::hoverEnterEvent(QGraphicsSceneHoverEvent * event) {
//    qDebug() << "hoverEnterEvent" << endl;
//    QFont tooltipFont = QFont("Newyork", 18);
//    QToolTip::setFont(tooltipFont);
    QToolTip::showText(event->screenPos(), toolTip());
    QGraphicsItem::hoverEnterEvent(event);
}

void DiagramItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) {
    //qDebug() << "hoverLeaveEvent" << endl;
    QToolTip::hideText();
    QGraphicsItem::hoverLeaveEvent(event);
}

void DiagramItem::hoverMoveEvent(QGraphicsSceneHoverEvent * event) {
//    QFont tooltipFont = QFont("Newyork", 18);
//    QToolTip::setFont(tooltipFont);
//    QToolTip::showText(pos().toPoint(), toolTip());
//    if(isSelected()) {
//        qDebug() << "hoverMoveEvent" << endl;

        //QPolygonF itemBR = boundingRect();
        QPolygonF sceneBR = mapToScene(boundingRect());

        //qDebug() << "itemBR" << itemBR << endl;
       // qDebug() << "sceneBR" << sceneBR << endl;

        //QPoint current_mTopLeftPoint = QPoint(scenePos().x() - boundingRect().x()/2, pos().y() - boundingRect().y()/2);
        QPoint hover_current_mTopLeftPoint = sceneBR.at(0).toPoint();
        //QPoint current_mBottomRightPoint = QPoint(scenePos().x() + boundingRect().x()/2, pos().y() + boundingRect().y()/2);
        QPoint hover_current_mBottomRightPoint = sceneBR.at(2).toPoint();
        QPointF eventPoint = mapToScene(event->pos());

//        qDebug() << "eventPoint " << eventPoint << endl;
//        qDebug() << "current_mTopLeftPoint " << current_mTopLeftPoint << endl;
//        qDebug() << "current_mBottomRightPoint " << current_mBottomRightPoint << endl;

        if (eventPoint.x() > hover_current_mTopLeftPoint.x() + margin &&
            eventPoint.x() < hover_current_mBottomRightPoint.x() - margin &&
            eventPoint.y() > hover_current_mTopLeftPoint.y() + margin &&
            eventPoint.y() < hover_current_mBottomRightPoint.y() - margin)
        {
            setCursor(Qt::SizeAllCursor);
        }
        else if ( (eventPoint.x() >= hover_current_mBottomRightPoint.x() - margin &&
                 eventPoint.x() <= hover_current_mBottomRightPoint.x() &&
                 eventPoint.y() >= hover_current_mBottomRightPoint.y() - margin &&
                 eventPoint.y() <= hover_current_mBottomRightPoint.y() ) ||
                    (eventPoint.x() >= hover_current_mTopLeftPoint.x() &&
                   eventPoint.x() <= hover_current_mTopLeftPoint.x() + margin &&
                   eventPoint.y() >= hover_current_mTopLeftPoint.y() &&
                   eventPoint.y() <= hover_current_mTopLeftPoint.y() + margin ))
        {
//            qDebug() << "Qt::SizeFDiagCursor" << endl;
            setCursor(Qt::SizeFDiagCursor);
        }
        else if ( (eventPoint.x() >= hover_current_mBottomRightPoint.x() - margin &&
                 eventPoint.x() <= hover_current_mBottomRightPoint.x() &&
                 eventPoint.y() >= hover_current_mTopLeftPoint.y() &&
                 eventPoint.y() <= hover_current_mTopLeftPoint.y() + margin ) ||
                    (eventPoint.x() >= hover_current_mTopLeftPoint.x() &&
                   eventPoint.x() <= hover_current_mTopLeftPoint.x() + margin &&
                   eventPoint.y() >= hover_current_mBottomRightPoint.y() - margin &&
                   eventPoint.y() <= hover_current_mBottomRightPoint.y() ))
        {
//            qDebug() << "Qt::SizeBDiagCursor" << endl;
            setCursor(Qt::SizeBDiagCursor);
        }
        else if ( (eventPoint.x() >= hover_current_mTopLeftPoint.x() + margin &&
                 eventPoint.x() <= hover_current_mBottomRightPoint.x() - margin &&
                 eventPoint.y() >= hover_current_mTopLeftPoint.y() &&
                 eventPoint.y() <= hover_current_mTopLeftPoint.y() + margin ) ||
                    (eventPoint.x() >= hover_current_mTopLeftPoint.x() + margin &&
                   eventPoint.x() <= hover_current_mBottomRightPoint.x() - margin &&
                   eventPoint.y() >= hover_current_mBottomRightPoint.y() - margin &&
                   eventPoint.y() <= hover_current_mBottomRightPoint.y() ))
        {
//            qDebug() << "Qt::SizeVerCursor" << endl;
            setCursor(Qt::SizeVerCursor);
        }
        else if ( (eventPoint.x() >= hover_current_mTopLeftPoint.x() &&
                 eventPoint.x() <= hover_current_mTopLeftPoint.x() + margin &&
                 eventPoint.y() >= hover_current_mTopLeftPoint.y() + margin &&
                 eventPoint.y() <= hover_current_mBottomRightPoint.y() - margin ) ||
                    (eventPoint.x() >= hover_current_mBottomRightPoint.x() - margin &&
                   eventPoint.x() <= hover_current_mBottomRightPoint.x() &&
                   eventPoint.y() >= hover_current_mTopLeftPoint.y() + margin &&
                   eventPoint.y() <= hover_current_mBottomRightPoint.y() - margin ))
        {
//            qDebug() << "Qt::SizeHorCursor" << endl;
            setCursor(Qt::SizeHorCursor);
        }
        else
        {
//            qDebug() << "Qt::ArrowCursor" << endl;
            setCursor(Qt::ArrowCursor);
        }
//    }
    QGraphicsItem::hoverMoveEvent(event);
}

void DiagramItem::keyPressEvent(QKeyEvent * event){
    //qDebug() << "keyPressEvent" << endl;
    QGraphicsItem::keyPressEvent(event);
}

void DiagramItem::keyReleaseEvent(QKeyEvent * event){
    //qDebug() << "keyReleaseEvent" << endl;
    QGraphicsItem::keyReleaseEvent(event);
}

void DiagramItem::focusInEvent(QFocusEvent * event){
    qDebug() << "focusInEvent" << endl;
    QGraphicsItem::focusInEvent(event);
}

void DiagramItem::focusOutEvent(QFocusEvent * event){
    qDebug() << "focusOutEvent" << endl;
    QGraphicsItem::focusOutEvent(event);
}

void DiagramItem::dragEnterEvent(QGraphicsSceneDragDropEvent * event){
    //qDebug() << "dragEnterEvent" << endl;
    QGraphicsItem::dragEnterEvent(event);
}

void DiagramItem::dragLeaveEvent(QGraphicsSceneDragDropEvent * event){
    //qDebug() << "dragLeaveEvent" << endl;
    QGraphicsItem::dragLeaveEvent(event);
}

void DiagramItem::dragMoveEvent(QGraphicsSceneDragDropEvent * event){
    //qDebug() << "dragMoveEvent" << endl;
    QGraphicsItem::dragMoveEvent(event);
}

void DiagramItem::dropEvent(QGraphicsSceneDragDropEvent * event){
//    qDebug() << "dropEvent" << endl;

//    qDebug() << "mime Text " << event->mimeData()->text() << endl;
    color = qvariant_cast<QColor>(event->mimeData()->colorData());

    data->scenesInfos->at(data->currentSceneInfoIndex)->rois->at(itemIndex)->setColor(color);
    data->scenesInfos->at(data->currentSceneInfoIndex)->rois->at(itemIndex)->setLabel(event->mimeData()->text());    
    data->scenesInfos->at(data->currentSceneInfoIndex)->rois->at(itemIndex)->setLabeled(true);
	data->scenesInfos->at(data->currentSceneInfoIndex)->rois->at(itemIndex)->setLabelId(event->mimeData()->property("id").toInt());
    setToolTip(event->mimeData()->text());

    QTableWidgetItem *labelItem = new QTableWidgetItem(event->mimeData()->text());
    labelItem->setFlags(labelItem->flags() ^ Qt::ItemIsEditable);
    labelItem->setTextAlignment(Qt::AlignCenter);
    roiTable->setItem(itemIndex, 1, labelItem);
    roiTable->selectRow(itemIndex);
    scene()->clearSelection();
    setSelected(true);
	setBrush(Qt::transparent);
    setPen(QPen(QBrush(color), penWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));

    roiList->setCurrentRow(itemIndex);
    QListWidgetItem *roiItem = roiList->currentItem();
    QString itemLabel;
    itemLabel.sprintf("%03d", itemIndex);
    roiItem->setText(event->mimeData()->text() + " " + itemLabel);
    roiItem->setTextColor(color);
	
	((TaggingWidget*)scene()->parent())->updateTreeWidget();

    QGraphicsItem::dropEvent(event);
}

void DiagramItem::wheelEvent(QGraphicsSceneWheelEvent * event) {
    //qDebug() << "item wheelEvent" << endl;
    QGraphicsItem::wheelEvent(event);
}

void DiagramItem::updateItemRow(int w, int h, int tpx, int tpy, int brx, int bry, bool updateTree) {
    QTableWidgetItem *widthItem = new QTableWidgetItem(QString::number(w, 'f', 0));
    widthItem->setFlags(widthItem->flags() ^ Qt::ItemIsEditable);
    widthItem->setTextAlignment(Qt::AlignCenter);

    QTableWidgetItem *heightItem = new QTableWidgetItem(QString::number(h, 'f', 0));
    heightItem->setFlags(heightItem->flags() ^ Qt::ItemIsEditable);
    heightItem->setTextAlignment(Qt::AlignCenter);

    QTableWidgetItem *tpxItem = new QTableWidgetItem(QString::number(tpx, 'f', 0));
    tpxItem->setFlags(tpxItem->flags() ^ Qt::ItemIsEditable);
    tpxItem->setTextAlignment(Qt::AlignCenter);

    QTableWidgetItem *tpyItem = new QTableWidgetItem(QString::number(tpy, 'f', 0));
    tpyItem->setFlags(tpyItem->flags() ^ Qt::ItemIsEditable);
    tpyItem->setTextAlignment(Qt::AlignCenter);

    QTableWidgetItem *brxItem = new QTableWidgetItem(QString::number(brx, 'f', 0));
    brxItem->setFlags(brxItem->flags() ^ Qt::ItemIsEditable);
    brxItem->setTextAlignment(Qt::AlignCenter);

    QTableWidgetItem *bryItem = new QTableWidgetItem(QString::number(bry, 'f', 0));
    bryItem->setFlags(bryItem->flags() ^ Qt::ItemIsEditable);
    bryItem->setTextAlignment(Qt::AlignCenter);

    roiTable->setItem(itemIndex, 2, widthItem);

    roiTable->setItem(itemIndex, 3, heightItem);

    roiTable->setItem(itemIndex, 4, tpxItem);
//        qDebug() << "roi table[1]: " << tpxItem->text() << endl;

    roiTable->setItem(itemIndex, 5, tpyItem);
//        qDebug() << "roi table[2]: " << tpyItem->text() << endl;

    roiTable->setItem(itemIndex, 6, brxItem);
//        qDebug() << "roi table[3]: " << brxItem->text() << endl;

    roiTable->setItem(itemIndex, 7, bryItem);

	qDebug() << "data->currentSceneInfoIndex" << data->currentSceneInfoIndex << endl;
	qDebug() << "data->scenesInfos->at(data->currentSceneInfoIndex)->rois->at(itemIndex)" << data->scenesInfos->at(data->currentSceneInfoIndex)->rois->at(itemIndex) << endl;

	data->scenesInfos->at(data->currentSceneInfoIndex)->rois->at(itemIndex)->setAutomatic(false);
    data->scenesInfos->at(data->currentSceneInfoIndex)->rois->at(itemIndex)->setWidth(w);
    data->scenesInfos->at(data->currentSceneInfoIndex)->rois->at(itemIndex)->setHeight(h);
    data->scenesInfos->at(data->currentSceneInfoIndex)->rois->at(itemIndex)->setTpx(tpx);
    data->scenesInfos->at(data->currentSceneInfoIndex)->rois->at(itemIndex)->setTpy(tpy);
    data->scenesInfos->at(data->currentSceneInfoIndex)->rois->at(itemIndex)->setBrx(brx);
    data->scenesInfos->at(data->currentSceneInfoIndex)->rois->at(itemIndex)->setBry(bry);	

    roiList->setCurrentRow(itemIndex);
    QListWidgetItem *roiItem = roiList->currentItem();

	QPixmap image = QPixmap();
	image.load(data->currentDir.absoluteFilePath(data->scenesInfos->at(data->currentSceneInfoIndex)->imagePath));
    QPixmap roiImage = image.copy(tpx, tpy, w, h).scaledToHeight(h*2);
    QIcon roiIcon(roiImage);
    roiItem->setIcon(roiIcon);

    roiItem->setData(Qt::UserRole+1, tpx);
    roiItem->setData(Qt::UserRole+2, tpy);
    roiItem->setData(Qt::UserRole+3, w);
    roiItem->setData(Qt::UserRole+4, h);

	if(updateTree) {
		((TaggingWidget*)scene()->parent())->updateTreeWidget();
	}
}

void DiagramItem::setSelectedPen() {
    setPen(QPen(QBrush(Qt::yellow), penWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
}

void DiagramItem::setUnselectedPen() {
    setPen(QPen(QBrush(color), penWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
}

//void DiagramItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *styleOption, QWidget *widget) {

//    if(isSelected()) {
//        painter->setPen(QPen(QBrush(Qt::yellow), 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
//        painter->setBrush(Qt::transparent);
//        painter->drawRect(polygon.at(0).x(), polygon.at(0).y(), polygon.at(2).x(), polygon.at(2).y());
//    } else {
//        painter->setPen(QPen(QBrush(color), penWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
//        painter->setBrush(Qt::transparent);
//        painter->drawRect(polygon.at(0).x(), polygon.at(0).y(), polygon.at(2).x(), polygon.at(2).y());
//    }
//    //QGraphicsItem::paint(painter, styleOption, widget);
//}

//bool DiagramItem::sceneEvent(QEvent * event) {
//    qDebug() << "scene event!" << endl;
//    QGraphicsItem::sceneEvent(event);
//    return true;
//}
