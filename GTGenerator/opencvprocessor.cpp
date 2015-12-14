#include "opencvprocessor.h"

#define qApp (static_cast<QApplication *>(QCoreApplication::instance()))
QProgressDialog *progressDialog;

void calculateHistogram(Mat Im_in, int Im_type, int bins,Mat &HistR, bool vis, char *plotname, int blackValue);
void computeShapeDescriptors(Mat A, vector<float> &output, bool vis);

OpenCVProcessor::OpenCVProcessor()
{
	data = GTProjectData::Instance();
}

OpenCVProcessor::~OpenCVProcessor()
{

}

void notifyBGSProgress(std::string label, int value, int total) {
	//progressDialog->setRange(0, total);
	//progressDialog->setValue(value);
	//progressDialog->setLabelText(QObject::tr(label.c_str()).arg(value).arg(total));
	progressDialog->setLabelText(QObject::tr(label.c_str()));
	//qDebug() << "notifyBGSProgress" <<QObject::tr(label.c_str()).arg(value).arg(total) << endl;
	qApp->processEvents();
}

vector<vector<float>> Mat2Vector(Mat A) {
	vector<vector<float>> B;
	vector<float> aux;

	if(A.size>0)
	{
		for(int i=0; i<A.rows; i++)
		{
			aux.clear();
			for(int j=0; j<A.cols; j++)
			{
				aux.push_back( A.at<float>(i,j));
			}
			B.push_back(aux);
		}
	}
	else
		cout<<"Sample size must be >0";

	return B;
}

