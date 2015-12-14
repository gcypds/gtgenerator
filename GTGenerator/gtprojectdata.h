#ifndef GTPROJECTDATA_H
#define GTPROJECTDATA_H

#include <QColor>
#include <QDir>
#include <QList>
#include <QMap>
#include "gtenums.h"
#include "gtproject.h"
#include "diagramroi.h"
#include "diagramsceneinfo.h"
#include "diagramroilabel.h"

class GTProjectData {

public:	
	static GTProjectData * Instance();	

	static const int minRoiWidth = 15;
	static const int minRoiHeight = 15;
	static const int autoSaverFreqSeconds = 60;

	GTProject *gtProject;
	int roiCounter;
    QList<DiagramSceneInfo *> *scenesInfos;
	QList<DiagramROILabel *> *scenesLabels;
	int sceneLabelsCounter;
    DiagramSceneInfo currentSceneInfo;
    int currentSceneInfoIndex;
    bool showingImage;
	int currentLabelId;
	bool labelSelected;
	QColor currentLabelColor;
	QString currentLabelString;

	QColor parentTreeColor;
	QColor parentTreeTextColor;
	QColor childTreeColor;
	QColor childTreeTextColor;

	QColor noRoisColor;
	QColor manuallyRoisUnlabeledColor;
	QColor manuallyRoisLabeledColor;
	QColor automaticRoisUnlabeledColor;
	QColor automaticRoisLabeledColor;
	QColor reviewFrameLabelsColor;	

	QMap<RoiCopyOption, QString> subsampledParentFrameCopyOptions;
	QMap<RoiCopyOption, QString> subsampledChildFrameCopyOptions;
	QMap<RoiCopyOption, QString> frameCopyOptions;

	QMap<QString, QList<DiagramROI*>> labelsSummary;

	int xWheel;
	qreal zoomPercentage;
	qreal zoomOffsetOrigin;
	int centerResolution;
	qreal scaleValue;

	QDir currentDir;

private:
	GTProjectData();

	static GTProjectData * _instance;			
};

#endif // GTPROJECTDATA_H
