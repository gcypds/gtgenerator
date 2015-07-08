#ifndef DIAGRAMVIEW_H
#define DIAGRAMVIEW_H
#include <QGraphicsView>
#include "gtprojectdata.h"
#include "diagramscene.h"

class DiagramView : public QGraphicsView
{
public:
    DiagramView( QWidget * parent = 0);
    DiagramView( QGraphicsScene * scene, QWidget * parent = 0);
	DiagramView(bool scrollEnabled, QGraphicsScene * scene, QWidget * parent = 0);
	
	qreal firstX;
	qreal firstY;
	qreal lastX;
	qreal lastY;
	int centerCounter;	
	QPoint initialZoomPoint;
	QPoint averagePoint;	

	void updateZoom();

protected:
    void wheelEvent ( QWheelEvent * event );
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void scrollContentsBy(int dx, int dy);	

private:
    //QGraphicsScene * scene;
	GTProjectData *data;
	bool scrollEnabled;
};

#endif // DIAGRAMVIEW_H
