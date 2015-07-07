#ifndef GTMAINWINDOW_H
#define GTMAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QPlainTextEdit>

#include "gtprojectdata.h"
#include "taggingwidget.h"
#include "newgtprojectwizard.h"
#include "fileprocessor.h"
#include "xmlprocessor.h"

namespace Ui {
class GTMainWindow;
}

class GTMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GTMainWindow(QWidget *parent = 0);
    ~GTMainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void about();
    void documentWasModified();
	void newProjectWizardFinished(int result);

private:
    Ui::GTMainWindow *ui;
	GTProjectData *data;
	FileProcessor *fileProcessor;
	XMLProcessor *xmlProcessor;
	QString openGTProjectPath;

	void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

	TaggingWidget *taggingWidget;    
    QPlainTextEdit *textEdit;
	NewGTProjectWizard *newProjectWizard;
    QString curFile;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
	QAction *closeAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
};

#endif // GTMAINWINDOW_H
