#include "fileprocessor.h"

#include <algorithm>
#include <string>
#include <iostream>

#include <QDebug>
#include <QFile> 
#include <QDir> 

FileProcessor::FileProcessor()
{

}

FileProcessor::~FileProcessor()
{

}

static const std::string forbiddenChars = " \\~#%&*{}/:<>?|\"-+";

static char clearForbidden(char toCheck) {
    if(forbiddenChars.find(toCheck) != std::string::npos) {
         return '_';
    }
    return toCheck;
}

bool FileProcessor::createDir(QString dirName) {
	if(!QDir(dirName).exists()) {
		if (QDir().mkpath(dirName)) {
			qDebug() << dirName << " created!" << endl;
			return true;
		} else {
			qDebug()  << dirName << " Cannot be created!" << endl;
			return false;
		}
	}

	return true;
}

QString FileProcessor::removeForbiddenChars(QString text) {
	std::string stdLabelName = text.toStdString();
	std::transform(stdLabelName.begin(), stdLabelName.end(), stdLabelName.begin(), clearForbidden);

	return QString::fromStdString(stdLabelName);
}
