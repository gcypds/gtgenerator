#include <QtGui>

#include "gtprojectdata.h"
#include "taggingwidget.h"
#include "diagramscene.h"
#include "diagramroi.h"

DiagramScene::DiagramScene(QObject *parent) : QGraphicsScene(parent) {
	QFont tooltipFont = QFont("Newyork", 18);

	QToolTip::setFont(tooltipFont);

	data = GTProjectData::Instance();	

	paintingRect = false;
	startDrag = false;
	draggedRect = false;

	//data->scenesInfos = new QList<DiagramSceneInfo>();    
}

//! [6]
void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{    
//    qDebug() << "mousePressEvent" << endl;
//    qDebug() << "sceneRect().width()" << sceneRect().width() << endl;
//    qDebug() << "sceneRect().height()" << sceneRect().height() << endl;

	if(!data->showingImage)
		return;

	firstX = mouseEvent->scenePos().x();
	firstY = mouseEvent->scenePos().y();
	//qDebug() << "firstX: " << firstX << endl;
	//qDebug() << "firstY: " << firstY << endl;

	if (mouseEvent->button() != Qt::LeftButton)
		return;

	if(mouseEvent->scenePos().x() >= 0 && mouseEvent->scenePos().y() >= 0 &&
			mouseEvent->scenePos().x() <= sceneRect().width() && mouseEvent->scenePos().y() <= sceneRect().height()) {

		//qDebug() << "itemAt(QPointF(firstX, firstY))->flags() "  << (!itemAt(QPointF(firstX, firstY))->flags()?true:false)<< endl;
		//qDebug() << "views().at(0)->itemAt(QPointF(lastX, lastY)) "  << views().at(0)->itemAt(QPoint(firstX, firstX))->pos() << endl;

		if(itemAt(QPointF(firstX, firstY)) != NULL && !itemAt(QPointF(firstX, firstY))->flags() && !(mouseEvent->modifiers() & Qt::ControlModifier)) {
			roiTable->clearSelection();
			paintingRect = true;
			startDrag = true;
			draggedRect = false;
	//        qDebug() << "item not found!" << endl;

			currentItem = new DiagramItem(data->roiCounter, roiTable, roiList, NULL, this);
//            qDebug() << "to add item" << endl;
			addItem(currentItem);
		} else {
	//        qDebug() << "item FOUND!" << endl;
		}
	}

	QGraphicsScene::mousePressEvent(mouseEvent);
}
//! [9]

//! [10]
void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	//qDebug() << "mouseMoveEvent on " << mouseEvent->scenePos() << endl;

	if(!data->showingImage)
		return;

	if(mouseEvent->modifiers() & Qt::ShiftModifier) {

		if(mouseEvent->scenePos().x() >= 0 && mouseEvent->scenePos().y() >= 0 &&
				mouseEvent->scenePos().x() <= sceneRect().width() && mouseEvent->scenePos().y() <= sceneRect().height()) {

			QToolTip::showText(mouseEvent->screenPos(),
				QString::number( mouseEvent->scenePos().x() , 'f', 0) + ", " +
				QString::number( mouseEvent->scenePos().y() , 'f', 0));
		} else {
			//QToolTip::hideText();
		}
//        qDebug() << "sceneRect().width()" << sceneRect().width() << endl;
//        qDebug() << "sceneRect().height()" << sceneRect().height() << endl;
	} else {
		//QToolTip::hideText();
	}

	lastX = mouseEvent->scenePos().x();
	lastY = mouseEvent->scenePos().y();
	//qDebug() << "lastX: " << lastX << endl;
	//qDebug() << "lastY: " << lastY << endl;

	//qDebug() << "mouseEvent->button()" << mouseEvent->button() << endl;

	if(paintingRect && startDrag) {
		//qDebug() << "dragging rectangle" << endl;
		draggedRect = true;
		QPolygonF myPolygon;

		myPolygon << QPointF(firstX, firstY)
					<< QPointF(lastX, firstY)
					<< QPointF(lastX, lastY)
					<< QPointF(firstX, lastY)
					<< QPointF(firstX, firstY);

		currentItem->setPolygon(myPolygon);
		currentItem->show();
	}   

	QGraphicsScene::mouseMoveEvent(mouseEvent);

}
//! [10]

