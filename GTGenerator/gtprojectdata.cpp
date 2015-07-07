#include "gtprojectdata.h"

GTProjectData* GTProjectData::_instance = 0;

GTProjectData::GTProjectData() {
	gtProject = new GTProject();
	scenesInfos = new QList<DiagramSceneInfo *>();
	scenesLabels = new QList<DiagramROILabel *>();
	sceneLabelsCounter = 0;
	showingImage = false;

	labelSelected = false;
	currentLabelColor = Qt::white;
	currentLabelString = "--NO LABEL--";
	currentLabelId = 0;

	parentTreeColor = QColor(255,255,255); //white
	parentTreeTextColor = QColor(0,0,0); //black
	childTreeColor = QColor(192,192,192); //silver
	childTreeTextColor = QColor(0,0,0); //black

	noRoisColor = QColor(255,69,0); //orange red
	manuallyRoisUnlabeledColor = QColor(255,165,0); //orange 
	manuallyRoisLabeledColor = QColor(0,255,0); //lime
	automaticRoisUnlabeledColor = QColor(0,255,255); //cyan
	automaticRoisLabeledColor = QColor(0,139,139); //dark cyan
	reviewFrameLabelsColor = QColor(255,20,147); //deep pink

	subsampledParentFrameCopyOptions = QMap<RoiCopyOption, QString>();
	subsampledParentFrameCopyOptions.insert(COPY_TO_SUMSAMPLED_FRAMES, "copy to subsampled frames");
	subsampledParentFrameCopyOptions.insert(COPY_TO_NEXT_PARENT_FRAME, "copy to next parent frame");
	subsampledParentFrameCopyOptions.insert(COPY_TO_PARENT_FRAMES, "copy to all parent frames");
	subsampledParentFrameCopyOptions.insert(COPY_UNTIL_LAST_FRAME, "copy until last frame");

	subsampledChildFrameCopyOptions = QMap<RoiCopyOption, QString>();
	subsampledChildFrameCopyOptions.insert(COPY_TO_NEXT_FRAME, "copy to next frame");
	//subsampledChildFrameCopyOptions.insert(COPY_FROM_PREVIOUS_FRAME, "copy from previous frame");

	frameCopyOptions = QMap<RoiCopyOption, QString>();
	frameCopyOptions.insert(COPY_TO_NEXT_FRAME, "copy to next frame");
	//frameCopyOptions.insert(COPY_FROM_PREVIOUS_FRAME, "copy from previous frame");
	frameCopyOptions.insert(COPY_UNTIL_LAST_FRAME, "copy until last frame");

	labelsSummary = QMap<QString, QList<DiagramROI*>>();
}

GTProjectData* GTProjectData::Instance() {
    if(!_instance)
        _instance = new GTProjectData;

    return _instance;
}