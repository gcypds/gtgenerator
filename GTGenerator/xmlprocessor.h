#ifndef XMLPROCESSOR_H
#define XMLPROCESSOR_H

#include "diagramsceneinfo.h"
#include "diagramroilabel.h"
#include "gtproject.h"

class XMLProcessor
{
public:
	XMLProcessor();
	~XMLProcessor();

	void saveRoisToXML(QList<DiagramSceneInfo *> *scenesInfos, QString xmlPath, int paddingPx, QString videoName);
	void readRoisFromXML(QList<DiagramSceneInfo *> *scenesInfos, QString xmlPath);

	void saveLabelsToXML(QList<DiagramROILabel *> *labels, QString xmlPath);
	void readLabelsFromXML(QList<DiagramROILabel *> *labels, QString xmlPath);

	void saveGTProjectToXML(GTProject *project, QString xmlPath);
	void readGTProjectFromXML(GTProject *project, QString xmlPath);

private:
	
};

#endif // XMLPROCESSOR_H
