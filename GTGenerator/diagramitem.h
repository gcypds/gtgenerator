#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QGraphicsPixmapItem>
#include <QList>
#include <QTableWidget>
#include <QListWidget>
#include "gtprojectdata.h"
#include "diagramsceneinfo.h"
#include "diagramroi.h"

QT_BEGIN_NAMESPACE
class QPixmap;
class QGraphicsItem;
class QGraphicsScene;
class QTextEdit;
class QGraphicsSceneMouseEvent;
class QMenu;
class QGraphicsSceneContextMenuEvent;
class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class QPolygonF;
QT_END_NAMESPACE

class Arrow;

//! [0]
class DiagramItem : public QGraphicsPolygonItem
{
public:
    enum { Type = UserType + 15 };
    int itemIndex;
	int labelIndex;
	GTProjectData * data;

    QTableWidget *roiTable;
    QListWidget *roiList;
    //QList<DiagramSceneInfo> *scenesInfos;
    //int currentSceneInfoIndex;

    DiagramItem(int index, QTableWidget *table, QListWidget *list, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    DiagramItem(DiagramROI roi, int index, QTableWidget *table, QListWidget *list, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

	int type() const { return Type;}
    void setSelectedPen();
    void setUnselectedPen();	

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);    
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);

    void focusInEvent(QFocusEvent * event);
    void focusOutEvent(QFocusEvent * event);

    void dragEnterEvent(QGraphicsSceneDragDropEvent * event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent * event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent * event);
    void dropEvent(QGraphicsSceneDragDropEvent * event);

    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent * event);

    void wheelEvent(QGraphicsSceneWheelEvent * event);
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *styleOption, QWidget *widget);
//    bool sceneEvent(QEvent * event);

private:
    QColor color;
    qreal lastSceneXPos;
    qreal lastSceneYPos;
    int selectionResizingStart;
    QPoint initialResizePoint;
    QPoint current_mTopLeftPoint;
    QPoint current_mBottomRightPoint;
    bool initCoords;
    QPolygonF polygon;
	void updateItemRow(int w, int h, int tpx, int tpy, int brx, int bry, bool updateTree);
};
//! [0]

#endif