//! [11]
void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	//qDebug() << "mouseReleaseEvent" << endl;

	if(!data->showingImage)
		return;

	if(firstX >= 0 && firstY >= 0 && firstX <= sceneRect().width() && firstY <= sceneRect().height()) {

		lastX = mouseEvent->scenePos().x();
		lastY = mouseEvent->scenePos().y();
		//qDebug() << "lastX: " << lastX << endl;
		//qDebug() << "lastY: " << lastY << endl;
		
		if(paintingRect && draggedRect) {

			if((lastX-firstX) > data->minRoiWidth && (lastY-firstY) > data->minRoiHeight) {
				//qDebug() << "adding Rect" << endl;
				QPolygonF myPolygon;

				myPolygon << QPointF(firstX, firstY)
							<< QPointF(lastX, firstY)
							<< QPointF(lastX, lastY)
							<< QPointF(firstX, lastY)
							<< QPointF(firstX, firstY);

				if(currentItem) {
					currentItem->setPolygon(myPolygon);
					currentItem->show();

					data->roiCounter++;

					DiagramROI *roi = new DiagramROI();
					roi->setAutomatic(false);
					roi->setFrameId(data->currentSceneInfoIndex);

					roi->setIndex(data->roiCounter);

					QString itemLabel;
					itemLabel.sprintf("%03d", data->roiCounter);

					QTableWidgetItem *roiNameItem = new QTableWidgetItem(itemLabel);
					roiNameItem->setFlags(roiNameItem->flags() ^ Qt::ItemIsEditable);
					roiNameItem->setTextAlignment(Qt::AlignCenter);

					QString roiLabel = data->currentLabelString;

					QTableWidgetItem *labelItem = new QTableWidgetItem(roiLabel);
					labelItem->setFlags(labelItem->flags() ^ Qt::ItemIsEditable);
					labelItem->setTextAlignment(Qt::AlignCenter);
					roi->setLabel(roiLabel);

					QTableWidgetItem *widthItem = new QTableWidgetItem(QString::number(lastX-firstX, 'f', 0));
					widthItem->setFlags(widthItem->flags() ^ Qt::ItemIsEditable);
					widthItem->setTextAlignment(Qt::AlignCenter);
					roi->setWidth(lastX-firstX);

					QTableWidgetItem *heightItem = new QTableWidgetItem(QString::number(lastY-firstY, 'f', 0));
					heightItem->setFlags(heightItem->flags() ^ Qt::ItemIsEditable);
					heightItem->setTextAlignment(Qt::AlignCenter);
					roi->setHeight(lastY-firstY);

					QTableWidgetItem *tpxItem = new QTableWidgetItem(QString::number(firstX, 'f', 0));
					tpxItem->setFlags(tpxItem->flags() ^ Qt::ItemIsEditable);
					tpxItem->setTextAlignment(Qt::AlignCenter);
					roi->setTpx(firstX);

					QTableWidgetItem *tpyItem = new QTableWidgetItem(QString::number(firstY, 'f', 0));
					tpyItem->setFlags(tpyItem->flags() ^ Qt::ItemIsEditable);
					tpyItem->setTextAlignment(Qt::AlignCenter);
					roi->setTpy(firstY);

					QTableWidgetItem *brxItem = new QTableWidgetItem(QString::number(lastX, 'f', 0));
					brxItem->setFlags(brxItem->flags() ^ Qt::ItemIsEditable);
					brxItem->setTextAlignment(Qt::AlignCenter);
					roi->setBrx(lastX);

					QTableWidgetItem *bryItem = new QTableWidgetItem(QString::number(lastY, 'f', 0));
					bryItem->setFlags(bryItem->flags() ^ Qt::ItemIsEditable);
					bryItem->setTextAlignment(Qt::AlignCenter);
					roi->setBry(lastY);

					int row = roiTable->rowCount();
					roiTable->insertRow(row);
					roiTable->setItem(row, 0, roiNameItem);
			//        qDebug() << "roi table[0]: " << roiNameItem->text() << endl;

					roiTable->setItem(row, 1, labelItem);

					roiTable->setItem(row, 2, widthItem);

					roiTable->setItem(row, 3, heightItem);

					roiTable->setItem(row, 4, tpxItem);
			//        qDebug() << "roi table[1]: " << tpxItem->text() << endl;

					roiTable->setItem(row, 5, tpyItem);
			//        qDebug() << "roi table[2]: " << tpyItem->text() << endl;

					roiTable->setItem(row, 6, brxItem);
			//        qDebug() << "roi table[3]: " << brxItem->text() << endl;

					roiTable->setItem(row, 7, bryItem);
			//        qDebug() << "roi table[4]: " << bryItem->text() << endl;
			
					if(data->labelSelected) {
						roi->setColor(data->currentLabelColor);
						roi->setLabel(data->currentLabelString);
						roi->setLabeled(true);
					}
			
					data->scenesInfos->at(data->currentSceneInfoIndex)->rois->append(roi);

					QListWidgetItem *roiItem = new QListWidgetItem(roiList);
					roiItem->setText(roiLabel + " " + itemLabel);
					roiItem->setTextColor(Qt::black);
					roiItem->setFont(QFont("Newyork", 18));
					roiItem->setData(Qt::UserRole, roi->getIndex());
					roiItem->setData(Qt::UserRole+1, roi->getTpx());
					roiItem->setData(Qt::UserRole+2, roi->getTpy());
					roiItem->setData(Qt::UserRole+3, roi->getWidth());
					roiItem->setData(Qt::UserRole+4, roi->getHeight());
					//roiItem->setBackground(roi->isLabeled()?roi->getColor():Qt::white);
					QPixmap roiImage = data->scenesInfos->at(data->currentSceneInfoIndex)->image->copy(roi->getTpx(), roi->getTpy(), roi->getWidth(), roi->getHeight()).scaledToHeight(roi->getHeight()*2);
					QIcon roiIcon(roiImage);
					roiItem->setIcon(roiIcon);
					roiItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
					roiItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);		

					((TaggingWidget*)parent())->updateTreeWidget();
				}
			} else {
				if(currentItem) {
					removeItem(currentItem);
					delete currentItem;
				}        
			}			
		} else if(paintingRect && !draggedRect) {
	//        qDebug() << "removing item..." << endl;
			if(currentItem) {
				removeItem(currentItem);
				delete currentItem;
			}        
		}	
	}	

