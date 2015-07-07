#ifndef GTPROJECT_H
#define GTPROJECT_H

#include <QString>

class GTProject
{

public:
	GTProject();
	
	// From XML
	QString name;
	int frameCount;
	int labelCount;
	QString videoSourcePath;
	bool subsamplingEnabled;
	int subsamplingValue;
	int subsamplingStep;
	bool bgsComputed;
	bool bgsLoaded;
	int bgsIterations;	
	bool descriptorsComputed;

	// Computed
	int roisDrawn;
	int roisFullLabeled;
	int roisLabeled;
	int roisAutoLabeled;

	double fps;

private:
	
};

#endif // GTPROJECT_H
