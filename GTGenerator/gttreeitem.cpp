#include "gttreeitem.h"

GTTreeItem::GTTreeItem()
{
	data = GTProjectData::Instance();
}

void GTTreeItem::setFrameId(const int &f) {
	frameId = f;
}
	 
void GTTreeItem::setFrameImage(const QPixmap &f){
	frameImage = f;
}

void GTTreeItem::setFrameFilename(const QString &f) {
	frameFilename = f;
}
	 
void GTTreeItem::setParent(const bool &p){
	parent = p;
}
	 
void GTTreeItem::setRoiLabelsStatus(const RoiLabelsStatus &r){
	roiLabelsStatus = r;
}
	 
void GTTreeItem::setParentId(const int &p){
	parentId = p;
}
     
void GTTreeItem::setRoiLabelsStatusColor(const QColor &c){
	roiLabelsStatusColor = c;
}