//    qDebug() << "---adding loading sceneInfo for " << currentSceneInfoIndex << endl;
//    qDebug() << "---adding scene->scenesInfos->at(scene->currentSceneInfoIndex).rois.size() " << scenesInfos->at(currentSceneInfoIndex).rois->size() << endl;

	paintingRect = false;
	startDrag = false;
	draggedRect = false;

	QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
//! [13]

void DiagramScene::wheelEvent(QGraphicsSceneWheelEvent * event) {
	// qDebug() << "DiagramScene wheelEvent" << endl;
//    if(QApplication::keyboardModifiers() && Qt::ControlModifier) {
//        qDebug() << "control pressed with wheel!" << endl;

//        xWheel += event->delta()/120;
//        qDebug() << "Total Steps: "+QString::number(xWheel) << endl;
//        qreal scale = 1+zoomPercentage*xWheel;

//        qDebug() << "scale: " << scale << endl;

//        QMatrix oldMatrix = views().at(0)->matrix();
//        views().at(0)->resetMatrix();

//        views().at(0)->scale(scale, scale);
//        views().at(0)->translate(oldMatrix.dx(), oldMatrix.dy());
//        views().at(0)->setFocus();
//        qDebug() << "Scaling to: " << 1+zoomPercentage*xWheel << 1+zoomPercentage*xWheel << endl;
//    }

//    if(event->modifiers() & Qt::ControlModifier) {
//        //qDebug() << "control pressed with wheel!" << endl;

//        xWheel += event->delta()/120;
//        //qDebug() << "Total Steps: "+QString::number(xWheel) << endl;
//        qreal scaleValue = 1+zoomPercentage*xWheel;

//        //qDebug() << "scale: " << scaleValue << endl;

//        QMatrix oldMatrix = views().at(0)->matrix();
//        views().at(0)->resetMatrix();

//        views().at(0)->scale(scaleValue, scaleValue);
//        views().at(0)->translate(oldMatrix.dx(), oldMatrix.dy());
//        views().at(0)->setFocus();
//        //qDebug() << "Scaling to: " << 1+zoomPercentage*xWheel << 1+zoomPercentage*xWheel << endl;

//        //QGraphicsScene::wheelEvent(event);
//        if(event->modifiers() & Qt::ShiftModifier) {
//            qDebug() << "plus shift!" << endl;
//            views().at(0)->centerOn(QPoint(0,0));
//        } else {
//            views().at(0)->centerOn(event->scenePos());
//        }
//    } else {
//        //QGraphicsScene::wheelEvent(event);
//    }

//    if(event->modifiers() & Qt::ControlModifier) {
//        qDebug() << "plus control!" << endl;
//        //views().at(0)->centerOn(QPoint(0,0));
//    }
	//else {
//        //views().at(0)->centerOn(event->scenePos());
//        //QGraphicsScene::wheelEvent(event);
//    }

	QGraphicsScene::wheelEvent(event);

}
