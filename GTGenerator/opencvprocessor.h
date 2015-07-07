#ifndef OPENCVPROCESSOR_H
#define OPENCVPROCESSOR_H

#include <QApplication>
#include <QDir> 
#include <QFile>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QProgressDialog>
 
#include "BackgroundRegions.h"
#include "BackgroundSubtractorSuBSENSE.h"

#include "opencv2/imgproc/types_c.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <iostream>

class OpenCVProcessor : public QObject
{
	Q_OBJECT

public:
	OpenCVProcessor();
	~OpenCVProcessor();

	QImage cvMatToQImage( const cv::Mat &inMat );
	QPixmap cvMatToQPixmap( const cv::Mat &inMat );
	cv::Mat QImageToCvMat( const QImage &inImage, bool inCloneImageData = true );
	cv::Mat QPixmapToCvMat( const QPixmap &inPixmap, bool inCloneImageData = true );
	
	void setProgressDialog(QProgressDialog *dialog);
	double saveFramesFromVideo(QString videoPath, QString framesPath);

	void computeBGSModel(QString framesPath, bool loadPreviousModel, int iteration);		
	void computeSURFDescriptors(const Mat &img, int frameId, int roiId, QString labelsFilename);
	void computeShapeAndColorDescriptors(const Mat &img, int frameId, int roiId, QString labelsFilename, int blackValue);
	
private:
	
};

#endif // OPENCVPROCESSOR_H