void calculateHistogram(Mat Im_in, int Im_type, int bins,Mat &HistR, bool vis, char *plotname, int blackValue) {
	Mat input = Im_in.clone();

	if (Im_type == 1)
		cvtColor(input, input,CV_BGR2HSV);

	/// Separate the image in 3 places ( B, G and R ) or (H, S and V)
	vector<Mat> image_planes;
	split(input, image_planes );

	/// Establish the number of bins
	int histSize = bins;
	bool uniform = true; bool accumulate = false;
	Mat ch1_hist, ch2_hist, ch3_hist;

	/// Set the ranges ( for B,G,R) )
	if(Im_type == 0)
	{
		float range[] = { blackValue, 255 } ;
		const float* histRange = { range };

		/// Compute the histograms:
		calcHist( &image_planes[0], 1, 0, Mat(), ch1_hist, 1, &histSize, &histRange, uniform, accumulate );
		calcHist( &image_planes[1], 1, 0, Mat(), ch2_hist, 1, &histSize, &histRange, uniform, accumulate );
		calcHist( &image_planes[2], 1, 0, Mat(), ch3_hist, 1, &histSize, &histRange, uniform, accumulate );

	}
	else if( Im_type == 1)
	{
		float H_range[] = { blackValue,180};
		float S_range[] = { blackValue, 255 } ;
		float V_range[] = { blackValue, 255};

		const float* histRangeH = { H_range };
		const float* histRangeS = { S_range };
		const float* histRangeV = { V_range };

		/// Compute the histograms:
		calcHist( &image_planes[0], 1, 0, Mat(), ch1_hist, 1, &histSize, &histRangeH, uniform, accumulate );
		calcHist( &image_planes[1], 1, 0, Mat(), ch2_hist, 1, &histSize, &histRangeS, uniform, accumulate );
		calcHist( &image_planes[2], 1, 0, Mat(), ch3_hist, 1, &histSize, &histRangeV, uniform, accumulate );
	}


	// Draw the histograms for B, G and R
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound( (double) hist_w/histSize );

	Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(ch1_hist, ch1_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(ch2_hist, ch2_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(ch3_hist, ch3_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );


	HistR = Mat::zeros(3,bins,ch3_hist.type());
	

	for (int k = 0;k<bins; k++)
	{
		HistR.at<float>(0,k) = ch1_hist.at<float>(k,0);
		HistR.at<float>(1,k) = ch2_hist.at<float>(k,0);
		HistR.at<float>(2,k) = ch1_hist.at<float>(k,0);
	}


	if(vis)
	{
		/// Draw for each channel
		for( int i = 1; i < histSize; i++ )
		{
			line( histImage, Point( bin_w*(i-1), hist_h - cvRound(ch1_hist.at<float>(i-1)) ) ,
				Point( bin_w*(i), hist_h - cvRound(ch1_hist.at<float>(i)) ),
				Scalar( 255, 0, 0), 2, 8, 0  );
			line( histImage, Point( bin_w*(i-1), hist_h - cvRound(ch2_hist.at<float>(i-1)) ) ,
				Point( bin_w*(i), hist_h - cvRound(ch2_hist.at<float>(i)) ),
				Scalar( 0, 255, 0), 2, 8, 0  );
			line( histImage, Point( bin_w*(i-1), hist_h - cvRound(ch3_hist.at<float>(i-1)) ) ,
				Point( bin_w*(i), hist_h - cvRound(ch3_hist.at<float>(i)) ),
				Scalar( 0, 0, 255), 2, 8, 0  );
		}
		/// Display
		namedWindow(plotname, CV_WINDOW_AUTOSIZE );
		imshow(plotname, histImage );
	}
}

void computeShapeDescriptors(Mat A, vector<float> &output, bool vis) {
	vector<vector<cv::Point>> contours;
	vector<cv::Vec4i> hierarchy;	

	Mat A_split[3];
	split(A,A_split);
	//qDebug() << "-- after split" << endl;

	findContours(A_split[0], contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	//qDebug() << "-- after findContours" << endl;

	//qDebug() << "-- contours.size()" << contours.size() << endl;
	
	if(contours.size() > 0) {
		vector<vector<int>> hull( contours.size() );
		vector<vector<Vec4i>> convDef(contours.size() );
		vector<vector<Point>> hull_points(contours.size());
		vector<vector<Point>> defect_points(contours.size());
		Mat drawing = Mat::zeros( A.size(), CV_8UC3 );

		//qDebug() << "-- after definitions" << endl;

		int max_c = 0;

		//Check for the biggest contour inside the ROI
		for(int j=0; j<contours.size(); j++)
		{
			if(contours[j].size()>max_c)
				max_c = contours[j].size();
		}

		//qDebug() << "-- after first for" << endl;

		vector<float> dist;
		for (int i = 0; i <contours.size(); i++)
		{
			//qDebug() << "-- in second for " << i << endl;

			//qDebug() << "-- contours[i].size() " << contours[i].size() << endl;

			if(contours[i].size()==max_c)
			{				
				// Find the convex hull object for each contour
				convexHull(contours[i], hull[i]);
				//qDebug() << "-- after convexHull"<< endl;

				/*for(int xyh=0;i<hull[i].size(); xyh++) {
					qDebug() << "hull[" << xyh << "] " << QString::number(hull[i].at(i)) << endl;
				}*/
				if(hull[i].size() >= 3) {				
					//qDebug() << "hull[i].size()" << hull[i].size() << endl;
					//qDebug() << "hull[" << i << "] " << hull[i][0] << endl;

					convexityDefects(contours[i], hull[i], convDef[i]);
					//qDebug() << "-- after convexityDefects"<< endl;
			
					for(int k=0;k<hull[i].size();k++)
					{           
						int ind=hull[i][k];
						hull_points[i].push_back(contours[i][ind]);
					}

					for(int k=0;k<convDef[i].size();k++)
					{           
						if(convDef[i][k][3]>256)
						{
							dist.push_back(float(convDef[i][k][3]/256));
							int ind_0=convDef[i][k][0];
							int ind_1=convDef[i][k][1];
							int ind_2=convDef[i][k][2];
							defect_points[i].push_back(contours[i][ind_2]);
							if (vis)
							{
								cv::circle(drawing,contours[i][ind_0],5,Scalar(0,255,0),-1);
								cv::circle(drawing,contours[i][ind_1],5,Scalar(0,255,0),-1);
								cv::circle(drawing,contours[i][ind_2],5,Scalar(0,0,255),-1);
								cv::line(drawing,contours[i][ind_2],contours[i][ind_0],Scalar(0,0,255),1);
								cv::line(drawing,contours[i][ind_2],contours[i][ind_1],Scalar(0,0,255),1);
							}
						}
					}
					if(vis)
					{
						drawContours( drawing, contours, i, Scalar(0,255,0), 1, 8, vector<Vec4i>(), 0, Point() );
						drawContours( drawing, hull_points, i, Scalar(255,0,0), 1, 8, vector<Vec4i>(), 0, Point() );
					}
				}
				
			}
			if(vis)
			{
				namedWindow( "Hull demo",cv::WINDOW_AUTOSIZE );
				imshow( "Hull demo", drawing );
			}
		}
		if(dist.size()!=0)
		{
			float scale = float(std::max(A_split[0].cols, A_split[0].rows));
			float mean = 0;
			float std = 0;
			for (int i = 0; i< dist.size();i++)
				mean += dist.at(i);
			mean = mean/(dist.size()*scale);

			for ( int i = 0; i<dist.size();i++)
				std += pow(dist.at(i) - mean,2);

			std = std/dist.size();
			std = (sqrt(std)/scale);

			float imax = *std::max_element(dist.begin(),dist.end());
			imax = imax/scale;

			output.push_back(mean);
			output.push_back(std);
			output.push_back(dist.size());
			output.push_back(imax);
		}
		else
		{
			output.push_back(0);
			output.push_back(0);
			output.push_back(0);
			output.push_back(0);
		}
	}	
}

QImage OpenCVProcessor::cvMatToQImage( const cv::Mat &inMat ) {
	switch ( inMat.type() )
	{
		// 8-bit, 4 channel
	case CV_8UC4:
		{
			QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );

			return image;
		}

		// 8-bit, 3 channel
	case CV_8UC3:
		{
			QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );

			return image.rgbSwapped();
		}

		// 8-bit, 1 channel
	case CV_8UC1:
		{
			static QVector<QRgb>  sColorTable;

			// only create our color table once
			if ( sColorTable.isEmpty() )
			{
				for ( int i = 0; i < 256; ++i )
					sColorTable.push_back( qRgb( i, i, i ) );
			}

			QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );

			image.setColorTable( sColorTable );

			return image;
		}

	default:
		qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
		break;
	}

	return QImage();
}

