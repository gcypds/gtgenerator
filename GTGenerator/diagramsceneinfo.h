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
    QPixmap *image;
	QPixmap *bgsMask;
	QPixmap *imageAndBgsMask;
    QString imagePath;
    QString imageName;
    QString imageSize;
};

#endif // DIAGRAMSCENEINFO_H
