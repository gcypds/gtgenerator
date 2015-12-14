#ifndef DIAGRAMSCENEINFO_H
#define DIAGRAMSCENEINFO_H

#include <diagramroi.h>
#include <QPixmap>
#include <QList>

class DiagramSceneInfo
{
public:
    DiagramSceneInfo();
    QList<DiagramROI*> * rois;
    QString imagePath;
	QString bgsMaskPath;
	QString imageAndBgsMaskPath;
    QString imageName;
    QString imageSize;
	int frameWidth;
	int frameHeight;
};

#endif // DIAGRAMSCENEINFO_H