QPixmap OpenCVProcessor::cvMatToQPixmap( const cv::Mat &inMat ) {
	return QPixmap::fromImage( cvMatToQImage( inMat ) );
}

cv::Mat OpenCVProcessor::QImageToCvMat( const QImage &inImage, bool inCloneImageData) {
	switch ( inImage.format() )
	{
		// 8-bit, 4 channel
	case QImage::Format_RGB32:
		{
			cv::Mat  mat( inImage.height(), inImage.width(), CV_8UC4, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine() );

			return (inCloneImageData ? mat.clone() : mat);
		}

		// 8-bit, 3 channel
	case QImage::Format_RGB888:
		{
			if ( !inCloneImageData )
				qWarning() << "ASM::QImageToCvMat() - Conversion requires cloning since we use a temporary QImage";

			QImage   swapped = inImage.rgbSwapped();

			return cv::Mat( swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar*>(swapped.bits()), swapped.bytesPerLine() ).clone();
		}

		// 8-bit, 1 channel
	case QImage::Format_Indexed8:
		{
			cv::Mat  mat( inImage.height(), inImage.width(), CV_8UC1, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine() );

			return (inCloneImageData ? mat.clone() : mat);
		}

	default:
		qWarning() << "ASM::QImageToCvMat() - QImage format not handled in switch:" << inImage.format();
		break;
	}

	return cv::Mat();
}

// If inPixmap exists for the lifetime of the resulting cv::Mat, pass false to inCloneImageData to share inPixmap's data
// with the cv::Mat directly
//    NOTE: Format_RGB888 is an exception since we need to use a local QImage and thus must clone the data regardless
cv::Mat OpenCVProcessor::QPixmapToCvMat( const QPixmap &inPixmap, bool inCloneImageData) {
	return QImageToCvMat( inPixmap.toImage(), inCloneImageData );
}

void OpenCVProcessor::setProgressDialog(QProgressDialog *dialog) {
	progressDialog = dialog;
}

