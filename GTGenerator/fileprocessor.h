#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

// Qt includes
#include <QString>

class FileProcessor
{
public:
	FileProcessor();
	~FileProcessor();

	bool createDir(QString dirName);
	QString removeForbiddenChars(QString text);
private:
	
};

#endif // FILEPROCESSOR_H
