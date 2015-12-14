#include "gtmainwindow.h"
#include "ui_gtmainwindow.h"

#include <QtGui>
#include <QDate>

GTMainWindow::GTMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::GTMainWindow) {
	ui->setupUi(this);

	data = GTProjectData::Instance();
	fileProcessor = new FileProcessor();
	xmlProcessor = new XMLProcessor();

	//textEdit = new QPlainTextEdit();

	//ui->gtStatusWidget->setVisible(false);

	createActions();
	//createMenus();
	createToolBars();
	//createStatusBar();

	//readSettings();

	//connect(textEdit->document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));	

	//setCurrentFile("");
	//setUnifiedTitleAndToolBarOnMac(true);    	
	delete ui->statusbar;
	/*taggingWidget = new TaggingWidget();
	setCentralWidget(taggingWidget);*/
	ui->gtStatusWidget->setVisible(false);
}

GTMainWindow::~GTMainWindow(){
	delete ui;
}

void GTMainWindow::closeEvent(QCloseEvent *event) {
	/*if (maybeSave()) {
		writeSettings();
		event->accept();
	} else {
		event->ignore();
	}*/
	QMainWindow::close();
}

void GTMainWindow::newFile() {
	//qDebug() << "window width: " << width() << endl;
	//gtProjectWidget = new GTProjectWidget(width());
	newProjectWizard = new NewGTProjectWizard();
	connect(newProjectWizard, SIGNAL(finished(int)), this, SLOT(newProjectWizardFinished(int)));
	newProjectWizard->show();
    //setCentralWidget(newProjectWizard);
}

void GTMainWindow::open() {
	openGTProjectPath = QFileDialog::getOpenFileName(this, tr("Open GTProject"), ".", tr("GTProject files (*.gtp)"));
	if (!openGTProjectPath.isEmpty()) {
		xmlProcessor->readGTProjectFromXML(data->gtProject, openGTProjectPath);
		ui->gtProjectName_title->setFont(QFont("Newyork", 10, QFont::Bold));
		ui->gtProjectName_title->setText(data->gtProject->name);

		taggingWidget = new TaggingWidget();
		QFileInfo fileInfo = QFileInfo(openGTProjectPath);
		taggingWidget->selectGTProject(fileInfo.dir().path());
		taggingWidget->loadData();		
		setCentralWidget(taggingWidget);

		ui->gtStatusWidget->setVisible(true);
		fileToolBar->addWidget(ui->gtStatusWidget);
	}
}

bool GTMainWindow::save() {
	/*QString fileName = QFileDialog::getSaveFileName(this, tr("Save GTProject"), data->gtProject->name+".gtp", tr("GTProject files (*.gtp)"));
	if (fileName.isEmpty())
		return false;*/

	if(data->currentDir.path() != NULL && !data->currentDir.path().isEmpty()) {
		xmlProcessor->saveGTProjectToXML(data->gtProject, data->currentDir.path()+"\\"+data->gtProject->name+".gtp");
		QFileInfo fileInfo = QFileInfo(openGTProjectPath);
		taggingWidget->saveData();
	}	

	return true;
}

bool GTMainWindow::saveAs() {
	/*QString fileName = QFileDialog::getSaveFileName(this, tr("Save GTProject"), data->gtProject->name+".gtp", tr("GTProject files (*.gtp)"));
	if (fileName.isEmpty())
		return false;*/

	xmlProcessor->saveGTProjectToXML(data->gtProject, openGTProjectPath);
	QFileInfo fileInfo = QFileInfo(openGTProjectPath);
	taggingWidget->selectGTProject(fileInfo.dir().path());
	taggingWidget->loadData();
	return true;
}

void GTMainWindow::about() {
	QMessageBox::about(this, tr("About Application"),
		tr("The <b>Application</b> example demonstrates how to "
		"write modern GUI applications using Qt, with a menu bar, "
		"toolbars, and a status bar."));
}

void GTMainWindow::documentWasModified() {
	setWindowModified(textEdit->document()->isModified());
}