double OpenCVProcessor::saveFramesFromVideo(QString videoPath, QString framesPath) {	
	string escaped_videoPath = boost::replace_all_copy(videoPath.toStdString(), "/", "\\");

	VideoCapture cap(escaped_videoPath); // open the video file for reading

    if ( !cap.isOpened() )  // if not success, exit program
    {
         qDebug() << "Cannot open the video file: " << QString::fromStdString(escaped_videoPath) << endl;
    }

    //cap.set(CV_CAP_PROP_POS_MSEC, 300); //start the video at 300ms

    double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video
	int length = int(cap.get(CV_CAP_PROP_FRAME_COUNT));

	progressDialog->show();
    progressDialog->setCancelButtonText(tr("&Cancel"));
    progressDialog->setRange(0, length);
    progressDialog->setWindowTitle(tr("Saving frames for video..."));

    qDebug() << "Frame per seconds : " << fps << endl;
	
	int frameCounter = 0;

    while(1) {
		frameCounter++;
        Mat frame;

		progressDialog->setValue(frameCounter);
		progressDialog->setLabelText(tr("Writing frame %1 of %2...").arg(frameCounter).arg(length));  

        bool bSuccess = cap.read(frame); // read a new frame from video

         if (!bSuccess) //if not success, break loop
        {
                       qDebug() << "Cannot read the frame from video file" << endl;
                       break;
        }

        //imshow("MyVideo", frame); //show the frame in "MyVideo" window
		 QString frameFilename;
		 frameFilename.sprintf("frame%04d.png", frameCounter);
		 QString framePath = framesPath + "\\" + frameFilename;

		 imwrite(framePath.toStdString(), frame);
		 qApp->processEvents();
    }
	progressDialog->hide();
	return fps;
}

void OpenCVProcessor::computeBGSModel(QString framesPath, bool loadPreviousModel, int iteration) {
	if(progressDialog == NULL) {
		qDebug() << "Please define a progressDialog!" << endl;
		return;
	}

	if (progressDialog->wasCanceled()) {
		progressDialog->hide();
		return;
	}
	
	progressDialog->setLabelText(tr("Initializing..."));
	progressDialog->show();

	static float pminArea = 0.0003;

	QDir framesDir = QDir(framesPath);

    QStringList framesFileNames;

    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg";

    framesFileNames = framesDir.entryList(filters, QDir::Files | QDir::NoSymLinks);   
	//progressDialog->setRange(0, framesFileNames.size());
	progressDialog->setValue(framesFileNames.size()*(iteration-1));
	progressDialog->setLabelText(tr("Computing initial model..."));

	progressDialog->show();

	cv::Mat oCurrInputFrame, oCurrSegmMask, oCurrReconstrBGImg;			

	// create BGS Subsense object
	BackgroundSubtractorSuBSENSE oBGSAlg;

	// copy loadvars flag
	qDebug() << "video_path filename: " << framesDir.dirName() << endl;

	ostringstream load_codebook_paramters_path;
	load_codebook_paramters_path << framesDir.absolutePath().toStdString() << "\\bgs\\" << QString::number(iteration-1).toStdString() << "\\cparameters.dat";
	qDebug() << "cparameters filename: " << QString::fromStdString(load_codebook_paramters_path.str()) << endl;
		
	oBGSAlg.setBGSProgressFunction(notifyBGSProgress);
	oBGSAlg.saveCodebookParametersPath(load_codebook_paramters_path.str());

	if(loadPreviousModel && QFile(QString::fromStdString(load_codebook_paramters_path.str())).exists()) {
		oBGSAlg.loadvars = true;
		qDebug() << "oBGSAlg.loadvars = true" << endl;
	} else {
		oBGSAlg.loadvars = false;
		qDebug() << "oBGSAlg.loadvars = false" << endl;
	}	

	oCurrInputFrame = cv::imread(framesDir.absoluteFilePath(framesFileNames[0]).toStdString());
	// Initialize Subsense variables
	oCurrSegmMask.create(oCurrInputFrame.size(), CV_8UC1);
	oCurrReconstrBGImg.create(oCurrInputFrame.size(), oCurrInputFrame.type());

	cv::Mat R = cv::Mat(oCurrInputFrame.size(),CV_8UC1,cv::Scalar_<uchar>(255));

	progressDialog->setValue(1 + framesFileNames.size()*(iteration-1));
	progressDialog->setLabelText(tr("Computing BGS model, iteration %3, for frame %1 of %2...").arg(1).arg(framesFileNames.size()).arg(iteration));
	qApp->processEvents();

	// Initialize Subsense	
	if(loadPreviousModel) {
		progressDialog->setLabelText(tr("Loading previous computed BGS model..."));
	} else {
		progressDialog->setLabelText(tr("Initializing BGS..."));
	}

	//qApp->processEvents();
	oBGSAlg.initialize(oCurrInputFrame, R);
	qApp->processEvents();

	// create visualization windows
    //cv::namedWindow("input",cv::WINDOW_AUTOSIZE);
    //cv::namedWindow("segmentation mask",cv::WINDOW_AUTOSIZE);

	int roi_counter = 0;
	int frame_counter = 0;

	for (int f=0; f<framesFileNames.size(); f++) {
		oCurrInputFrame = cv::imread(framesDir.absoluteFilePath(framesFileNames[f]).toStdString());

		if(oCurrInputFrame.empty())
			return;

		if (progressDialog->wasCanceled())
			return;

		// Process
		oBGSAlg(oCurrInputFrame, oCurrSegmMask);
		oBGSAlg.getBackgroundImage(oCurrReconstrBGImg);

		QDir bgsFramesDir = QDir(framesDir.absolutePath() + "\\bgs\\" + QString::number(iteration));

		if(!bgsFramesDir.exists()) {
			if(bgsFramesDir.mkpath(bgsFramesDir.path())) {
				qDebug() << "creating dir " << bgsFramesDir << endl;
			} else {
				qDebug() << "cannot create dir " << bgsFramesDir << endl;
			}
		}

		/*QString bgsImageLabel;
		bgsImageLabel.sprintf("background%04d.png", f+1);
		imwrite(bgsFramesDir.path().toStdString() + "\\" + bgsImageLabel.toStdString(), oCurrReconstrBGImg);*/

		QString maskImageLabel;
		maskImageLabel.sprintf("mask%04d.png", f+1);
		imwrite(bgsFramesDir.path().toStdString() + "\\" + maskImageLabel.toStdString(), oCurrSegmMask);

		//qDebug() << "bgs for frame " << f << endl;
		//progressDialog->setRange(0, framesFileNames.size());
		progressDialog->setValue((f+1) + framesFileNames.size()*(iteration-1));
		progressDialog->setLabelText(tr("Computing BGS model, iteration %3, for frame %1 of %2...").arg(f+1).arg(framesFileNames.size()).arg(iteration));
		qApp->processEvents();
	}

	progressDialog->setLabelText(tr("Saving BGS model to disk..."));
	
	ostringstream save_codebook_paramters_path;
	save_codebook_paramters_path << framesDir.absolutePath().toStdString() << "\\bgs\\" << QString::number(iteration).toStdString() << "\\cparameters.dat";
	qDebug() << "cparameters filename: " << QString::fromStdString(save_codebook_paramters_path.str()) << endl;
		
	oBGSAlg.saveCodebookParametersPath(save_codebook_paramters_path.str());

	oBGSAlg.saveVariables();	
	qDebug() << "bgs finished!" << endl;
	//progressDialog->hide();
}

