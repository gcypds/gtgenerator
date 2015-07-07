#ifndef GTTREEITEM_H
#define GTTREEITEM_H

#include "gtprojectdata.h"
#include "gtenums.h"
#include <QColor>
#include <QPixmap>

class GTTreeItem
{

public:
    GTTreeItem();

    int getFrameId() const { return frameId; }
    void setFrameId(const int &f);

	QPixmap getFrameImage() const { return frameImage; }
    void setFrameImage(const QPixmap &f);

	QString getFrameFilename() const { return frameFilename; }
    void setFrameFilename(const QString &f);

	bool isParent() const { return parent; }
	void setParent(const bool &p);

	RoiLabelsStatus getRoiLabelsStatus() const { return roiLabelsStatus; }
    void setRoiLabelsStatus(const RoiLabelsStatus &r);

	int getParentId() const { return parentId; }
    void setParentId(const int &p);
    
    QColor getRoiLabelsStatusColor() const { return roiLabelsStatusColor; }
    void setRoiLabelsStatusColor(const QColor &c);

private:
    int frameId;
	QPixmap frameImage;
	QString frameFilename;
	bool parent;
	RoiLabelsStatus roiLabelsStatus;
	int parentId;    
    QColor roiLabelsStatusColor;

	GTProjectData * data;
};

#endif // GTTREEITEM_H
