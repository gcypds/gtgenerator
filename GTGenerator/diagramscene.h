#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include <QGraphicsScene>
#include <QTableWidget>
#include <QListWidget>
#include "gtprojectdata.h"
#include "diagramitem.h"
#include "diagramsceneinfo.h"
#include "diagramroi.h"

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
QT_END_NAMESPACE

//! [0]
class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    DiagramScene(QObject *parent = 0);

    QTableWidget *roiTable;
    QListWidget *roiList;

	GTProjectData *data;
    /*int roiCounter;
    QList<DiagramSceneInfo> *scenesInfos;
    DiagramSceneInfo currentSceneInfo;
    int currentSceneInfoIndex;
    bool showingImage;*/
	
	qreal firstX;
	qreal firstY;
	qreal lastX;
	qreal lastY;
	bool paintingRect;
	bool startDrag;
	bool draggedRect;

	DiagramItem *currentItem;

public slots:    

signals:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void wheelEvent(QGraphicsSceneWheelEvent * event);

private:    

};
//! [0]

#endif