void OpenCVProcessor::computeSURFDescriptors(const Mat &img, int frameId, int roiId, QString labelsFilename) {
	double hessThresh = 400.0;  // por defecto 400;
	int nOctaves = 3;  // por defecto 3
	int nLayers = 2;
	bool extended = true;
	bool upright = true;  // por defecto true
	Mat Desc_Mat;
	vector<KeyPoint> keys;

	//Set detector
	cv::SURF detector(hessThresh, nOctaves, nLayers, extended, upright);

	//Set ROI mask for detector
	cv::Mat Fmask = Mat::ones(img.rows, img.cols, CV_8UC1);		

	//Detect keypoints
	detector(img, Fmask, keys);

	//Compute descriptors
	detector.compute(img, keys, Desc_Mat);

	//Convert descriptors to vector
	vector<vector<float>> Desc = Mat2Vector(Desc_Mat);

	int nKeys = keys.size();

	if(nKeys > 0) {
		QFile file(labelsFilename);

		if (file.open(QIODevice::Append)) {
			QTextStream stream(&file);		
			QString descriptorLine;					

			// Informacion de ROIs desde Ground Truth
			for (int i = 0; i < nKeys; ++i) {
				descriptorLine.sprintf("%03d ", frameId);
				stream << descriptorLine;

				descriptorLine.sprintf("%02d ", roiId);
				stream << descriptorLine;

				descriptorLine.sprintf("%f %f %f ", keys[i].pt.x, keys[i].pt.y, keys[i].size);
				stream << descriptorLine;

				vector<float> descriptors = Desc.at(i);
				for(int j = 0; j<descriptors.size(); j++) {
					descriptorLine.sprintf("%f ", descriptors.at(j));
					stream << descriptorLine;
				}

				stream << endl;
			}			
		}		
    }	
}