void GTMainWindow::createActions() {
	newAct = new QAction(QIcon(":/Resources/gtmain_images/new.png"), tr("&New"), this);
	newAct->setShortcuts(QKeySequence::New);
	newAct->setStatusTip(tr("Create a new GT project"));
	newAct->setToolTip(tr("Create a new GT project"));
	connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));
	openAct = new QAction(QIcon(":/Resources/gtmain_images/open.png"), tr("&Open..."), this);
	openAct->setShortcuts(QKeySequence::Open);
	openAct->setStatusTip(tr("Open an existing GT project"));
	openAct->setToolTip(tr("Open an existing GT project"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
	saveAct = new QAction(QIcon(":/Resources/gtmain_images/save.png"), tr("&Save"), this);
	saveAct->setShortcuts(QKeySequence::Save);
	saveAct->setStatusTip(tr("Save GT project to disk"));
	saveAct->setToolTip(tr("Save GT project to disk"));
	connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));
	closeAct = new QAction(QIcon(":/Resources/gtmain_images/close.png"), tr("&Close"), this);
	closeAct->setShortcuts(QKeySequence::Close);
	closeAct->setStatusTip(tr("Close GT project"));
	closeAct->setToolTip(tr("Close GT project"));
	connect(closeAct, SIGNAL(triggered()), this, SLOT(close()));

	/*saveAsAct = new QAction(tr("Save &As..."), this);
	saveAsAct->setShortcuts(QKeySequence::SaveAs);
	saveAsAct->setStatusTip(tr("Save the document under a new name"));
	connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));*/
	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcuts(QKeySequence::Quit);

	exitAct->setStatusTip(tr("Exit GTGenerator"));
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
	/*cutAct = new QAction(QIcon(":/Resources/gtmain_images/cut.png"), tr("Cu&t"), this);

	cutAct->setShortcuts(QKeySequence::Cut);
	cutAct->setStatusTip(tr("Cut the current selection's contents to the "
		"clipboard"));
	connect(cutAct, SIGNAL(triggered()), textEdit, SLOT(cut()));

	copyAct = new QAction(QIcon(":/Resources/gtmain_images/copy.png"), tr("&Copy"), this);
	copyAct->setShortcuts(QKeySequence::Copy);
	copyAct->setStatusTip(tr("Copy the current selection's contents to the "
		"clipboard"));
	connect(copyAct, SIGNAL(triggered()), textEdit, SLOT(copy()));

	pasteAct = new QAction(QIcon(":/Resources/gtmain_images/paste.png"), tr("&Paste"), this);
	pasteAct->setShortcuts(QKeySequence::Paste);
	pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
		"selection"));
	connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));

	aboutAct = new QAction(tr("&About"), this);
	aboutAct->setStatusTip(tr("Show the application's About box"));
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
	aboutQtAct = new QAction(tr("About &Qt"), this);
	aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
	connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

	cutAct->setEnabled(false);

	copyAct->setEnabled(false);
	connect(textEdit, SIGNAL(copyAvailable(bool)),
		cutAct, SLOT(setEnabled(bool)));
	connect(textEdit, SIGNAL(copyAvailable(bool)),
		copyAct, SLOT(setEnabled(bool)));*/
}

void GTMainWindow::createMenus() {
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAct);

	fileMenu->addAction(openAct);

	fileMenu->addAction(saveAct);

	fileMenu->addAction(closeAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	menuBar()->addSeparator();
	menuBar()->addSeparator();
	menuBar()->addSeparator();

	menuBar()->addAction(newAct);
	menuBar()->addSeparator();

	menuBar()->addAction(openAct);
	menuBar()->addSeparator();

	menuBar()->addAction(saveAct);
	menuBar()->addSeparator();

	menuBar()->addAction(closeAct);
	menuBar()->addSeparator();

	/*editMenu = menuBar()->addMenu(tr("&Edit"));
	editMenu->addAction(cutAct);
	editMenu->addAction(copyAct);
	editMenu->addAction(pasteAct);*/

	/*menuBar()->addSeparator();

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAct);
	helpMenu->addAction(aboutQtAct);*/
}

void GTMainWindow::createToolBars(){	
	fileToolBar = addToolBar(tr("File"));
	fileToolBar->setFloatable(false);
	fileToolBar->setMovable(false);
	fileToolBar->setIconSize(QSize(25, 25));

	fileMenu =  new QMenu();
	fileMenu->addAction(newAct);

	fileMenu->addAction(openAct);

	fileMenu->addAction(saveAct);

	fileMenu->addAction(closeAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	QToolButton* toolButton = new QToolButton();
	toolButton->setIcon(QIcon(":/Resources/gt_icon.png"));
	toolButton->setMenu(fileMenu);
	toolButton->setPopupMode(QToolButton::InstantPopup);
	fileToolBar->addWidget(toolButton);

	fileToolBar->addSeparator();
	fileToolBar->addAction(newAct);

	fileToolBar->addAction(openAct);

	fileToolBar->addAction(saveAct);

	fileToolBar->addAction(closeAct);

	fileToolBar->addSeparator();

	//ui->gtStatusWidget->setParent(fileToolBar);
	//ui->gtStatusWidget->setVisible(false);
	//fileToolBar->addWidget(ui->gtStatusWidget);

	/*editToolBar = addToolBar(tr("Edit"));
	editToolBar->addAction(cutAct);
	editToolBar->addAction(copyAct);
	editToolBar->addAction(pasteAct);*/
}

void GTMainWindow::createStatusBar() {
	statusBar()->showMessage(tr("Ready"));
}

void GTMainWindow::readSettings() {
	QSettings settings("Trolltech", "Application Example");
	QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
	QSize size = settings.value("size", QSize(400, 400)).toSize();
	resize(size);
	move(pos);
}

void GTMainWindow::writeSettings() {
	QSettings settings("Trolltech", "Application Example");
	settings.setValue("pos", pos());
	settings.setValue("size", size());
}

bool GTMainWindow::maybeSave() {
	if (textEdit->document()->isModified()) {
		QMessageBox::StandardButton ret;
		ret = QMessageBox::warning(this, tr("Application"),
			tr("The document has been modified.\n"
			"Do you want to save your changes?"),
			QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		if (ret == QMessageBox::Save)
			return save();
		else if (ret == QMessageBox::Cancel)
			return false;
	}
	return true;
}

void GTMainWindow::loadFile(const QString &fileName) {
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Application"),
			tr("Cannot read file %1:\n%2.")
			.arg(fileName)
			.arg(file.errorString()));
		return;
	}

	QTextStream in(&file);
#ifndef QT_NO_CURSOR
	QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
	textEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
	QApplication::restoreOverrideCursor();
#endif

	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File loaded"), 2000);
}

bool GTMainWindow::saveFile(const QString &fileName) {
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Application"),
			tr("Cannot write file %1:\n%2.")
			.arg(fileName)
			.arg(file.errorString()));
		return false;
	}

	QTextStream out(&file);
#ifndef QT_NO_CURSOR
	QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
	out << textEdit->toPlainText();
#ifndef QT_NO_CURSOR
	QApplication::restoreOverrideCursor();
#endif

	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File saved"), 2000);
	return true;
}

void GTMainWindow::setCurrentFile(const QString &fileName) {
	curFile = fileName;
	textEdit->document()->setModified(false);
	setWindowModified(false);

	QString shownName = curFile;
	if (curFile.isEmpty())
		shownName = "untitled.txt";
	setWindowFilePath(shownName);
}

QString GTMainWindow::strippedName(const QString &fullFileName) {
	return QFileInfo(fullFileName).fileName();
}

void GTMainWindow::newProjectWizardFinished(int result) {
	qDebug() << "wizard Finished " << result << endl;

	data->gtProject->name = fileProcessor->removeForbiddenChars(newProjectWizard->getGTProjectName()).toUpper();
	if(data->gtProject->name.isEmpty()) {
		data->gtProject->name = "BLANK_GTPROJECT_" + QDate::currentDate().toString(Qt::ISODate);
	}

	ui->gtProjectName_title->setFont(QFont("Newyork", 10, QFont::Bold));
	ui->gtProjectName_title->setText(data->gtProject->name);
	
	taggingWidget = new TaggingWidget();
	setCentralWidget(taggingWidget);

	ui->gtStatusWidget->setVisible(true);
	fileToolBar->addWidget(ui->gtStatusWidget);

	//gtProjectWidget = new GTProjectWidget(width());
	//setCentralWidget(gtProjectWidget);
}