void OpenCVProcessor::computeShapeAndColorDescriptors(const Mat &img, int frameId, int roiId, QString labelsFilename, int blackValue) {
	// HU moments
	Mat ImC1;
	cvtColor(img, ImC1,COLOR_BGR2GRAY);
	Moments momentHU = moments(ImC1,true);
	double hum[7]={0};
	HuMoments(momentHU, hum);
	//qDebug() << "-- after HuMoments" << endl;

	// HSV histograms
	Mat H_RGB;
	char histHSV[50];
	strcpy_s(histHSV,"histHSV");
	calculateHistogram(img, 1, 16, H_RGB, false, histHSV, blackValue);
	//qDebug() << "-- after histHSV" << endl;

	// BGR histograms
	Mat H_HSV;
	char histBGR[50];
	strcpy_s(histBGR,"histBGR");
	calculateHistogram(img, 0, 16, H_HSV, false, histBGR, blackValue);
	//qDebug() << "-- after histBGR" << endl;

	//Shape Descriptors 
	vector<float> key_shape;
	computeShapeDescriptors(img, key_shape, false);
	//qDebug() << "-- after inner computeShapeDescriptors" << endl;

	QFile file(labelsFilename);

	if (file.open(QIODevice::Append)) {
		QTextStream stream(&file);		
		QString descriptorLine;

		descriptorLine.sprintf("%03d ", frameId);
		stream << descriptorLine;

		descriptorLine.sprintf("%02d ", roiId);
		stream << descriptorLine;

		for(int i = 0; i<H_RGB.cols; i++) {
			for (int j = 0; j < H_RGB.rows; j++) {
				descriptorLine.sprintf("%.3f ",H_RGB.at<float>(j,i));
				stream << descriptorLine;
			}
		}

		for(int i = 0; i<H_HSV.cols; i++) {
			for (int j = 0; j < H_HSV.rows; j++) {
				descriptorLine.sprintf("%.3f ",H_HSV.at<float>(j,i));
				stream << descriptorLine;
			}
		}

		for (int i = 0; i< key_shape.size(); i++) {
			descriptorLine.sprintf("%.3f ", key_shape.at(i));
			stream << descriptorLine;
		}

		stream << endl;
	}
}

void OpenCVProcessor::saveThumbnailsFromVideoFrames(const QStringList &files) {
	QDir thumbnailsDir = QDir(data->currentDir.absolutePath() + "\\thumbnails");

	if(!thumbnailsDir.exists()) {
		if(thumbnailsDir.mkpath(thumbnailsDir.path())) {
			qDebug() << "creating dir " << thumbnailsDir << endl;
		} else {
			qDebug() << "cannot create dir " << thumbnailsDir << endl;
		}
	}

	if(thumbnailsDir.exists()) {
		progressDialog->show();
		progressDialog->setCancelButtonText(tr("&Cancel"));
		progressDialog->setRange(0, files.size());
		progressDialog->setWindowTitle(tr("Processing thumbnails..."));

		vector<int> compression_params;
		compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
		compression_params.push_back(9);		

		int thumbnail_height = 100;		

		Mat original, thumbnail;
		original = imread(data->currentDir.absoluteFilePath(files[0]).toStdString());			

		double aspect_ratio = (double)original.cols/(double)original.rows;
		int thumbnail_width = aspect_ratio*thumbnail_height;
		
		resize(original, thumbnail, Size(thumbnail_width, thumbnail_height), 0, 0, INTER_AREA);
		imwrite(thumbnailsDir.path().toStdString() + "\\" + files[0].toStdString(), thumbnail, compression_params);
		
		thumbnail.release();
		original.release();

		progressDialog->setValue(1);
        progressDialog->setLabelText(tr("Saving thumbnail number %1 of %2...").arg(1).arg(files.size()));

		for (int i = 1; i < files.size(); ++i) {		
			original = imread(data->currentDir.absoluteFilePath(files[i]).toStdString());
			resize(original, thumbnail, Size(thumbnail_width, thumbnail_height), 0, 0, INTER_AREA);
			imwrite(thumbnailsDir.path().toStdString() + "\\" + files[i].toStdString(), thumbnail, compression_params);
			thumbnail.release();
			original.release();
			progressDialog->setValue(i+1);
			progressDialog->setLabelText(tr("Saving thumbnail number %1 of %2...").arg(i+1).arg(files.size()));
		}
	}
}