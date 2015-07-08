#include "taggingwidget.h"
#include "ui_taggingwidget.h"

#include <QDebug>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QProgressDialog>
#include <QApplication>
#include <QCoreApplication>
#include <QSizePolicy>

#include "diagramitem.h"
#include "diagramscene.h"
#include "colorlistwidgetitem.h"
#include "diagramsceneinfo.h"
#include "diagramroi.h"
#include "fileprocessor.h"
#include "opencvprocessor.h"
#include "xmlprocessor.h"
#include "diagramroilabel.h"

#include <QApplication>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QScrollArea>
#include <QLabel>
#include <QtEvents>
#include <QPainter>
#include <QInputDialog>
#include <QUndoGroup>
#include <QtCore/QTimer>
#include <QtCore/QMap>
#include <QColor>
#include <QColorDialog>
#include <QSizePolicy>
#include <QToolTip>
#include <cstdlib>
#include <QListWidget>
#include <QListWidgetItem>
#include <time.h>

#define qApp (static_cast<QApplication *>(QCoreApplication::instance()))

TaggingWidget::TaggingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaggingWidget)
{
	data = GTProjectData::Instance();

	treeItems = QList<GTTreeItem*>();

	previewPlayerTimer = new QTimer(this);
    connect(previewPlayerTimer, SIGNAL(timeout()), this, SLOT(playPreview()));
	stopPreview = true;

	DEFAULT_DIR_KEY = "default_dir";
	InsertTextButton = 10;
	scalePercentageWidth = 0.88;
	scalePercentageHeight = 0.88;
	currentPreviewIndex = 0;
	currentTopLevelItems = 0;
	subsamplingStep = 0;
	imagesLength = 0;
	roiItemFont = QFont("Newyork", 18);

     dirSettingsPath = QApplication::applicationDirPath() + "/settings.ini";
//    qDebug() << "Creating settings file: " << dirSettingsPath << endl;

    QSettings dirSettings(dirSettingsPath, QSettings::IniFormat);
    dirSettings.setValue(DEFAULT_DIR_KEY, "G:\\data\\sebastianvilla139\\work\\datasets\\survmantics\\00001");
    //dirSettings.setValue(DEFAULT_DIR_KEY, "Z:\\master\\survmantics\\dataset\\processed\\00001");

    ui->setupUi(this);

	progressDialog = new QProgressDialog(this);
	progressDialog->setFixedSize(QSize(400,100));

//    QPixmap pix( "Z:\\master\\survmantics\\dataset\\processed\\00001\\image00001.png" );
    //QPixmap pix( "Z:\\master\\fish_contest\\dataset\\videos\\test_video\\0.png" );

    scene = new DiagramScene(this);
    //scene->setSceneRect(QRectF(0, 0, pix.width()*scalePercentageWidth, pix.height()*scalePercentageHeight));
    //scene->setSceneRect(QRectF(0, 0, width()*scalePercentageWidth, height()*scalePercentageHeight));

    view = new DiagramView(scene, ui->imageArea);

//    QPixmap finalPix = pix.scaledToWidth(width()*scalePercentageWidth);

//    scene->addPixmap( finalPix );

    //imageArea = new ImageArea(true, "", ui->imageArea);

    //filesTable = new QTableWidget(0, 2);
    ui->roiTable->setRowCount(0);
    ui->roiTable->setColumnCount(8);
    QStringList roiTableHeader;
    roiTableHeader << tr("ROI ID") << tr("Label") << tr("W") << tr("H") << tr("TLX") << tr("TLY") << tr("BRX") << tr("BRY");

    ui->roiTable->setColumnWidth(0, 100);
    ui->roiTable->setColumnWidth(1, 160);
    ui->roiTable->setColumnWidth(2, 50);
    ui->roiTable->setColumnWidth(3, 50);
    ui->roiTable->setColumnWidth(4, 50);
    ui->roiTable->setColumnWidth(5, 50);
    ui->roiTable->setColumnWidth(6, 50);
    ui->roiTable->setColumnWidth(7, 50);

	QPalette palette;    
	palette.setColor(QPalette::Highlight, Qt::yellow);
    palette.setColor(QPalette::HighlightedText, Qt::black);
	ui->roiTable->setPalette(palette);

    ui->roiTable->setHorizontalHeaderLabels(roiTableHeader);

    ui->roiTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->roiTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    ui->roiTable->verticalHeader()->hide();
    ui->roiTable->setShowGrid(true);

    scene->roiTable = ui->roiTable;

    ui->fileListWidget->installEventFilter(this);    
    //mZoomInAction->setShortcut(DataSingleton::Instance()->getToolShortcutByKey("ZoomIn"));
    //mZoomOutAction->setShortcut(DataSingleton::Instance()->getToolShortcutByKey("ZoomOut"));
    //connect(mZoomInAction, SIGNAL(triggered()), this, SLOT(zoomInAct()));
    //connect(mZoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOutAct()));
    //imageArea->resize(ui->scrollArea->width(), ui->scrollArea->height());
    //qDebug() << "resizing to size of: " << ui->scrollArea << endl;        

//    for(int i=0; i<10; i++) {
//        QListWidgetItem *pieceItem = new QListWidgetItem(ui->labelsListWidget);

//        QPixmap colorItem(100,100);

//        QPainter painter(&colorItem);
//        int r_comp = rand() % 255;
//        int g_comp = rand() % 255;
//        int b_comp = rand() % 255;

//        QColor color(r_comp, g_comp, b_comp);

//        pieceItem->setText(color.name());
//        pieceItem->setToolTip(QString::number(color.red()));
//        pieceItem->setTextAlignment(Qt::AlignBottom);

//        //painter.setBrush(Qt::SolidPattern);
//        //painter.setPen(QPen(color, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
//        painter.setBrush(QBrush(color));
//        //painter.setPen(Qt::darkGreen);
//        painter.drawRect(QRect(QPoint(0,0), QPoint(100,100) - QPoint(2,2)));

//        pieceItem->setData(Qt::UserRole, color);
//        pieceItem->setData(Qt::UserRole+1, color.name());
//        pieceItem->setData(Qt::UserRole+2, QString::number(color.red()));
//        pieceItem->setData(Qt::UserRole+3, colorItem);

//        pieceItem->setIcon(QIcon(colorItem));
//        pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
//    }

//    for(int i=0; i<10; i++) {
//        ColorListWidgetItem *pieceItem = new ColorListWidgetItem(ui->labelsListWidget);

//        QPixmap colorItem(100,100);

//        QPainter painter(&colorItem);
//        int r_comp = rand() % 255;
//        int g_comp = rand() % 255;
//        int b_comp = rand() % 255;

//        QColor color(r_comp, g_comp, b_comp);

//        pieceItem->setText(color.name());
//        pieceItem->setToolTip(QString::number(color.red()));
//        pieceItem->setTextAlignment(Qt::AlignBottom);

//        //painter.setBrush(Qt::SolidPattern);
//        //painter.setPen(QPen(color, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
//        painter.setBrush(QBrush(color));
//        //painter.setPen(Qt::darkGreen);
//        painter.drawRect(QRect(QPoint(0,0), QPoint(100,100) - QPoint(2,2)));

//        pieceItem->setData(Qt::UserRole, color);
//        pieceItem->setData(Qt::UserRole+1, color.name());
//        pieceItem->setData(Qt::UserRole+2, QString::number(color.red()));
//        pieceItem->setData(Qt::UserRole+3, colorItem);

//        pieceItem->setIcon(QIcon(colorItem));
//        pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
//    }

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);
    view->setRubberBandSelectionMode(Qt::ContainsItemBoundingRect);
    ui->imageArea->setLayout(layout);

//    deleteAction = new QAction(this);
//    deleteAction->setShortcut(Qt::Key_Delete);
//    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));

    scene->installEventFilter(this);

    connect(scene->roiTable->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(handleSelectionChanged(QItemSelection)));

    connect(scene, SIGNAL(selectionChanged()), this, SLOT(sceneSelectionChanged()));

    colorToAdd = Qt::red;

    QPixmap colorItem(50,50);
    QPainter painter(&colorItem);
    painter.setBrush(colorToAdd);
    painter.drawRect(QRect(QPoint(0,0), QPoint(50, 50) - QPoint(2,2)));
    ui->selectLabelColor->setIcon(QIcon(colorItem));

    ui->imageTree->setColumnCount(3);
    ui->imageTree->setColumnWidth(0, 70);
    ui->imageTree->setColumnWidth(1, 100);
    ui->imageTree->setColumnWidth(2, 50);

    QStringList treeTableHeader;
    treeTableHeader << tr("Frame") << tr("Image") << tr("Labeled");
    ui->imageTree->setHeaderLabels(treeTableHeader);

    QTreeWidgetItem *headeritem = new QTreeWidgetItem(treeTableHeader);
    headeritem->setTextAlignment(0,Qt::AlignHCenter);
    headeritem->setTextAlignment(1,Qt::AlignHCenter);
    headeritem->setTextAlignment(2,Qt::AlignHCenter);
    ui->imageTree->setHeaderItem(headeritem);
    ui->imageTree->setHeaderLabels(treeTableHeader);

    //ui->subsamplingMonitor->setIconSize(QSize(2, 28));
    ui->imageTree->setIconSize(QSize(100,100));
    ui->imageTree->setExpandsOnDoubleClick(false);
    ui->imageTree->installEventFilter(this);
    ui->subsamplingMonitor->installEventFilter(this);

    previewScene = new QGraphicsScene(ui->previewWidget);
    previewView = new DiagramView(false, previewScene);

    QHBoxLayout *layoutPreview = new QHBoxLayout;
    layoutPreview->addWidget(previewView);
    previewView->setRubberBandSelectionMode(Qt::ContainsItemBoundingRect);
    ui->previewWidget->setLayout(layoutPreview);

//    QPixmap fileImage;
//    if(fileImage.load("Z:\\master\\survmantics\\dataset\\processed\\00001\\image00001.png")) {
//        double ratio = fileImage.width()/fileImage.height();
//        qDebug() << "ui->tab->height()" << ui->previewWidget->height() << endl;
//        QPixmap scaled = fileImage.scaledToHeight(ui->previewWidget->height()*0.7);
//        previewScene->addPixmap(scaled);
//        previewScene->setSceneRect(QRectF(0, 0, scaled.width(), scaled.height()));
//    }

    //scene->setSceneRect(QRectF(0, 0, pix.width()*scalePercentageWidth, pix.height()*scalePercentageHeight));
    //scene->setSceneRect(QRectF(0, 0, width()*scalePercentageWidth, height()*scalePercentageHeight));

    subsampledItems = QList<int>();

    //ui->imageTree->setStyleSheet("QTreeWidget::item:selected {border:1px solid yellow;}");

    ui->fileListWidget->setStyleSheet("QListWidget::item:selected { background-color: yellow; border-width:1px; color:black;}");

    ui->subsamplingMonitor->setStyleSheet("QListWidget::item:selected { background-color: yellow; border-width:1px; color:black;}");

    ui->roisListWidget->installEventFilter(this);

    ui->roisListWidget->setStyleSheet("QListWidget::item:selected { background-color: yellow; border-width:1px; color:black;}");

    ui->labelsListWidget->installEventFilter(this);

    ui->labelToAdd->installEventFilter(this);

    colorDialog = new QColorDialog(this);

//    connect(colorDialog, SIGNAL(colorSelected(QColor)), this, SLOT(colorSelectedChanged(QColor)));
    manualColor = false;
    srand (time(NULL));

	ui->currentLabelColor->setText("--NO LABEL--");
	ui->currentLabelColor->setStyleSheet("background-color: white; color: black;");

	bgsLoaded = false;
	bgsMaxIterations = 0;

	ui->roisListWidget->installEventFilter(this);
	ui->roiTable->installEventFilter(this);

	ui->globalTabs->setTabEnabled(0, true);
	ui->globalTabs->setTabEnabled(1, false);
	ui->globalTabs->setTabEnabled(2, false);
	ui->globalTabs->setTabEnabled(3, false);
	ui->globalTabs->setTabEnabled(4, false);
	ui->globalTabs->setTabEnabled(5, false);

	ui->subsamplingMonitor->setVisible(false);
}

TaggingWidget::~TaggingWidget()
{
    delete ui;
}

void TaggingWidget::handleSelectionChanged(const QItemSelection& selection) {
    if(!selection.indexes().isEmpty()) {
//        qDebug() << "selection Changed! selection: " << selection.first().model() << endl;
//        qDebug() << "selection Changed! selection: selection.first().indexes().first().row() " << selection.first().indexes().first().row() << endl;
        selectItemFromModel(selection.first().model(), selection.first().indexes().first().row());
        on_roisListWidget_pressed(selection.first().indexes().first());
        //qDebug() << "no selection!" << endl;
      //clearMyView();
    } else {
      //displayModelIndexInMyView(selection.indexes().first());
        ui->roisListWidget->clearSelection();
        ui->roiTable->clearSelection();
    }
}

bool TaggingWidget::eventFilter(QObject *object, QEvent *event)
{
    if ( object == ui->fileListWidget && event->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);

        //qDebug() << "key Event: " << ke->key() << endl;

        if (ke->key() == Qt::Key_Return || ke->key() == Qt::Key_Space) {
            int index = ui->fileListWidget->currentItem()->data(Qt::UserRole+2).toString().toInt();
            ui->subsamplingMonitor->setCurrentRow(index);

            if(ui->imageTree->topLevelItem(index)->isHidden()) {
                int division = subsamplingStep==0?0:index/subsamplingStep;
//                qDebug() << "division: " << division << endl;

                int parentIndex = division*subsamplingStep;
//                qDebug() << "parentIndex: " << parentIndex << endl;

                int childIndex = index - parentIndex - 1;
//                qDebug() << "childIndex: " << childIndex << endl;

//                qDebug() << "subsamplingStep:" << subsamplingStep << endl;
//                qDebug() << "calculusIndex:" << calculusIndex << endl;
                //ui->imageTree->collapseAll();
                ui->imageTree->topLevelItem(parentIndex)->child(childIndex)->setExpanded(true);
                ui->imageTree->setCurrentItem(ui->imageTree->topLevelItem(parentIndex)->child(childIndex));
                ui->imageTree->scrollToItem(ui->imageTree->topLevelItem(parentIndex)->child(childIndex));
            } else {
//                qDebug() << "not hidden..." << endl;
                //ui->imageTree->collapseAll();
                ui->imageTree->setCurrentItem(ui->imageTree->topLevelItem(index));
                ui->imageTree->scrollToItem(ui->imageTree->topLevelItem(index));
            }
            updateImage(index);
        }

        QWidget::eventFilter(object, event);
        return false;

    } else if ( object == ui->imageTree && event->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);

        //qDebug() << "key Event: " << ke->key() << endl;

        if (ke->key() == Qt::Key_Return || ke->key() == Qt::Key_Space) {
            //imageArea->clearSelection();
            int index = ui->imageTree->currentItem()->data(0, Qt::UserRole+2).toString().toInt();
            ui->subsamplingMonitor->setCurrentRow(index);
            ui->fileListWidget->setCurrentRow(index);
            updateImage(index);
        }

        QWidget::eventFilter(object, event);
        return false;
    } else if ( object == ui->subsamplingMonitor && event->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);

        //qDebug() << "key Event: " << ke->key() << endl;

        if (ke->key() == Qt::Key_Return || ke->key() == Qt::Key_Space) {
            //imageArea->clearSelection();
            int index = ui->subsamplingMonitor->currentItem()->data(Qt::UserRole+2).toString().toInt();
            ui->fileListWidget->setCurrentRow(index);

            if(ui->imageTree->topLevelItem(index)->isHidden()) {
                int division = subsamplingStep==0?0:index/subsamplingStep;
//                qDebug() << "division: " << division << endl;

                int parentIndex = division*subsamplingStep;
//                qDebug() << "parentIndex: " << parentIndex << endl;

                int childIndex = index - parentIndex - 1;
//                qDebug() << "childIndex: " << childIndex << endl;

//                qDebug() << "subsamplingStep:" << subsamplingStep << endl;
//                qDebug() << "calculusIndex:" << calculusIndex << endl;
                //ui->imageTree->collapseAll();
                ui->imageTree->topLevelItem(parentIndex)->child(childIndex)->setExpanded(true);
                ui->imageTree->setCurrentItem(ui->imageTree->topLevelItem(parentIndex)->child(childIndex));
                ui->imageTree->scrollToItem(ui->imageTree->topLevelItem(parentIndex)->child(childIndex));
            } else {
//                qDebug() << "not hidden..." << endl;
                //ui->imageTree->collapseAll();
                ui->imageTree->setCurrentItem(ui->imageTree->topLevelItem(index));
                ui->imageTree->scrollToItem(ui->imageTree->topLevelItem(index));
            }

            updateImage(index);
        }

        QWidget::eventFilter(object, event);
        return false;
    } else if ( object == ui->labelsListWidget && event->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);

        //qDebug() << "key Event: " << ke->key() << endl;

        if (ke->key() == Qt::Key_Return) {
            //imageArea->clearSelection();
            ui->labelsListWidget->closePersistentEditor(ui->labelsListWidget->currentItem());
            ui->labelsListWidget->currentItem()->setText(ui->labelsListWidget->currentItem()->text().toUpper());
            ui->labelsListWidget->currentItem()->setToolTip(ui->labelsListWidget->currentItem()->text().toUpper());

			int index = ui->labelsListWidget->currentItem()->data(Qt::UserRole+2).toInt();
			data->scenesLabels->at(index)->setName(ui->labelsListWidget->currentItem()->text().toUpper());

			ui->labelsListWidgetTagging->setCurrentRow(index);
			ui->labelsListWidgetTagging->currentItem()->setText(ui->labelsListWidget->currentItem()->text().toUpper());
            ui->labelsListWidgetTagging->currentItem()->setToolTip(ui->labelsListWidget->currentItem()->text().toUpper());			
        } else if (ke->key() == Qt::Key_Delete) {            
			int index = ui->labelsListWidget->currentRow();
			ui->labelsListWidget->takeItem(ui->labelsListWidget->currentRow());

			ui->labelsListWidgetTagging->setCurrentRow(index);
			ui->labelsListWidgetTagging->takeItem(index);

			data->scenesLabels->at(index)->setRemoved(true);
		} else if (ke->key() == Qt::Key_F2) {
			if(ui->labelsListWidget->currentItem() != NULL) {
				ui->labelsListWidget->openPersistentEditor(ui->labelsListWidget->currentItem());
			}			
		} else if (ke->key() == Qt::Key_F3) {
			if(ui->labelsListWidget->currentItem() != NULL) {
				QColor itemColor = qvariant_cast<QColor>(ui->labelsListWidget->currentItem()->data(Qt::UserRole));
				QColor selectedColor = colorDialog->getColor(itemColor);

				if(selectedColor != itemColor) {
					int index = ui->labelsListWidget->currentItem()->data(Qt::UserRole+2).toInt();
					data->scenesLabels->at(index)->setColor(selectedColor);

					QPixmap colorItem(100, 100);
					QPainter painter(&colorItem);
					painter.setBrush(selectedColor);
					painter.drawRect(QRect(QPoint(0,0), QPoint(100, 100) - QPoint(2,2)));

					int d = 0;
					// Counting the perceptive luminance - human eye favors green color... 
					double a = 1 - ( 0.299 * selectedColor.red() + 0.587 * selectedColor.green() + 0.114 * selectedColor.blue())/255;

					QString textColor = "white";
					QColor textualColor = Qt::black;

					if (a < 0.5) {
					   textColor = "black"; // bright colors - black font
					   textualColor = Qt::black;
					} else {
					   textColor = "white"; // dark colors - white font	
					   textualColor = Qt::white;
					}

					ui->currentLabelColor->setStyleSheet("background-color:" + data->currentLabelColor.name()+";" + "color: " + textColor +";");

					painter.setPen(QPen(QBrush(textualColor), 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
					painter.setFont(QFont("Newyork", 25));

					if(index < 10) {
						painter.drawText(QPoint(40,60), QString::number(index+1));
					} else {
						painter.drawText(QPoint(35,60), QString::number(index+1));
					}

					ui->labelsListWidget->currentItem()->setIcon(QIcon(colorItem));
					ui->labelsListWidget->currentItem()->setData(Qt::UserRole, selectedColor);
					ui->labelsListWidget->currentItem()->setData(Qt::UserRole+3, colorItem);
					ui->labelsListWidgetTagging->setCurrentRow(ui->labelsListWidget->row(ui->labelsListWidget->currentItem()));
					ui->labelsListWidgetTagging->item(ui->labelsListWidget->row(ui->labelsListWidget->currentItem()))->setIcon(QIcon(colorItem));
					ui->labelsListWidgetTagging->item(ui->labelsListWidget->row(ui->labelsListWidget->currentItem()))->setData(Qt::UserRole, selectedColor);
					//ui->labelsListWidgetTagging->item(ui->labelsListWidget->row(ui->labelsListWidget->currentItem()))->setData(Qt::UserRole+2, index);
					ui->labelsListWidgetTagging->item(ui->labelsListWidget->row(ui->labelsListWidget->currentItem()))->setData(Qt::UserRole+3, colorItem);

					data->currentLabelColor = colorToAdd;

					data->labelSelected = true;
					data->currentLabelColor = qvariant_cast<QColor>(ui->labelsListWidget->currentItem()->data(Qt::UserRole));
					data->currentLabelString = ui->labelsListWidget->currentItem()->data(Qt::UserRole+1).toString();
					data->currentLabelId = ui->labelsListWidget->currentItem()->data(Qt::UserRole+2).toInt();
					ui->currentLabelColor->setText(data->currentLabelString);					
				}    
			}			
		}

        QWidget::eventFilter(object, event);
        return false;
    } else if ( object == ui->labelToAdd && event->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);

        //qDebug() << "key Event: " << ke->key() << endl;

        if (ke->key() == Qt::Key_Return) {
            //imageArea->clearSelection();
            //colorToAdd

            if(!manualColor) {                
                int r_comp = rand() % 255;
                int g_comp = rand() % 255;
                int b_comp = rand() % 255;

                colorToAdd = QColor(r_comp, g_comp, b_comp);
                manualColor = false;
            }
			
            on_addLabel_clicked();
        }

        QWidget::eventFilter(object, event);
        return false;
    } else if (object == scene && event->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);

        if (ke->key() == Qt::Key_Delete ) {
            deleteItem();
        }

        QWidget::eventFilter(object, event);
        return false;
	} else if (object == ui->roiTable && event->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);

        if (ke->key() == Qt::Key_Delete ) {
            deleteItem();
        }

        QWidget::eventFilter(object, event);
        return false;
    } else if (object == ui->roisListWidget && event->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);

        if (ke->key() == Qt::Key_Delete ) {
            deleteItem();
        }

        QWidget::eventFilter(object, event);
        return false;
    } else
        return false;
}

void TaggingWidget::selectGTProject(QString directory) {
	QSettings dirSettings(dirSettingsPath, QSettings::IniFormat);

    if (!directory.isEmpty()) {
//        qDebug() << "Selected directory: " << directory << endl;

        currentDir = QDir(directory);

        dirSettings.setValue(DEFAULT_DIR_KEY, currentDir.absoluteFilePath(directory));
//        qDebug() << "Setting dir settings to: " << currentDir.absoluteFilePath(directory) << endl;

        ui->videoDirPath->setText(directory);

        QStringList files;

        QStringList filters;
        filters << "*.png" << "*.jpg" << "*.jpeg";

        files = currentDir.entryList(filters, QDir::Files | QDir::NoSymLinks);

        data->scenesInfos->clear();
        //qDebug() << "Showing files.." << endl;
        showFiles(files);
    }
}

void TaggingWidget::on_selectVideo_clicked() {
  QSettings dirSettings(dirSettingsPath, QSettings::IniFormat);
//    qDebug() << "Reading dir settings as: " << dirSettings.value(DEFAULT_DIR_KEY).toString() << endl;
    QString videoPath = QFileDialog::getOpenFileName(this, tr("Select video:"), dirSettings.value(DEFAULT_DIR_KEY).toString(), tr("Video Files (*.avi *.flv *.mp4)"));
    //dirSettings.value(DEFAULT_DIR_KEY).toString()
    //"G:\\data\\sebastianvilla139\\work\\datasets\\survmantics\\00001"
	videoFile = QFileInfo(videoPath);

    if (!videoPath.isEmpty()) {
//        qDebug() << "Selected directory: " << directory << endl;

        currentDir = QDir(videoPath);
		qDebug() << "currentDir: " << videoFile.dir().path() << endl;
		qDebug() << "currentFile: " << videoFile.fileName() << endl;

		QDir videoFramesDir = QDir(videoFile.dir().path()+"\\"+ videoFile.baseName().section(".", 0, 0) + "_video_frames\\");

		qDebug() << "videoFramesDir" << videoFramesDir.path() << endl;

		if(!videoFramesDir.exists()) {
			QDir().mkdir(videoFramesDir.path());
		}

		/*currentDir.cdUp();
		qDebug() << "currentDir: " << currentDir << endl;*/

        dirSettings.setValue(DEFAULT_DIR_KEY, currentDir.absoluteFilePath(videoPath));
//        qDebug() << "Setting dir settings to: " << currentDir.absoluteFilePath(directory) << endl;        

		OpenCVProcessor openCVProcessor = OpenCVProcessor();
		openCVProcessor.setProgressDialog(progressDialog);
		double fps = openCVProcessor.saveFramesFromVideo(videoPath, videoFramesDir.path());

		currentDir = QDir(videoFramesDir.path());

		ui->videoDirPath->setText(videoFramesDir.path());

        QStringList files;

        QStringList filters;
        filters << "*.png" << "*.jpg" << "*.jpeg";

        files = currentDir.entryList(filters, QDir::Files | QDir::NoSymLinks);

        data->scenesInfos->clear();
        //qDebug() << "Showing files.." << endl;
        showFiles(files);
    }
}

void TaggingWidget::on_selectDir_clicked()
{
    QSettings dirSettings(dirSettingsPath, QSettings::IniFormat);
//    qDebug() << "Reading dir settings as: " << dirSettings.value(DEFAULT_DIR_KEY).toString() << endl;
    QString directory = QFileDialog::getExistingDirectory(this, tr("Select directory:"), dirSettings.value(DEFAULT_DIR_KEY).toString());
    //dirSettings.value(DEFAULT_DIR_KEY).toString()
    //"G:\\data\\sebastianvilla139\\work\\datasets\\survmantics\\00001"

    if (!directory.isEmpty()) {
//        qDebug() << "Selected directory: " << directory << endl;

        currentDir = QDir(directory);

        dirSettings.setValue(DEFAULT_DIR_KEY, currentDir.absoluteFilePath(directory));
//        qDebug() << "Setting dir settings to: " << currentDir.absoluteFilePath(directory) << endl;

        ui->videoDirPath->setText(directory);

        QStringList files;

        QStringList filters;
        filters << "*.png" << "*.jpg" << "*.jpeg";

        files = currentDir.entryList(filters, QDir::Files | QDir::NoSymLinks);

        data->scenesInfos->clear();
        //qDebug() << "Showing files.." << endl;
        showFiles(files);

    }
}

void TaggingWidget::showFiles(const QStringList &files)
{    
    progressDialog->show();
    progressDialog->setCancelButtonText(tr("&Cancel"));
    progressDialog->setRange(0, files.size());
    progressDialog->setWindowTitle(tr("Listing Images..."));

    ui->fileListWidget->clear();
    ui->roisListWidget->clear();
    ui->subsamplingMonitor->clear();
    ui->imageTree->clear();
    scene->clear();
    subsampledItems.clear();
    ui->imageNameLabel->setText("");
    ui->subsamplingSlider->setEnabled(false);
    ui->subsamplingSlider->setValue(100);
    ui->subsamplingCheck->setChecked(false);
    //ui->subsamplingUpdateButton->setEnabled(false);
    ui->subsamplingValue->setText("100");
    ui->subsamplingValue->setEnabled(false);
    ui->fpsLabel->setEnabled(false);
    ui->fpsPreview->setEnabled(false);
    ui->playPreviewButton->setEnabled(false);
    ui->playPreviewProgressBar->setValue(0);
    ui->playPreviewProgressBar->setEnabled(false);
    ui->showROIsLabel->setEnabled(false);
    ui->showROIsCheckbox->setChecked(false);
    ui->showROIsCheckbox->setEnabled(false);
    ui->showOnlyLabeledROIsLabel->setEnabled(false);
    ui->showOnlyLabeledROIsCheckbox->setChecked(false);
    ui->showOnlyLabeledROIsCheckbox->setEnabled(false);
	ui->copyComboBox->setEnabled(false);
	ui->copyOptionsLabel->setEnabled(false);
	ui->copyROIsButton->setEnabled(false);
	ui->showFirstFrameButton->setEnabled(false);
	ui->showPreviousFrameButton->setEnabled(false);
	ui->showPreviousParentFrameButton->setEnabled(false);
	ui->showNextFrameButton->setEnabled(false);
	ui->copyOnNextCheck->setEnabled(false);
	ui->showNextParentFrameButton->setEnabled(false);
	ui->showLastFrameButton->setEnabled(false);
    previewScene->clear();
	treeItems.clear();

	double firstGridWidth = (double)ui->subsamplingMonitor->width()/(double)files.size();
	double secondGridWidth = 0.7*firstGridWidth;
	double coeficient = ((double)ui->subsamplingMonitor->width()*firstGridWidth)/((double)ui->subsamplingMonitor->width()*secondGridWidth);
	qDebug() << "coeficient" << coeficient << endl;

    gridWidth = coeficient*(double)ui->subsamplingMonitor->width()/(double)files.size();

    qDebug() << "ui->subsamplingMonitor->width()" << ui->subsamplingMonitor->width() << endl;
    qDebug() << "files.size()" << files.size() << endl;
    qDebug() << "gridWidth" << gridWidth << endl;
    qDebug() << "(int)gridWidth*files.size()" << ((int)gridWidth)*files.size() << endl;
    qDebug() << "gridWidth*files.size()" << gridWidth*files.size() << endl;

    ui->subsamplingMonitor->setGridSize(QSize(gridWidth*0.7, 30));
    ui->subsamplingMonitor->setIconSize(QSize(gridWidth, 30));

    int intSize = ((int)firstGridWidth)*files.size();
//    double doubleSize = gridWidth*files.size();
//    int spaceSize = (doubleSize - intSize)/2;
    ui->subsamplingMonitor->setFixedWidth(intSize+4);

//    qDebug() << "spaceSize" << spaceSize << endl;

//    QListWidgetItem *firstSpaceItem = new QListWidgetItem(ui->subsamplingMonitor);
//    QPixmap firstSpaceItemColor(spaceSize, 35);
//    QPainter painterFirst(&firstSpaceItemColor);
////        painter.setPen(Qt::transparent);
////        painter.setBrush(Qt::blue);
//    painterFirst.fillRect(QRect(QPoint(0,0), QPoint(spaceSize, 35)), Qt::white);
//    firstSpaceItem->setIcon(QIcon(firstSpaceItemColor));

    QPixmap colorItem(gridWidth*0.9, 33);
    QPainter painter(&colorItem);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(QRect(QPoint(0,0), QPoint(gridWidth*0.9, 33)), QColor(51, 153, 255));

    for (int i = 0; i < files.size(); ++i) {

        progressDialog->setValue(i+1);
        progressDialog->setLabelText(tr("Loading image number %1 of %2...").arg(i+1).arg(files.size()));       

        DiagramSceneInfo * info = new DiagramSceneInfo();

        if (progressDialog->wasCanceled()) {

            ui->fileListWidget->clear();
            ui->roisListWidget->clear();
            ui->subsamplingMonitor->clear();
            ui->imageTree->clear();
            scene->clear();
            subsampledItems.clear();
            ui->imageNameLabel->setText("");
            ui->subsamplingSlider->setEnabled(false);
            ui->subsamplingSlider->setValue(100);
            ui->subsamplingCheck->setChecked(false);
            //ui->subsamplingUpdateButton->setEnabled(false);
            ui->subsamplingValue->setText("100");
            ui->subsamplingValue->setEnabled(false);
            ui->fpsLabel->setEnabled(false);
            ui->fpsPreview->setEnabled(false);
            ui->playPreviewButton->setEnabled(false);
            ui->showROIsLabel->setEnabled(false);
            ui->showROIsCheckbox->setChecked(false);
            ui->showROIsCheckbox->setEnabled(false);
            ui->showOnlyLabeledROIsLabel->setEnabled(false);
            ui->showOnlyLabeledROIsCheckbox->setChecked(false);
            ui->showOnlyLabeledROIsCheckbox->setEnabled(false);
            ui->playPreviewProgressBar->setValue(0);
            ui->playPreviewProgressBar->setEnabled(false);
			ui->copyComboBox->setEnabled(false);
			ui->copyOptionsLabel->setEnabled(false);
			ui->copyROIsButton->setEnabled(false);
			ui->showFirstFrameButton->setEnabled(false);
			ui->showPreviousFrameButton->setEnabled(false);
			ui->showPreviousParentFrameButton->setEnabled(false);
			ui->showNextFrameButton->setEnabled(false);
			ui->copyOnNextCheck->setEnabled(false);
			ui->showNextParentFrameButton->setEnabled(false);
			ui->showLastFrameButton->setEnabled(false);
            previewScene->clear();
			treeItems.clear();

            break;
        }

//        QFile file(currentDir.absoluteFilePath(files[i]));
//        qint64 size = QFileInfo(file).size();
        //qDebug() << "Showing " << files[i] << ", size: " << QString::number(size) <<  endl;

        QListWidgetItem *pieceItem = new QListWidgetItem(ui->fileListWidget);
        //QDateTime date = QDateTime::currentDateTime();

        pieceItem->setText(files[i]);
        //pieceItem->setToolTip(QString::number(size));
        pieceItem->setTextAlignment(Qt::AlignBottom);

        /*QPixmap * fileImage = new QPixmap();
        fileImage->load(currentDir.absoluteFilePath(files[i]));
        info->image = fileImage;*/
		info->image = new QPixmap();
		info->image->load(currentDir.absoluteFilePath(files[i]));
        info->imageName = files[i];
        info->imagePath = currentDir.absoluteFilePath(files[i]);
//        info->imageSize = QString::number(size);

        QIcon fileIcon(*info->image);
        //fileIcon.setIconSize(QSize(50, 50));
        pieceItem->setIcon(fileIcon);

        //qDebug() << "Setting image for " << currentDir.absoluteFilePath(files[i]) << endl;
        pieceItem->setData(Qt::UserRole, QVariant(*info->image));
        pieceItem->setData(Qt::UserRole+1, currentDir.absoluteFilePath(files[i]));
        pieceItem->setData(Qt::UserRole+2, i);
        pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);

        //QTableWidgetItem *fileNameItem = new QTableWidgetItem(files[i]);
        //fileNameItem->setFlags(fileNameItem->flags() ^ Qt::ItemIsEditable);
        //QTableWidgetItem *sizeItem = new QTableWidgetItem(tr("%1 KB")
                                             //.arg(int((size + 1023) / 1024)));
        //sizeItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        //sizeItem->setFlags(sizeItem->flags() ^ Qt::ItemIsEditable);

        //int row = filesTable->rowCount();
        //filesTable->insertRow(row);
        //filesTable->setItem(row, 0, fileNameItem);
        //filesTable->setItem(row, 1, sizeItem);
        data->scenesInfos->append(info);

		GTTreeItem *gtTreeItem = new GTTreeItem();

        QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->imageTree);

        // QTreeWidgetItem::setText(int column, const QString & text)		
        QString treeLabel;
        treeLabel.sprintf("%03d", i+1);
		gtTreeItem->setFrameId(i+1);

        treeItem->setText(0, treeLabel);
        //treeItem->setIcon();
        treeItem->setText(1, files[i]);
        //treeItem->setText(2, "false");
		gtTreeItem->setRoiLabelsStatus(NO_ROIS);

        //treeItem->setBackgroundColor(0, QColor(51, 153, 255));
        //treeItem->setBackgroundColor(1, QColor(51, 153, 255));
        //treeItem->setBackgroundColor(2, QColor(51, 153, 255));

        treeItem->setTextAlignment(0, Qt::AlignCenter);
        treeItem->setTextAlignment(1, Qt::AlignCenter);
        treeItem->setTextAlignment(2, Qt::AlignCenter);

        treeItem->setData(0, Qt::UserRole, QVariant(*info->image));
        treeItem->setData(0, Qt::UserRole+2, i);
//        treeItem->setData(1, Qt::UserRole+2, i);
//        treeItem->setData(2, Qt::UserRole+2, i);
        treeItem->setIcon(1, fileIcon);
		gtTreeItem->setFrameImage(*info->image);
        //treeItem->setForeground(1, QBrush(fileImage));

		treeItems.append(gtTreeItem);

        QListWidgetItem *monitorItem = new QListWidgetItem(ui->subsamplingMonitor);
//        painter.setPen(Qt::transparent);
//        painter.setBrush(Qt::blue);        
        monitorItem->setData(Qt::UserRole+2, i);
        monitorItem->setIcon(QIcon(colorItem));
        monitorItem->setToolTip(files[i]);
        //monitorItem->setText("");

        subsampledItems.append(i);

        qApp->processEvents();
    }

//    QListWidgetItem *secondSpaceItem = new QListWidgetItem(ui->subsamplingMonitor);
//    QPixmap secondSpaceItemColor(spaceSize, 35);
//    QPainter painterSecond(&secondSpaceItemColor);
////        painter.setPen(Qt::transparent);
////        painter.setBrush(Qt::blue);
//    painterSecond.fillRect(QRect(QPoint(0,0), QPoint(spaceSize, 35)), Qt::white);
//    secondSpaceItem->setIcon(QIcon(secondSpaceItemColor));    

    QString totalLabel;
    totalLabel.sprintf("Total frames: %d", files.size());
    ui->totalFramesLabel->setEnabled(true);
    ui->totalFramesLabel->setText(totalLabel);

    QString showingLabel;
    showingLabel.sprintf("Showing  %d  frames of  %d - %.1f%", files.size(), files.size(), 100.0);
    ui->showingFramesLabel->setEnabled(true);
    ui->showingFramesLabel->setText(showingLabel);

    ui->fpsLabel->setEnabled(true);
    ui->fpsPreview->setEnabled(true);
    ui->playPreviewButton->setEnabled(true);    
    ui->playPreviewProgressBar->setEnabled(true);
    ui->playPreviewProgressBar->setValue(0);
    ui->showROIsLabel->setEnabled(true);
    ui->showROIsCheckbox->setChecked(false);
    ui->showROIsCheckbox->setEnabled(true);
    //filesFoundLabel->setText(tr("%1 file(s) found").arg(files.size()) +
   //filesFoundLabel->setWordWrap(true);
	updateTreeWidget();
	updateImage(0);
	
	if(QDir(currentDir.absolutePath() + "\\bgs\\0\\").exists()) {
		ui->loadBGSData->setEnabled(true);
		/*ui->previewBGSCheckTagging->setEnabled(true);
		ui->previewFrameAndBGSCheckTagging->setEnabled(true);
		ui->previewBGSCheck->setEnabled(true);
		ui->previewFrameAndBGSCheck->setEnabled(true);
		ui->useBGSCheck->setEnabled(true);*/
	} else {
		ui->loadBGSData->setEnabled(false);
		/*ui->previewBGSCheckTagging->setEnabled(false);
		ui->previewFrameAndBGSCheckTagging->setEnabled(false);
		ui->previewBGSCheck->setEnabled(false);
		ui->previewFrameAndBGSCheck->setEnabled(false);
		ui->useBGSCheck->setEnabled(false);*/
	}

	ui->globalTabs->setTabEnabled(0, true);
	ui->globalTabs->setTabEnabled(1, true);
	ui->globalTabs->setTabEnabled(2, true);
	ui->globalTabs->setTabEnabled(3, true);
	ui->globalTabs->setTabEnabled(4, true);
	ui->globalTabs->setTabEnabled(5, true);

	progressDialog->hide();	
}

void TaggingWidget::updateFiles(int index)
{    
    progressDialog->show();
    progressDialog->setCancelButtonText(tr("&Cancel"));
    progressDialog->setRange(0, data->scenesInfos->size());
    progressDialog->setWindowTitle(tr("Updating Images..."));

	for (int i = 0; i < data->scenesInfos->size(); ++i) {
        progressDialog->setValue(i+1);
        progressDialog->setLabelText(tr("Updating image number %1 of %2...").arg(i+1).arg(data->scenesInfos->size()));

        if (progressDialog->wasCanceled()) {
			progressDialog->hide();
            return;
        }
		
		QTreeWidgetItem *treeItem = ui->imageTree->topLevelItem(i);
				
		if(treeItem->isHidden()) {
			int division = subsamplingStep==0?0:i/subsamplingStep;
			int parentIndex = division*subsamplingStep;
			int childIndex = i - parentIndex - 1;
			treeItem = ui->imageTree->topLevelItem(parentIndex)->child(childIndex);
		}

		if(ui->previewBGSCheckTagging->isChecked() && bgsLoaded) {
			treeItem->setData(0, Qt::UserRole, QVariant(*data->scenesInfos->at(i)->bgsMask));
			treeItem->setIcon(1, QIcon(*data->scenesInfos->at(i)->bgsMask));
		} else if(ui->previewFrameAndBGSCheckTagging->isChecked() && bgsLoaded) {
			treeItem->setData(0, Qt::UserRole, QVariant(*data->scenesInfos->at(i)->imageAndBgsMask));
			treeItem->setIcon(1, QIcon(*data->scenesInfos->at(i)->imageAndBgsMask));
		} else { // ui->previewFrameCheckTagging->isChecked()
			treeItem->setData(0, Qt::UserRole, QVariant(*data->scenesInfos->at(i)->image));
			treeItem->setIcon(1, QIcon(*data->scenesInfos->at(i)->image));
		}
        
        qApp->processEvents();
    }

	updateTreeWidget();
	updateImage(index);
		
	progressDialog->hide();	
}

void TaggingWidget::on_fileListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //imageArea->clearSelection();
    int index = item->data(Qt::UserRole+2).toString().toInt();
    ui->subsamplingMonitor->setCurrentRow(index);

    if(ui->imageTree->topLevelItem(index)->isHidden()) {
        int division = subsamplingStep==0?0:index/subsamplingStep;
//                qDebug() << "division: " << division << endl;

        int parentIndex = division*subsamplingStep;
//                qDebug() << "parentIndex: " << parentIndex << endl;

        int childIndex = index - parentIndex - 1;
//                qDebug() << "childIndex: " << childIndex << endl;

//                qDebug() << "subsamplingStep:" << subsamplingStep << endl;
//                qDebug() << "calculusIndex:" << calculusIndex << endl;
        //ui->imageTree->collapseAll();
        ui->imageTree->topLevelItem(parentIndex)->child(childIndex)->setExpanded(true);
        ui->imageTree->setCurrentItem(ui->imageTree->topLevelItem(parentIndex)->child(childIndex));
        ui->imageTree->scrollToItem(ui->imageTree->topLevelItem(parentIndex)->child(childIndex));
    } else {
//                qDebug() << "not hidden..." << endl;
        //ui->imageTree->collapseAll();
        ui->imageTree->setCurrentItem(ui->imageTree->topLevelItem(index));
        ui->imageTree->scrollToItem(ui->imageTree->topLevelItem(index));
    }

    updateImage(index);
}

void TaggingWidget::updateImage(int index) {
//    QString filename = item->data(Qt::UserRole+1).toString();    
//    qDebug() << "Showing image: " << filename << endl;
//    qDebug() << "Showing index: " << index << endl;

//    QPixmap pix( filename );        

    data->currentSceneInfoIndex = index;

	if(data->currentSceneInfoIndex == 0) {
		ui->showPreviousFrameButton->setEnabled(false);
		ui->showPreviousParentFrameButton->setEnabled(false);
		ui->showFirstFrameButton->setEnabled(false);
		ui->showNextFrameButton->setEnabled(true);
		ui->copyOnNextCheck->setEnabled(true);
		if(ui->subsamplingCheck->isChecked() && subsamplingStep > 0) {
			ui->showNextParentFrameButton->setEnabled(true);
		} else {
			ui->showNextParentFrameButton->setEnabled(false);
		}
		ui->showLastFrameButton->setEnabled(true);
	} else if((data->currentSceneInfoIndex >= 1) && data->currentSceneInfoIndex < (data->scenesInfos->size()-1)) {
		int division = subsamplingStep==0?0:data->currentSceneInfoIndex/subsamplingStep;
        int parentIndex = division*subsamplingStep;
        int childIndex = data->currentSceneInfoIndex - parentIndex - 1;

		if((parentIndex - subsamplingStep) >= 0 && ((data->currentSceneInfoIndex) > 0) && ui->subsamplingCheck->isChecked()) {
			ui->showPreviousParentFrameButton->setEnabled(true);
		} else {
			ui->showPreviousParentFrameButton->setEnabled(false);
		}

		QTreeWidgetItem *treeItem = ui->imageTree->topLevelItem(data->currentSceneInfoIndex);
		if(treeItem->isHidden()) {
			if((parentIndex + subsamplingStep) <= (data->scenesInfos->size()-1) && ui->subsamplingCheck->isChecked() && subsamplingStep > 0) {
				ui->showNextParentFrameButton->setEnabled(true);
			} else {
				ui->showNextParentFrameButton->setEnabled(false);
			}
		} else {
			if((data->currentSceneInfoIndex + subsamplingStep) <= (data->scenesInfos->size()-1)  && ui->subsamplingCheck->isChecked() && subsamplingStep > 0) {
				ui->showNextParentFrameButton->setEnabled(true);
			} else {
				ui->showNextParentFrameButton->setEnabled(false);
			}
		}

		ui->showFirstFrameButton->setEnabled(true);
		ui->showPreviousFrameButton->setEnabled(true);
		ui->showNextFrameButton->setEnabled(true);
		ui->copyOnNextCheck->setEnabled(true);
		ui->showLastFrameButton->setEnabled(true);
	} else if(data->currentSceneInfoIndex == (data->scenesInfos->size()-1)) {
		ui->showFirstFrameButton->setEnabled(true);
		ui->showPreviousFrameButton->setEnabled(true);
		if(ui->subsamplingCheck->isChecked()) {
			ui->showPreviousParentFrameButton->setEnabled(true);	
		} else {
			ui->showPreviousParentFrameButton->setEnabled(false);
		}
		
		ui->showNextFrameButton->setEnabled(false);
		ui->copyOnNextCheck->setEnabled(false);
		ui->showNextParentFrameButton->setEnabled(false);
		ui->showLastFrameButton->setEnabled(false);
	}

	ui->fileListWidget->setCurrentRow(data->currentSceneInfoIndex);
	ui->subsamplingMonitor->setCurrentRow(data->currentSceneInfoIndex);
	
	if(ui->imageTree->topLevelItem(data->currentSceneInfoIndex)->isHidden()) {
        int division = subsamplingStep==0?0:data->currentSceneInfoIndex/subsamplingStep;
//                qDebug() << "division: " << division << endl;

        int parentIndex = division*subsamplingStep;
//                qDebug() << "parentIndex: " << parentIndex << endl;

        int childIndex = data->currentSceneInfoIndex - parentIndex - 1;
//                qDebug() << "childIndex: " << childIndex << endl;

//                qDebug() << "subsamplingStep:" << subsamplingStep << endl;
//                qDebug() << "calculusIndex:" << calculusIndex << endl;
        //ui->imageTree->collapseAll();
        ui->imageTree->topLevelItem(parentIndex)->child(childIndex)->setExpanded(true);
        ui->imageTree->setCurrentItem(ui->imageTree->topLevelItem(parentIndex)->child(childIndex));
        ui->imageTree->scrollToItem(ui->imageTree->topLevelItem(parentIndex)->child(childIndex));
    } else {
//                qDebug() << "not hidden..." << endl;
        //ui->imageTree->collapseAll();
        ui->imageTree->setCurrentItem(ui->imageTree->topLevelItem(data->currentSceneInfoIndex));
        ui->imageTree->scrollToItem(ui->imageTree->topLevelItem(data->currentSceneInfoIndex));
    }

    //qDebug() << "data->currentSceneInfoIndex" << data->currentSceneInfoIndex << endl;
    //scene->currentSceneInfo = data->scenesInfos->at(data->currentSceneInfoIndex);

    scene->clear();
    //ui->imageNameLabel->setText(data->scenesInfos->at(data->currentSceneInfoIndex)->imageName + " - " + data->scenesInfos->at(data->currentSceneInfoIndex)->imagePath);
	QString frameLabel;
    frameLabel.sprintf("Frame %03d", data->currentSceneInfoIndex+1);
	ui->imageNameLabel->setText(frameLabel + " - " + data->scenesInfos->at(data->currentSceneInfoIndex)->imageName);

	if(ui->previewBGSCheckTagging->isChecked() && bgsLoaded) {
		scene->addPixmap( *data->scenesInfos->at(data->currentSceneInfoIndex)->bgsMask );
		scene->setSceneRect(QRectF(0, 0, data->scenesInfos->at(data->currentSceneInfoIndex)->bgsMask->width(), data->scenesInfos->at(data->currentSceneInfoIndex)->bgsMask->height()));
	} else if(ui->previewFrameAndBGSCheckTagging->isChecked() && bgsLoaded) {
		scene->addPixmap( *data->scenesInfos->at(data->currentSceneInfoIndex)->imageAndBgsMask );
		scene->setSceneRect(QRectF(0, 0, data->scenesInfos->at(data->currentSceneInfoIndex)->imageAndBgsMask->width(), data->scenesInfos->at(data->currentSceneInfoIndex)->imageAndBgsMask->height()));
	} else { // ui->previewFrameCheckTagging->isChecked()
		scene->addPixmap( *data->scenesInfos->at(data->currentSceneInfoIndex)->image );
		scene->setSceneRect(QRectF(0, 0, data->scenesInfos->at(data->currentSceneInfoIndex)->image->width(), data->scenesInfos->at(data->currentSceneInfoIndex)->image->height()));
	}

//    qDebug() << "loading sceneInfo for " << data->currentSceneInfoIndex << endl;
//    qDebug() << "data->scenesInfos->at(data->currentSceneInfoIndex)->rois.size() " << data->scenesInfos->at(data->currentSceneInfoIndex)->rois->size() << endl;

    data->roiCounter = data->scenesInfos->at(data->currentSceneInfoIndex)->rois->size();
    scene->roiTable->setRowCount(0);
    ui->roisListWidget->clear();
    ui->roisListWidget->setIconSize(QSize(300, 400));

    for(int i=0; i<data->scenesInfos->at(data->currentSceneInfoIndex)->rois->size();i++) {
        DiagramROI * roi = data->scenesInfos->at(data->currentSceneInfoIndex)->rois->at(i);

//        qDebug() << "roi->getIndex() " << roi->getIndex() << endl;
//        qDebug() << "roi->getLabel() " << roi->getLabel() << endl;
//        qDebug() << "roi->getColor() " << roi->getColor().name() << endl;
//        qDebug() << "roi->getWidth() " << roi->getWidth() << endl;
//        qDebug() << "roi->getHeight() " << roi->getHeight() << endl;
//        qDebug() << "roi->getTpx() " << roi->getTpx() << endl;
//        qDebug() << "roi->getTpy() " << roi->getTpy() << endl;
//        qDebug() << "roi->getBrx() " << roi->getBrx() << endl;
//        qDebug() << "roi->getBry() " << roi->getBry() << endl;

        if(!roi->isRemoved()) {
            DiagramItem *itemToAdd = new DiagramItem(*roi, i, scene->roiTable, scene->roiList, NULL, NULL);
            scene->addItem(itemToAdd);
    //        qDebug() << "***item added!" << endl;
    //        qDebug() << "roi table[4]: " << bryItem->text() << endl;
        }

        QString itemLabel;
        itemLabel.sprintf("%03d", roi->getIndex());
		qDebug() << "roi index " << roi->getIndex() << endl;

        QTableWidgetItem *roiNameItem = new QTableWidgetItem(itemLabel);
        roiNameItem->setFlags(roiNameItem->flags() ^ Qt::ItemIsEditable);
        roiNameItem->setTextAlignment(Qt::AlignCenter);

        QTableWidgetItem *labelItem = new QTableWidgetItem(roi->getLabel());
        labelItem->setFlags(labelItem->flags() ^ Qt::ItemIsEditable);
        labelItem->setTextAlignment(Qt::AlignCenter);

        QTableWidgetItem *widthItem = new QTableWidgetItem(QString::number(roi->getWidth(), 'f', 0));
        widthItem->setFlags(widthItem->flags() ^ Qt::ItemIsEditable);
        widthItem->setTextAlignment(Qt::AlignCenter);

        QTableWidgetItem *heightItem = new QTableWidgetItem(QString::number(roi->getHeight(), 'f', 0));
        heightItem->setFlags(heightItem->flags() ^ Qt::ItemIsEditable);
        heightItem->setTextAlignment(Qt::AlignCenter);

        QTableWidgetItem *tpxItem = new QTableWidgetItem(QString::number(roi->getTpx(), 'f', 0));
        tpxItem->setFlags(tpxItem->flags() ^ Qt::ItemIsEditable);
        tpxItem->setTextAlignment(Qt::AlignCenter);

        QTableWidgetItem *tpyItem = new QTableWidgetItem(QString::number(roi->getTpy(), 'f', 0));
        tpyItem->setFlags(tpyItem->flags() ^ Qt::ItemIsEditable);
        tpyItem->setTextAlignment(Qt::AlignCenter);

        QTableWidgetItem *brxItem = new QTableWidgetItem(QString::number(roi->getBrx(), 'f', 0));
        brxItem->setFlags(brxItem->flags() ^ Qt::ItemIsEditable);
        brxItem->setTextAlignment(Qt::AlignCenter);

        QTableWidgetItem *bryItem = new QTableWidgetItem(QString::number(roi->getBry(), 'f', 0));
        bryItem->setFlags(bryItem->flags() ^ Qt::ItemIsEditable);
        bryItem->setTextAlignment(Qt::AlignCenter);

        scene->roiTable->insertRow(roi->getIndex());

        if(roi->isRemoved()) {
            scene->roiTable->hideRow(roi->getIndex());
        } else {
            scene->roiTable->setItem(roi->getIndex(), 0, roiNameItem);
    //        qDebug() << "roi table[0]: " << roiNameItem->text() << endl;

            scene->roiTable->setItem(roi->getIndex(), 1, labelItem);

            scene->roiTable->setItem(roi->getIndex(), 2, widthItem);

            scene->roiTable->setItem(roi->getIndex(), 3, heightItem);

            scene->roiTable->setItem(roi->getIndex(), 4, tpxItem);
    //        qDebug() << "roi table[1]: " << tpxItem->text() << endl;

            scene->roiTable->setItem(roi->getIndex(), 5, tpyItem);
    //        qDebug() << "roi table[2]: " << tpyItem->text() << endl;

            scene->roiTable->setItem(roi->getIndex(), 6, brxItem);
    //        qDebug() << "roi table[3]: " << brxItem->text() << endl;

            scene->roiTable->setItem(roi->getIndex(), 7, bryItem);
        }
		
        QListWidgetItem *roiItem = new QListWidgetItem(ui->roisListWidget);

		if(roi->isRemoved()) {
			roiItem->setHidden(true);
		}

        roiItem->setText(roi->getLabel() + " " + itemLabel);
        roiItem->setTextColor(roi->isLabeled()?roi->getColor():Qt::black);
        roiItem->setFont(roiItemFont);
        roiItem->setData(Qt::UserRole, roi->getIndex());
        roiItem->setData(Qt::UserRole+1, roi->getTpx());
        roiItem->setData(Qt::UserRole+2, roi->getTpy());
        roiItem->setData(Qt::UserRole+3, roi->getWidth());
        roiItem->setData(Qt::UserRole+4, roi->getHeight());
        //roiItem->setBackground(roi->isLabeled()?roi->getColor():Qt::white);

		if(ui->previewBGSCheckTagging->isChecked() && bgsLoaded) {
			roiItem->setIcon(QIcon(data->scenesInfos->at(data->currentSceneInfoIndex)->bgsMask->copy(roi->getTpx(), roi->getTpy(), roi->getWidth(), roi->getHeight()).scaledToHeight(roi->getHeight()*2)));
		} else if(ui->previewFrameAndBGSCheckTagging->isChecked() && bgsLoaded) {
			roiItem->setIcon(QIcon(data->scenesInfos->at(data->currentSceneInfoIndex)->imageAndBgsMask->copy(roi->getTpx(), roi->getTpy(), roi->getWidth(), roi->getHeight()).scaledToHeight(roi->getHeight()*2)));
		} else { // ui->previewFrameCheckTagging->isChecked()
			roiItem->setIcon(QIcon(data->scenesInfos->at(data->currentSceneInfoIndex)->image->copy(roi->getTpx(), roi->getTpy(), roi->getWidth(), roi->getHeight()).scaledToHeight(roi->getHeight()*2)));
		}

        roiItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        roiItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);

		//treeItems
    }

    //ui->roisListWidget->sortItems();
    data->showingImage = true;

//    imageArea->zoomImage(0.0);
//    imageArea->open(filename);
//    imageArea->zoomImage(2.0);
//    imageArea->repaint();
//    DataSingleton::Instance()->setInstrument(CURSOR);

	ui->copyComboBox->setEnabled(true);
	ui->copyOptionsLabel->setEnabled(true);
	ui->copyROIsButton->setEnabled(true);

	updateRoiCopyOptions(index);

    scene->roiList = ui->roisListWidget;
	updateTreeWidget();
    qApp->processEvents();
}

void TaggingWidget::on_labelsListWidget_itemPressed(QListWidgetItem *item)
{
//    qDebug() << "Item list pressed!" << endl;
//    QDrag *drag = new QDrag(this);
//    QMimeData *mimeData = new QMimeData;

//    mimeData->setText(item->text());
//    drag->setMimeData(mimeData);
//    drag->setPixmap(qvariant_cast<QPixmap>(item->data(Qt::UserRole+3)));

//    drag->exec();

    QDrag *drag = new QDrag(this);
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);

    drag->setPixmap(qvariant_cast<QPixmap>(item->data(Qt::UserRole+3)));

	data->labelSelected = true;
	data->currentLabelColor = qvariant_cast<QColor>(item->data(Qt::UserRole));
	data->currentLabelString = item->data(Qt::UserRole+1).toString();
	data->currentLabelId = item->data(Qt::UserRole+2).toInt();

    mime->setColorData(data->currentLabelColor);
    mime->setText(item->text());
	mime->setProperty("id", item->data(Qt::UserRole+2));
	ui->currentLabelColor->setText(data->currentLabelString);

	int d = 0;
    // Counting the perceptive luminance - human eye favors green color... 
	double a = 1 - ( 0.299 * data->currentLabelColor.red() + 0.587 * data->currentLabelColor.green() + 0.114 * data->currentLabelColor.blue())/255;

	QString textColor = "white";

    if (a < 0.5)
       textColor = "black"; // bright colors - black font
    else
       textColor = "white"; // dark colors - white font	

	ui->currentLabelColor->setStyleSheet("background-color:" + data->currentLabelColor.name()+";" + "color: " + textColor +";");

//    qDebug() << "item->text()" << item->text() << endl;
    drag->exec();
}

void TaggingWidget::deleteItem()
{
    qDebug() << "deleteItem" << endl;
    foreach (QGraphicsItem *item, scene->selectedItems()) {
         int removedIndex = qgraphicsitem_cast<DiagramItem *>(item)->itemIndex;
         scene->roiTable->hideRow(removedIndex);
		 ui->roisListWidget->setRowHidden(removedIndex, true);
         scene->removeItem(item);
         data->scenesInfos->at(data->currentSceneInfoIndex)->rois->at(removedIndex)->setRemoved(true);
         delete item;
     }
}

void TaggingWidget::on_roiTable_itemPressed(QTableWidgetItem *item) {
//    qDebug() << "selected row: " << item->row() << endl;
//    qDebug() << "selected value: " << item->text() << endl;
}

void TaggingWidget::selectItemFromModel(const QAbstractItemModel * model, int row) {
    double tpx = model->data(model->index(row, 4), Qt::DisplayRole).toString().toDouble();
    double tpy = model->data(model->index(row, 5), Qt::DisplayRole).toString().toDouble();
    double brx = model->data(model->index(row, 6), Qt::DisplayRole).toString().toDouble();
    double bry = model->data(model->index(row, 7), Qt::DisplayRole).toString().toDouble();

    //qDebug() << "--model row:" << model->data(model->index(index.row(),0), Qt::DisplayRole).toString() << endl;
//    qDebug() << "tpx " << tpx << endl;
//    qDebug() << "tpy " << tpy << endl;
//    qDebug() << "brx " << brx << endl;
//    qDebug() << "bry " << bry << endl;

    DiagramItem * item = qgraphicsitem_cast<DiagramItem *>(scene->itemAt((tpx+brx)/2, (tpy+bry)/2));

    if(item != NULL) {
//        qDebug() << "item found!" << endl;
        scene->clearSelection();
        item->setSelected(true);		
    }
}

void TaggingWidget::on_roiTable_pressed(const QModelIndex &index) {
//    qDebug() << "--selected row: " << index.row() << endl;

    selectItemFromModel(index.model(), index.row());
}


void TaggingWidget::addLabel(int id, QString label, QColor color, bool appendToSceneLabels) {
	FileProcessor fileProcessor = FileProcessor();
	label = fileProcessor.removeForbiddenChars(label);

	if(appendToSceneLabels) {
		DiagramROILabel *sceneLabel = new DiagramROILabel();

		sceneLabel->setRemoved(false);
		sceneLabel->setColor(color);
		sceneLabel->setName(label);
		sceneLabel->setId(id);
		data->scenesLabels->append(sceneLabel);
	}	

    QPixmap colorItemButton(50,50);
    QPainter painterButton(&colorItemButton);
    painterButton.setBrush(color);
    painterButton.drawRect(QRect(QPoint(0,0), QPoint(50, 50) - QPoint(2,2)));
    ui->selectLabelColor->setIcon(QIcon(colorItemButton));

    ColorListWidgetItem *pieceItem = new ColorListWidgetItem(ui->labelsListWidget);
	ColorListWidgetItem *pieceItemTagging = new ColorListWidgetItem(ui->labelsListWidgetTagging);
			
    QPixmap colorItem(100,100);

    QPainter painter(&colorItem);

    pieceItem->setText(label);
    pieceItem->setToolTip(label);
    pieceItem->setTextAlignment(Qt::AlignVCenter);

	pieceItemTagging->setText(label);			
    pieceItemTagging->setToolTip(label);
    pieceItemTagging->setTextAlignment(Qt::AlignVCenter);

    //painter.setBrush(Qt::SolidPattern);
    //painter.setPen(QPen(color, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(color);
    //painter.setPen(Qt::darkGreen);
    painter.drawRect(QRect(QPoint(0,0), QPoint(100,100) - QPoint(2,2)));

	int d = 0;
	// Counting the perceptive luminance - human eye favors green color... 
	double a = 1 - ( 0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue())/255;

	QColor textColor = Qt::white;

	if (a < 0.5)
		textColor = Qt::black; // bright colors - black font
	else
		textColor = Qt::white; // dark colors - white font	

	painter.setPen(QPen(QBrush(textColor), 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    painter.setFont(QFont("Newyork", 25));

	if(id < 10) {
		painter.drawText(QPoint(40,60), QString::number(id+1));
	} else {
		painter.drawText(QPoint(35,60), QString::number(id+1));
	}

    pieceItem->setData(Qt::UserRole, color);
    pieceItem->setData(Qt::UserRole+1, label);
	pieceItem->setData(Qt::UserRole+2, id);
    pieceItem->setData(Qt::UserRole+3, colorItem);
    pieceItem->setIcon(QIcon(colorItem));
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);

	pieceItemTagging->setData(Qt::UserRole, color);
    pieceItemTagging->setData(Qt::UserRole+1, label);
	pieceItemTagging->setData(Qt::UserRole+2, id);
    pieceItemTagging->setData(Qt::UserRole+3, colorItem);
    pieceItemTagging->setIcon(QIcon(colorItem));
    pieceItemTagging->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
}

void TaggingWidget::on_addLabel_clicked()
{
    if(!ui->labelToAdd->text().isEmpty()) {

        QString label = ui->labelToAdd->text().toUpper();

        if(ui->labelsListWidget->findItems(label, Qt::MatchExactly).size() == 0) {
			addLabel(data->sceneLabelsCounter++, label, colorToAdd, true);
        }
    }
}

void TaggingWidget::on_selectLabelColor_clicked()
{
    QColor selectedColor = colorDialog->getColor(colorToAdd);

//    qDebug() << "colorToAdd " << colorToAdd << endl;
//    qDebug() << "selected color " << selectedColor << endl;

    if(selectedColor != colorToAdd) {
        manualColor = true;
//        qDebug() << "colors different!" << endl;
        colorToAdd = selectedColor;
        QPixmap colorItemButton(50,50);
        QPainter painterButton(&colorItemButton);
        painterButton.setBrush(colorToAdd);
        painterButton.drawRect(QRect(QPoint(0,0), QPoint(50, 50) - QPoint(2,2)));
        ui->selectLabelColor->setIcon(QIcon(colorItemButton));
        on_addLabel_clicked();
    }
}

void TaggingWidget::sceneSelectionChanged() {
//    qDebug() << "scene selection changed!" << endl;
//    qDebug() << "scene->selectedItems().size() " << scene->selectedItems().size() << endl;
//    qDebug() << "scene->items().size() " << scene->items().size() << endl;

    for(int i=0; i<scene->items().size()-1; i++) {
        //qDebug() << "item.at(" << i << ") " << scene->items().at(i)->type() << endl;		
        DiagramItem *item = qgraphicsitem_cast<DiagramItem *>(scene->items().at(i));
		//qDebug() << "item" << item << endl;
		//qDebug() << "scene->items().at(i)" << scene->items().at(i) << endl;		
		//qDebug() << "item index" << item->itemIndex << endl;

        if(item->isSelected()) {
            item->setSelectedPen();
        } else {
            item->setUnselectedPen();
        }
    }
}

void TaggingWidget::on_subsamplingCheck_toggled(bool checked)
{
//    if(checked) {
//        qDebug() << "subsampling enabled!" << endl;
//    } else {
//        qDebug() << "subsampling disabled!" << endl;
//    }

    ui->subsamplingSlider->setEnabled(checked);
    ui->subsamplingValue->setEnabled(checked);
    //ui->subsamplingUpdateButton->setEnabled(checked);

    if(!checked) {
        ui->subsamplingValue->setText(QString::number(100));
        ui->subsamplingSlider->setValue(100);
        on_subsamplingUpdateButton_clicked();
    } else {
        ui->subsamplingValue->setText(QString::number(ui->subsamplingSlider->value()));
    }
}

void TaggingWidget::on_subsamplingSlider_valueChanged(int value)
{
    //qDebug() << "changing subsampling to " << value << endl;
    ui->subsamplingValue->setText(QString::number(value));
    //ui->subsamplingSlider->setToolTip(QString::number(value));
    QToolTip::showText(mapFromGlobal(QCursor::pos()+QPoint(40,-20)), QString::number(value), ui->subsamplingSlider);
//    on_subsamplingUpdateButton_clicked();
}

void TaggingWidget::on_subsamplingUpdateButton_clicked()
{
    int subsamplingValue = ui->subsamplingValue->text().toInt();

    ui->subsamplingSlider->setValue(subsamplingValue);

//    qDebug() << "subsamplit at " << subsamplingValue << endl;

    imagesLength = data->scenesInfos->size();    

    if(imagesLength > 0) {
    //    qDebug() << "prior gridWidth" << gridWidth << endl;
        //gridWidth = (double)ui->subsamplingMonitor->width()/imagesLength;
    //    qDebug() << "after gridWidth" << gridWidth << endl;

        subsampledItems.clear();
        previewScene->clear();
        ui->playPreviewProgressBar->setValue(0);

//        qDebug() << "subsamplingValue" << subsamplingValue << endl;

        double subsamplingStepDouble = subsamplingValue!=0?imagesLength/(double)(imagesLength*subsamplingValue/100):0;

//        qDebug() << "subsamplingStepDouble" << subsamplingStepDouble << endl;

        subsamplingStep = (int) subsamplingStepDouble;

//        qDebug() << "subsamplingStep" << subsamplingStep << endl;

        int subsampledCounter = 0;

//        qDebug() << "subsamplingStep" << subsamplingStep << endl;

        if(subsamplingStep > 0 && subsamplingStep <= imagesLength) {
    //        ui->subsamplingMonitor->setGridSize(QSize(gridWidth, 33));
    //        ui->subsamplingMonitor->setIconSize(QSize(gridWidth, 33));

            int subsamplingAmount = imagesLength/subsamplingStep;
            
            progressDialog->show();
            progressDialog->setCancelButtonText(tr("&Cancel"));
            progressDialog->setRange(0, subsamplingAmount);
            progressDialog->setWindowTitle(tr("Subsampling images..."));

    //        for(int i=0;i<imagesLength; i=i+subsamplingStep) {
    //            subsampledCounter++;
    //            progressDialog->setValue(subsampledCounter);
    //            progressDialog->setLabelText(tr("Subsampling image number %1 of %2...").arg(subsampledCounter).arg(subsamplingAmount));
    //            qApp->processEvents();

    //            qDebug() << "image(" <<  i << ")" << endl;

    //            ui->subsamplingMonitor->setCurrentRow(i);

    //            QListWidgetItem *monitorItem = ui->subsamplingMonitor->currentItem();

    //            QPixmap colorItem(gridWidth, 33);
    //            QPainter painter(&colorItem);
    //        //        painter.setPen(Qt::transparent);
    //        //        painter.setBrush(Qt::blue);
    //            painter.fillRect(QRect(QPoint(0,0), QPoint(gridWidth-1, 35)), Qt::red);
    //            monitorItem->setIcon(QIcon(colorItem));
    //        }
    //        ui->subsamplingMonitor->setCurrentRow(-1);
            int lastSubsamplingParentIndex = 0;
//            int lastSubsamplingParentCounter = 0;

            for(int i=0;i<imagesLength; i++) {
//                qDebug() << "image(" <<  i << ")" << endl;

                ui->subsamplingMonitor->setCurrentRow(i);
                QListWidgetItem *monitorItem = ui->subsamplingMonitor->currentItem();

                QTreeWidgetItem *treeItem = ui->imageTree->topLevelItem(i);
                QTreeWidgetItem *lastParentItem;
				GTTreeItem * gtTreeItem = treeItems.at(i);

                QPixmap colorItem(gridWidth*0.9, 33);
                QPainter painter(&colorItem);
                painter.setRenderHint(QPainter::Antialiasing);

            //        painter.setPen(Qt::transparent);
            //        painter.setBrush(Qt::blue);
                if(i%subsamplingStep==0) {
                    lastSubsamplingParentIndex = i;
                    subsampledItems.append(i);
//                    qDebug() << "setting lastSubsamplingParentIndex to " << lastSubsamplingParentIndex << endl;
                    lastParentItem = ui->imageTree->topLevelItem(lastSubsamplingParentIndex);
                    lastParentItem->takeChildren();
//                    lastSubsamplingParentCounter = 0;
                    subsampledCounter++;

                    painter.fillRect(QRect(QPoint(0,0), QPoint(gridWidth*0.9, 33)), QColor(51, 153, 255));

//                    QString treeLabel;
//                    treeLabel.sprintf("%03d", i+1);

//                    treeItem->setText(0, treeLabel);
//                    treeItem->setText(1, files[i]);
//                    treeItem->setText(2, "false");
										
					gtTreeItem->setParent(true);

                    treeItem->setHidden(false);
                    /*treeItem->setBackgroundColor(0, QColor(51, 153, 255));
                    treeItem->setBackgroundColor(1, QColor(51, 153, 255));*/
                    treeItem->setBackgroundColor(2, QColor(255, 69, 0));

//                    treeItem->setTextAlignment(0, Qt::AlignCenter);
//                    treeItem->setTextAlignment(1, Qt::AlignCenter);
//                    treeItem->setTextAlignment(2, Qt::AlignCenter);

                    if(subsampledCounter <= subsamplingAmount) {
                        progressDialog->setValue(subsampledCounter);
                        progressDialog->setLabelText(tr("Subsampling image number %1 of %2...").arg(subsampledCounter).arg(subsamplingAmount));
//                        qDebug() << "subsampledCounter " << subsampledCounter << endl;
//                        qDebug() << "subsamplingAmount " << subsamplingAmount << endl;                                                
                    }

                    qApp->processEvents();
                } else {
                    painter.fillRect(QRect(QPoint(0,0), QPoint(gridWidth*0.9, 33)), Qt::white);

                    if(lastParentItem != NULL) {
                        //ui->imageTree->takeTopLevelItem(i);
//                        qDebug() << "adding child " << i << " to parent " << lastSubsamplingParentIndex << endl;
						gtTreeItem->setParent(false);

						treeItem->setHidden(true);
                        treeItem->takeChildren();
                        QTreeWidgetItem *clonedChild = treeItem->clone();
                        /*clonedChild->setBackgroundColor(0, Qt::white);
                        clonedChild->setBackgroundColor(1, Qt::white);*/
                        //clonedChild->setBackgroundColor(2, Qt::white);
						clonedChild->setBackgroundColor(2, QColor(255, 69, 0));
                        //clonedChild->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
                        lastParentItem->addChild(clonedChild);
                    }
//                    lastSubsamplingParentCounter++;
                }
                monitorItem->setIcon(QIcon(colorItem));
            }
            ui->subsamplingMonitor->setCurrentRow(-1);
            progressDialog->hide();
//            qApp->processEvents();
			ui->showNextParentFrameButton->setEnabled(true);
			ui->showPreviousParentFrameButton->setEnabled(true);
        } else {
            subsamplingStep = 0;
            ui->subsamplingMonitor->setCurrentRow(0);
            //QListWidgetItem *monitorItem = ui->subsamplingMonitor->currentItem();
            QTreeWidgetItem *lastParentItem = ui->imageTree->topLevelItem(0);

            QPixmap colorItem(gridWidth*0.9, 33);
            QPainter painter(&colorItem);
            painter.setRenderHint(QPainter::Antialiasing);

            subsampledItems.append(0);
            lastParentItem->takeChildren();
            painter.fillRect(QRect(QPoint(0,0), QPoint(gridWidth*0.9, 33)), QColor(51, 153, 255));

			GTTreeItem * gtTreeItem = treeItems.at(0);
			gtTreeItem->setParent(true);
            lastParentItem->setHidden(false);
            //lastParentItem->setBackgroundColor(0, QColor(51, 153, 255));
            //lastParentItem->setBackgroundColor(1, QColor(51, 153, 255));
            lastParentItem->setBackgroundColor(2, QColor(255, 69, 0));

            qApp->processEvents();

            for(int i=1; i<imagesLength; i++) {
                painter.fillRect(QRect(QPoint(0,0), QPoint(gridWidth*0.9, 33)), Qt::white);

                if(lastParentItem != NULL) {
                    QTreeWidgetItem *treeItem = ui->imageTree->topLevelItem(i);
					gtTreeItem = treeItems.at(i);
					gtTreeItem->setParent(false);
                    treeItem->setHidden(true);
                    treeItem->takeChildren();
                    QTreeWidgetItem *clonedChild = treeItem->clone();
                    clonedChild->setBackgroundColor(0, Qt::white);
                    clonedChild->setBackgroundColor(1, Qt::white);
                    clonedChild->setBackgroundColor(2, Qt::white);
                    //clonedChild->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
                    lastParentItem->addChild(clonedChild);
                }
            }

        }
        ui->subsamplingMonitor->setCurrentRow(-1);
    //    qDebug() << "subsampledCounter "  << subsampledCounter << endl;
    }

    QString showingLabel;
    double showingPercentage = ((double)subsampledItems.size()/(double)imagesLength)*100;
	showingLabel.sprintf("Showing  %d  frames of  %d - %.1f%", subsampledItems.size(), imagesLength, showingPercentage);
    ui->showingFramesLabel->setEnabled(true);
    ui->showingFramesLabel->setText(showingLabel);	

	QString subsamplingLabel;    
	subsamplingLabel.sprintf("Subsampling Step: %d", subsamplingStep);
    ui->subsamplingStepLabel->setEnabled(true);
    ui->subsamplingStepLabel->setText(subsamplingLabel);		

	/*updateTreeWidget();
	updateRoiCopyOptions(data->currentSceneInfoIndex);*/
	updateImage(data->currentSceneInfoIndex);
}

void TaggingWidget::on_imageTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    int index = item->data(0, Qt::UserRole+2).toString().toInt();
    ui->fileListWidget->setCurrentRow(index);
    ui->subsamplingMonitor->setCurrentRow(index);
    updateImage(index);
}

void TaggingWidget::on_subsamplingSlider_sliderMoved(int position)
{
//    qDebug() << "slider moved to" << position << endl;
}

void TaggingWidget::on_subsamplingSlider_sliderReleased()
{
//    qDebug() << "slider moved to" << ui->subsamplingSlider->value() << endl;
    on_subsamplingUpdateButton_clicked();
}

void TaggingWidget::on_subsamplingMonitor_itemDoubleClicked(QListWidgetItem *item)
{
    int index = item->data(Qt::UserRole+2).toString().toInt();
    ui->fileListWidget->setCurrentRow(index);

    if(ui->imageTree->topLevelItem(index)->isHidden()) {
        int division = subsamplingStep==0?0:index/subsamplingStep;
//                qDebug() << "division: " << division << endl;

        int parentIndex = division*subsamplingStep;
//                qDebug() << "parentIndex: " << parentIndex << endl;

        int childIndex = index - parentIndex - 1;
//                qDebug() << "childIndex: " << childIndex << endl;

//                qDebug() << "subsamplingStep:" << subsamplingStep << endl;
//                qDebug() << "calculusIndex:" << calculusIndex << endl;
        //ui->imageTree->collapseAll();
        ui->imageTree->topLevelItem(parentIndex)->child(childIndex)->setExpanded(true);
        ui->imageTree->setCurrentItem(ui->imageTree->topLevelItem(parentIndex)->child(childIndex));
        ui->imageTree->scrollToItem(ui->imageTree->topLevelItem(parentIndex)->child(childIndex));
    } else {
//                qDebug() << "not hidden..." << endl;
        //ui->imageTree->collapseAll();
        ui->imageTree->setCurrentItem(ui->imageTree->topLevelItem(index));
        ui->imageTree->scrollToItem(ui->imageTree->topLevelItem(index));
    }
    updateImage(index);
}

void TaggingWidget::playPreview() {
	if(!stopPreview) {
		qDebug() << "playing preview at " << currentPreviewIndex << endl;
		QTreeWidgetItem *treeItem = ui->imageTree->topLevelItem(subsampledItems.at(currentPreviewIndex));
	//    qDebug() << "got treeitem at " << subsampledItems.at(currentPreviewIndex) << endl;
		//QPixmap image = qvariant_cast<QPixmap>(treeItem->data(0, Qt::UserRole));    
		QPixmap *image;
		QPixmap scaled;
		double scaledRatio = 1.0;

		previewScene->clear();

		if(ui->previewBGSCheck->isChecked()) {
			image = data->scenesInfos->at(subsampledItems.at(currentPreviewIndex))->bgsMask;		
		} else if(ui->previewFrameAndBGSCheck->isChecked()) {
			image = data->scenesInfos->at(subsampledItems.at(currentPreviewIndex))->imageAndBgsMask;	
		} else { // ui->previewFrameCheck->isChecked()
			image = data->scenesInfos->at(subsampledItems.at(currentPreviewIndex))->image;
		}		    

		//scaled = image->scaledToHeight(ui->previewWidget->height()*0.9);
		scaled = *image;
		qDebug() << "scaled w: " << scaled.width() << endl;;
		qDebug() << "scaled h: " << scaled.height() << endl;;

		qDebug() << "image w: " << image->width() << endl;;
		qDebug() << "image h: " << image->height() << endl;;

		scaledRatio = (double)scaled.height()/(double)image->height();

		QPainter painter(&scaled);
		painter.setPen(QPen(QBrush(QColor(255,69,0)), 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
		QFont tooltipFont = QFont("Newyork", 18);
		painter.setFont(tooltipFont);
		QString frameLabel;
		frameLabel.sprintf("Frame %03d", subsampledItems.at(currentPreviewIndex)+1);
		painter.drawText(QPoint(10,30), frameLabel);	

		if(ui->showROIsCheckbox->isChecked()) {
			//qDebug() << "data->currentSceneInfoIndex" << data->currentSceneInfoIndex << endl;
	//        qDebug() << "ui->showROIsCheckbox->isChecked()" << ui->showROIsCheckbox->isChecked() << endl;

			//DiagramSceneInfo currentSceneInfo = data->scenesInfos->at(subsampledItems.at(currentPreviewIndex));

			int previewRoiCount = data->scenesInfos->at(subsampledItems.at(currentPreviewIndex))->rois->size();

	//        qDebug() << "previewRoiCount" << previewRoiCount << endl;

			for(int i=0; i<previewRoiCount;i++) {
				DiagramROI * roi = data->scenesInfos->at(subsampledItems.at(currentPreviewIndex))->rois->at(i);

		//        qDebug() << "roi->getIndex() " << roi->getIndex() << endl;
		//        qDebug() << "roi->getLabel() " << roi->getLabel() << endl;
		//        qDebug() << "roi->getColor() " << roi->getColor().name() << endl;
		//        qDebug() << "roi->getWidth() " << roi->getWidth() << endl;
		//        qDebug() << "roi->getHeight() " << roi->getHeight() << endl;
		//        qDebug() << "roi->getTpx() " << roi->getTpx() << endl;
		//        qDebug() << "roi->getTpy() " << roi->getTpy() << endl;
		//        qDebug() << "roi->getBrx() " << roi->getBrx() << endl;
		//        qDebug() << "roi->getBry() " << roi->getBry() << endl;

				if(!roi->isRemoved()) {
					if(roi->isLabeled()) {
	//                    qDebug() << "roi->isLabeled()" << roi->isLabeled() << endl;
						painter.setPen(QPen(QBrush(roi->getColor()), 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
						painter.drawRect(roi->getTpx()*scaledRatio, roi->getTpy()*scaledRatio, roi->getWidth()*scaledRatio, roi->getHeight()*scaledRatio);
					} else {
	//                    qDebug() << "roi->isLabeled()" << roi->isLabeled() << endl;
						if(!ui->showOnlyLabeledROIsCheckbox->isChecked()) {
	//                        qDebug() << "ui->showOnlyLabeledROIsCheckbox->isChecked()" << ui->showOnlyLabeledROIsCheckbox->isChecked() << endl;
							painter.setPen(QPen(QBrush(Qt::white), 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
							painter.drawRect(roi->getTpx()*scaledRatio, roi->getTpy()*scaledRatio, roi->getWidth()*scaledRatio, roi->getHeight()*scaledRatio);
						}
					}
				}
			}
		}
    
		previewScene->addPixmap(scaled);
		previewScene->setSceneRect(QRectF(0, 0, scaled.width(), scaled.height()));
		previewView->updateZoom();
		currentPreviewIndex++;

		//qDebug() << "ui->imageTree->topLevelItemCount() " << ui->imageTree->topLevelItemCount() << endl;

		ui->playPreviewProgressBar->setValue(currentPreviewIndex);

		if(currentPreviewIndex >= currentTopLevelItems) {
	//        qDebug() << "before reseting..." << currentPreviewIndex << endl;
			currentPreviewIndex = 0;
	//        qDebug() << "reseting currentPreviewIndex ..." << currentPreviewIndex << endl;
		}
	}//  
}

void TaggingWidget::on_playPreviewButton_toggled(bool checked)
{
    
}


void TaggingWidget::on_showROIsCheckbox_toggled(bool checked)
{
    ui->showOnlyLabeledROIsLabel->setEnabled(checked);
    ui->showOnlyLabeledROIsCheckbox->setChecked(false);
    ui->showOnlyLabeledROIsCheckbox->setEnabled(checked);
}

void TaggingWidget::on_roisListWidget_pressed(const QModelIndex &index)
{
//    qDebug() << "pressed " << index.row() << endl;
//    qDebug() << "Qt::UserRole" << index.data(Qt::UserRole);
//    qDebug() << "Qt::UserRole+1" << index.data(Qt::UserRole+1);
//    qDebug() << "Qt::UserRole+2" << index.data(Qt::UserRole+2);
//    qDebug() << "Qt::UserRole+3" << index.data(Qt::UserRole+3);
//    qDebug() << "Qt::UserRole+4" << index.data(Qt::UserRole+4);

    int tpx = index.data(Qt::UserRole+1).toInt();
    int tpy = index.data(Qt::UserRole+2).toInt();
    int w = index.data(Qt::UserRole+3).toInt();
    int y = index.data(Qt::UserRole+4).toInt();

    DiagramItem * item = qgraphicsitem_cast<DiagramItem *>(scene->itemAt(tpx+w/2, tpy+y/2));

    if(item != NULL) {
        scene->clearSelection();
        item->setSelected(true);
    }
}

void TaggingWidget::on_labelsListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    
}

void TaggingWidget::updateTreeWidget() {
	for(int i=0; i<treeItems.size(); i++) {
		QTreeWidgetItem *treeItem = ui->imageTree->topLevelItem(i);
		if(treeItem->isHidden()) {
            int division = subsamplingStep==0?0:i/subsamplingStep;
//                qDebug() << "division: " << division << endl;

            int parentIndex = division*subsamplingStep;
//                qDebug() << "parentIndex: " << parentIndex << endl;

            int childIndex = i - parentIndex - 1;
//                qDebug() << "childIndex: " << childIndex << endl;

//                qDebug() << "subsamplingStep:" << subsamplingStep << endl;
//                qDebug() << "calculusIndex:" << calculusIndex << endl;            
			treeItem = ui->imageTree->topLevelItem(parentIndex)->child(childIndex);
        }

		GTTreeItem * gtTreeItem = treeItems.at(i);
        
        //QString treeLabel;
		//treeLabel.sprintf("%03d", i+1);

        //treeItem->setText(0, treeLabel);
		//treeItem->setText(1, gtTreeItem->getFrameFilename());
        //treeItem->setText(2, "");
		
		QColor parentColor;
		QColor labelStausColor;

		switch(getRoiLabelsStatus(i)) {
		case MANUAL_UNLABELED_ROIS:
			labelStausColor = data->manuallyRoisUnlabeledColor;
			break;
		case MANUAL_LABELED_ROIS:
			labelStausColor = data->manuallyRoisLabeledColor;
			break;
		case AUTOMATIC_UNLABELED_ROIS:
			labelStausColor = data->automaticRoisUnlabeledColor;
			break;
		case AUTOMATIC_LABELED_ROIS:
			labelStausColor = data->automaticRoisLabeledColor;
			break;
		case REVIEW_FRAME_ROIS:
			labelStausColor = data->reviewFrameLabelsColor;
			break;
		default:
			labelStausColor = data->noRoisColor;
			break;
		}

		gtTreeItem->setRoiLabelsStatusColor(labelStausColor);		
		
		parentColor = gtTreeItem->isParent()?Qt::white:Qt::blue;
		//qDebug() << i << " --b parent color to " << parentColor.name() << endl;

		if(gtTreeItem->isParent()) {
			parentColor = data->parentTreeColor;
			//treeItem->setTextColor(0, data->parentTreeTextColor);
			//qDebug() << i << " updating parent color to " << parentColor.name() << endl;
			//qDebug() << i << " updating parent color to " << labelStausColor.name() << endl;
		} else {			
			parentColor = data->childTreeColor;
			//qDebug() << i << " updating child color to " << parentColor.name() << endl;
			//qDebug() << i << " updating child color to " << labelStausColor.name() << endl;
		}

		//qDebug() << i << " --a parent color to " << parentColor.name() << endl;

		treeItem->setBackground(0, parentColor);
		treeItem->setBackground(2, labelStausColor);

        //treeItem->setTextAlignment(0, Qt::AlignCenter);
        //treeItem->setTextAlignment(1, Qt::AlignCenter);
        //treeItem->setTextAlignment(2, Qt::AlignCenter);

        //treeItem->setData(0, Qt::UserRole, QVariant(fileImage));
        //treeItem->setData(0, Qt::UserRole+2, i);
        //treeItem->setData(1, Qt::UserRole+2, i);
        //treeItem->setData(2, Qt::UserRole+2, i);
        //treeItem->setIcon(1, fileIcon);
		//gtTreeItem->setFrameImage(fileImage);
        //treeItem->setForeground(1, QBrush(fileImage));
	}
}

RoiLabelsStatus TaggingWidget::getRoiLabelsStatus(int frameId) {
	QList<DiagramROI*> *rois = data->scenesInfos->at(frameId)->rois;
	int roisSize = rois->size();

	if(roisSize == 0)
		return NO_ROIS;
		
	int removedRoisCounter = 0;
	int manuallyRoisUnlabeledCounter = 0;
	int manuallyRoisLabeledCounter = 0;
	int automaticRoisUnlabeledCounter = 0;
	int automaticRoisLabeledCounter = 0;
	
	for(int i=0; i<rois->size();i++) {
		DiagramROI *roi = rois->at(i);
		
		if(roi->isRemoved()) {
			removedRoisCounter++;
			continue;
		}

		if(roi->isLabeled()) {
			if(roi->isAutomatic()) {
				automaticRoisLabeledCounter++;
			} else {
				manuallyRoisLabeledCounter++;
			}
		} else {
			if(roi->isAutomatic()) {
				automaticRoisUnlabeledCounter++;
			} else {
				manuallyRoisUnlabeledCounter++;
			}
		}
	}

	if(removedRoisCounter == roisSize)
		return NO_ROIS;

	if(automaticRoisLabeledCounter == roisSize)
		return AUTOMATIC_LABELED_ROIS;

	if(manuallyRoisLabeledCounter == roisSize)
		return MANUAL_LABELED_ROIS;

	if(automaticRoisUnlabeledCounter == roisSize)
		return AUTOMATIC_UNLABELED_ROIS;

	if(manuallyRoisUnlabeledCounter == roisSize)
		return MANUAL_UNLABELED_ROIS;

	return REVIEW_FRAME_ROIS;
}

void TaggingWidget::updateRoiCopyOptions(int index) {
	ui->copyComboBox->clear();
	
	QList<RoiCopyOption> keys;
	QList<QString> values;

	GTTreeItem * gtTreeItem = treeItems.at(index);

	if(ui->subsamplingCheck->isChecked()) {
		if(gtTreeItem->isParent()) {
			keys = data->subsampledParentFrameCopyOptions.keys();
			values = data->subsampledParentFrameCopyOptions.values();
		} else {
			keys = data->subsampledChildFrameCopyOptions.keys();
			values = data->subsampledChildFrameCopyOptions.values();
		}
	} else {
		keys = data->frameCopyOptions.keys();
		values = data->frameCopyOptions.values();
	}		

	ui->copyComboBox->clear();
	for(int i=0; i< keys.size(); i++) {
		RoiCopyOption key = keys.at(i);
		ui->copyComboBox->addItem(values.at(i), QVariant(key));
	}
}

void TaggingWidget::generateIndexesList(int start, int size, QList<int> * indexList) {
	indexList->clear();	
	for(int i=0; i<size; i++) {
		indexList->append(start+i);
	}
}

void TaggingWidget::generateParentIndexesList(int start, QList<int> * indexList) {
	for(int i=start; i<treeItems.size(); i++) {
		QTreeWidgetItem *treeItem = ui->imageTree->topLevelItem(i);
		if(!treeItem->isHidden()) {
			indexList->append(i);
		}
	}
}

void TaggingWidget::generateChildIndexesList(int start, QList<int> * indexList) {
	for(int i=start; i<treeItems.size(); i++) {
		QTreeWidgetItem *treeItem = ui->imageTree->topLevelItem(i);
		if(treeItem->isHidden()) {
			indexList->append(i);
		} else {
			return;
		}		
	}
}

void TaggingWidget::on_copyROIsButton_clicked()
{
	int currentIndex = ui->copyComboBox->currentIndex();
	qDebug() << "currentIndex " << currentIndex << endl;

	RoiCopyOption selectedCopyOption = static_cast<RoiCopyOption>(ui->copyComboBox->itemData(currentIndex).toInt());

	qDebug() << "copy invoked! " << selectedCopyOption << endl;
	
	QList<int> targetIndexes = QList<int>();
	QList<int> nextParentFrame = QList<int>();

	int sourceIndex = data->currentSceneInfoIndex;
	int targetCount = 0;
	
	progressDialog->setCancelButtonText(tr("&Cancel"));
	progressDialog->setWindowTitle(tr("Copying ROIs ..."));			

	switch(selectedCopyOption) {
		case COPY_TO_PARENT_FRAMES:			
			generateParentIndexesList(sourceIndex+1, &targetIndexes);
			progressDialog->setRange(0, targetIndexes.size());
			progressDialog->show();
			copyRois(sourceIndex, targetIndexes);
			progressDialog->setValue(targetIndexes.size());
			progressDialog->setLabelText(tr("ROIs Copied..."));
			progressDialog->hide();
			break;
		case COPY_TO_SUMSAMPLED_FRAMES:
			generateChildIndexesList(sourceIndex+1, &targetIndexes);
			progressDialog->setRange(0, targetIndexes.size());
			progressDialog->show();
			copyRois(sourceIndex, targetIndexes);
			progressDialog->setValue(targetIndexes.size());
			progressDialog->setLabelText(tr("ROIs Copied..."));
			progressDialog->hide();
			break;
		case COPY_UNTIL_LAST_FRAME:
			targetCount = data->scenesInfos->size() - data->currentSceneInfoIndex - 1;
			generateIndexesList(sourceIndex+1, targetCount, &targetIndexes);
			progressDialog->setRange(0, targetCount);
			progressDialog->show();
			copyRois(sourceIndex, targetIndexes);
			progressDialog->setValue(targetCount);
			progressDialog->setLabelText(tr("ROIs Copied..."));
			progressDialog->hide();
			break;
		case COPY_TO_NEXT_PARENT_FRAME:					
			generateParentIndexesList(sourceIndex+1, &targetIndexes);			
			progressDialog->setRange(0, targetIndexes.size());
			progressDialog->show();			
			if(targetIndexes.size() > 0 ) {
				nextParentFrame.clear();
				nextParentFrame.append(targetIndexes.at(0));
				copyRois(sourceIndex,  nextParentFrame);
				progressDialog->setValue(targetIndexes.size());
			}
			progressDialog->setLabelText(tr("ROIs Copied..."));
			progressDialog->hide();
			break;
		case COPY_TO_NEXT_FRAME:			
			targetIndexes.append(sourceIndex+2);
			generateIndexesList(sourceIndex+1, 1, &targetIndexes);
			progressDialog->setRange(0, 1);
			progressDialog->show();
			copyRois(sourceIndex, targetIndexes);
			progressDialog->setValue(1);
			progressDialog->setLabelText(tr("ROIs Copied..."));
			progressDialog->hide();
			break;
		default:
			qDebug() << "Not copying..." << endl;
			break;
	}

	updateTreeWidget();
}

void TaggingWidget::copyRois(int sourceIndex, QList<int> targetIndexes) {
	int sourcesRoisCount = data->scenesInfos->at(sourceIndex)->rois->size();
	QList<DiagramROI *> * sourceRois = data->scenesInfos->at(sourceIndex)->rois;

	for(int i=0; i<targetIndexes.size(); i++) {
		QList<DiagramROI *> * targetRois = data->scenesInfos->at(targetIndexes.at(i))->rois;
		targetRois->clear();

		for(int j=0; j<sourcesRoisCount; j++) {
			DiagramROI * sourceRoi = sourceRois->at(j);
		
			DiagramROI *targetRoi = new DiagramROI();			
			targetRoi->setIndex(sourceRoi->getIndex());
			targetRoi->setLabel(sourceRoi->getLabel());
			targetRoi->setLabelId(sourceRoi->getLabelId());
			targetRoi->setWidth(sourceRoi->getWidth());
			targetRoi->setHeight(sourceRoi->getHeight());
			targetRoi->setTpx(sourceRoi->getTpx());
			targetRoi->setTpy(sourceRoi->getTpy());
			targetRoi->setBrx(sourceRoi->getBrx());
			targetRoi->setBry(sourceRoi->getBry());
			targetRoi->setColor(sourceRoi->getColor());
			targetRoi->setLabeled(sourceRoi->isLabeled());
			targetRoi->setRemoved(sourceRoi->isRemoved());
			targetRoi->setAutomatic(true);
			targetRoi->setFrameId(targetIndexes.at(i));

			targetRois->append(targetRoi);
		}
	}
}

void TaggingWidget::on_showFirstFrameButton_clicked() {
	updateImage(0);
}

void TaggingWidget::on_showPreviousFrameButton_clicked() {
	if((data->currentSceneInfoIndex-1) >= 0) {
		updateImage(data->currentSceneInfoIndex-1);
	}
}

void TaggingWidget::on_showPreviousParentFrameButton_clicked() {
	if((data->currentSceneInfoIndex-1) >= 0) {
		int division = subsamplingStep==0?0:data->currentSceneInfoIndex/subsamplingStep;
        int parentIndex = division*subsamplingStep;
        int childIndex = data->currentSceneInfoIndex - parentIndex - 1;
		
		QTreeWidgetItem *treeItem = ui->imageTree->topLevelItem(data->currentSceneInfoIndex);
		if(treeItem->isHidden()) {
			updateImage(parentIndex);
		} else {
			if((parentIndex - subsamplingStep) >= 0) {
				updateImage(parentIndex - subsamplingStep);
			} else {
				updateImage(0);
			}
		}		
	}
}

void TaggingWidget::on_showNextParentFrameButton_clicked() {
	if((data->currentSceneInfoIndex+1 + subsamplingStep) <= (data->scenesInfos->size()-1)) {
		int division = subsamplingStep==0?0:data->currentSceneInfoIndex/subsamplingStep;
        int parentIndex = division*subsamplingStep;
        int childIndex = data->currentSceneInfoIndex - parentIndex - 1;
		
		QTreeWidgetItem *treeItem = ui->imageTree->topLevelItem(data->currentSceneInfoIndex);
		if(treeItem->isHidden()) {
			if((parentIndex + subsamplingStep) <= (data->scenesInfos->size()-1)) {
				updateImage(parentIndex + subsamplingStep);
			} else {
				updateImage(data->scenesInfos->size()-1);
			}
		} else {
			if((data->currentSceneInfoIndex + subsamplingStep) <= data->scenesInfos->size()-1) {
				updateImage(data->currentSceneInfoIndex + subsamplingStep);
			} else {
				updateImage(data->scenesInfos->size()-1);
			}
		}		
	}
}

void TaggingWidget::on_showNextFrameButton_clicked() {
	if((data->currentSceneInfoIndex+1) <= (data->scenesInfos->size()-1)) {

		if(ui->copyOnNextCheck->isChecked()) {	
			QList<int> targetIndexes = QList<int>();
			targetIndexes.append(data->currentSceneInfoIndex+1);
			copyRois(data->currentSceneInfoIndex, targetIndexes);
		}

		updateImage(data->currentSceneInfoIndex+1);
	}
}

void TaggingWidget::on_showLastFrameButton_clicked() {
	updateImage(data->scenesInfos->size()-1);
}

void TaggingWidget::on_computeRoiSummary_clicked() {
	int totalSize = data->scenesInfos->size();
	
	progressDialog->show();
	progressDialog->setCancelButtonText(tr("&Cancel"));
	progressDialog->setRange(0, totalSize);
	progressDialog->setWindowTitle(tr("Computing ROIs Summary..."));

	data->labelsSummary.clear();

	for(int i=0; i<totalSize; i++) {
		progressDialog->setValue(i+1);
		progressDialog->setLabelText(tr("Computing ROIs Summary for frame %1 of %2...").arg(i+1).arg(totalSize));

		if (progressDialog->wasCanceled()) {
			break;
		}
		
		for(int j=0; j<data->scenesInfos->at(i)->rois->size(); j++) {
			DiagramROI *roi = data->scenesInfos->at(i)->rois->at(j);

			if(!roi->isRemoved() && roi->getWidth() > data->minRoiWidth && roi->getHeight() > data->minRoiHeight) {
				QList<DiagramROI*> labelList;

				if(data->labelsSummary.contains(roi->getLabel())) {
					labelList = data->labelsSummary.value(roi->getLabel());				
				} else {
					labelList = QList<DiagramROI*>();
				}

				labelList.append(roi);
				data->labelsSummary.insert(roi->getLabel(), labelList);		
			}				
		}

		qApp->processEvents();
	}
	
	ui->summaryTabWidget->clear();

	QList<QString> labels = data->labelsSummary.keys();
	QPixmap tabIconColor(15,15);
    QPainter tabIconPainter(&tabIconColor);

	progressDialog->setRange(0, labels.size());
	progressDialog->show();
	progressDialog->setWindowTitle(tr("Displaying ROIs Summary..."));

	for(int i=0; i<labels.size(); i++) {				
		progressDialog->setValue(i+1);
		progressDialog->setLabelText(tr("Displaying ROIs Summary for label %1 of %2...").arg(i+1).arg(labels.size()));

		QList<DiagramROI*> rois = data->labelsSummary.value(labels.at(i));
		QListWidget * labelList = new QListWidget();
		labelList->setViewMode(QListWidget::IconMode);
		labelList->setIconSize(QSize(100,100));

		for(int j=0; j<rois.size(); j++) {
			DiagramROI * roi = rois.at(j);

			if(!roi->isRemoved() && roi->getWidth() > data->minRoiWidth && roi->getHeight() > data->minRoiHeight) {
				QListWidgetItem *roiItem = new QListWidgetItem(labelList);
				QString frameLabel;
				frameLabel.sprintf("Frame %03d", roi->getFrameId()+1);
				roiItem->setText(frameLabel);
				roiItem->setFont(QFont("Newyork", 14));
				QPixmap roiImage = data->scenesInfos->at(roi->getFrameId())->image->copy(roi->getTpx(), roi->getTpy(), roi->getWidth(), roi->getHeight()).scaledToHeight(roi->getHeight()*2);
				QIcon roiIcon(roiImage);
				roiItem->setIcon(roiIcon);
				roiItem->setTextAlignment(Qt::AlignBottom | Qt::AlignHCenter);
				roiItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
			}			
		}
		
		tabIconPainter.setBrush(rois.at(0)->getColor());
        tabIconPainter.drawRect(QRect(QPoint(0,0), QPoint(15,15) - QPoint(2,2)));
		ui->summaryTabWidget->addTab(labelList, QIcon(tabIconColor), labels.at(i));		

		if (progressDialog->wasCanceled()) {
			break;
		}

		qApp->processEvents();
	}			

	ui->summaryTabWidget->setEnabled(true);
	ui->saveRoisToDiskButton->setEnabled(true);
	ui->saveBGSFrameCheckbox->setEnabled(true);
	ui->saveBGSMaskCheckbox->setEnabled(true);

	progressDialog->hide();
}

void TaggingWidget::on_saveRoisToDiskButton_clicked() {
	int totalSize = data->scenesInfos->size();
	QString basePath = currentDir.path()+ "\\rois\\";
	FileProcessor fileProcessor = FileProcessor();
	
	QList<QString> labels = data->labelsSummary.keys();

	progressDialog->setCancelButtonText(tr("&Cancel"));	
	progressDialog->setRange(0, labels.size());
	progressDialog->setValue(0);
	progressDialog->setWindowTitle(tr("Saving ROI to disk..."));
	progressDialog->setLabelText(tr("Saving ROIs to disk..."));
	progressDialog->show();	
	qApp->processEvents();

	for(int i=0; i<labels.size(); i++) {		
		QList<DiagramROI*> rois = data->labelsSummary.value(labels.at(i));
		
		QString labelName = fileProcessor.removeForbiddenChars(labels.at(i));
		qDebug() << "to create dir: " << labelName << endl;
		
		QString dirName = basePath + labelName;		
		qDebug() << "to create dir: " << dirName << endl;

		progressDialog->setRange(0, rois.size());
		progressDialog->setValue(0);

		if(fileProcessor.createDir(dirName)) {
			for(int j=0; j<rois.size(); j++) {
				DiagramROI * roi = rois.at(j);
			
				if(!roi->isRemoved() && roi->getWidth() > data->minRoiWidth && roi->getHeight() > data->minRoiHeight) {
					QString roiFileName;
					roiFileName.sprintf("frame%03d_roi%02d.png", roi->getFrameId()+1, roi->getIndex());

					QPixmap roiImage = data->scenesInfos->at(roi->getFrameId())->image->copy(roi->getTpx(), roi->getTpy(), roi->getWidth(), roi->getHeight());
					QFile roiFile(dirName + "\\" +roiFileName);
					roiFile.open(QIODevice::WriteOnly);
					roiImage.save(&roiFile, "PNG");

					if(bgsLoaded) {
						if(ui->saveBGSMaskCheckbox->isChecked()) {
							QString bgsRoiFileName;
							bgsRoiFileName.sprintf("frame%03d_roi%02d_bgs.png", roi->getFrameId()+1, roi->getIndex());

							QPixmap bgsRoiImage = data->scenesInfos->at(roi->getFrameId())->bgsMask->copy(roi->getTpx(), roi->getTpy(), roi->getWidth(), roi->getHeight());
							QFile bgsRoiFile(dirName + "\\" +bgsRoiFileName);
							bgsRoiFile.open(QIODevice::WriteOnly);
							bgsRoiImage.save(&bgsRoiFile, "PNG");
						}

						if(ui->saveBGSFrameCheckbox->isChecked()) {
							QString bgsAndImageRoiFileName;
							bgsAndImageRoiFileName.sprintf("frame%03d_roi%02d_bgsAndImage.png", roi->getFrameId()+1, roi->getIndex());

							QPixmap bgsAndImageRoiImage = data->scenesInfos->at(roi->getFrameId())->imageAndBgsMask->copy(roi->getTpx(), roi->getTpy(), roi->getWidth(), roi->getHeight());
							QFile bgsAndImageRoiFile(dirName + "\\" +bgsAndImageRoiFileName);
							bgsAndImageRoiFile.open(QIODevice::WriteOnly);
							bgsAndImageRoiImage.save(&bgsAndImageRoiFile, "PNG");
						}						
					}
				}	

				progressDialog->setValue(j+1);
				progressDialog->setLabelText(tr("Saving ROI %1 of %2 for label %3").arg(j+1).arg(rois.size()).arg(i+1));
			}
		}				

		if (progressDialog->wasCanceled()) {
			break;
		}

		/*progressDialog->setValue(i+1);
		progressDialog->setLabelText(tr("Saving ROIs to disk for label %1 of %2...").arg(i+1).arg(labels.size()));*/
		qApp->processEvents();
	}

	XMLProcessor xmlProcessor = XMLProcessor(); 

	if(!QDir(basePath).exists()) {
		QDir().mkpath(basePath);
	}

	progressDialog->setWindowTitle(tr("Saving ROIs as XML..."));
	xmlProcessor.saveRoisToXML(data->scenesInfos, basePath + "rois.xml", ui->pixelPadding->value(), currentDir.dirName());
	progressDialog->setLabelText(tr("Saved ROIs as XML!"));
	progressDialog->hide();
}

void TaggingWidget::on_computeBGS_clicked() {	
	OpenCVProcessor openCVProcessor = OpenCVProcessor();
	openCVProcessor.setProgressDialog(progressDialog);

	int bgsIterations = ui->bgsIterations->text().toInt();
	
	progressDialog->setCancelButtonText(tr("&Cancel"));	
	//progressDialog->setWindowTitle(tr("Iteration 1 for BGS Model..."));
	//progressDialog->setValue(0);
	progressDialog->setWindowTitle(tr("BGS iteration %1 of %2").arg(1).arg(bgsIterations));
	progressDialog->show();	

	QString iterationPath =  currentDir.absolutePath() + "\\bgs\\1\\";

	QDir().mkpath(iterationPath);

	if(QDir().mkpath(iterationPath)) {
		QStringList framesFileNames;

		QStringList filters;
		filters << "*.png" << "*.jpg" << "*.jpeg";

		framesFileNames = currentDir.entryList(filters, QDir::Files | QDir::NoSymLinks);   
		progressDialog->setRange(0, framesFileNames.size()*bgsIterations);

		openCVProcessor.computeBGSModel(currentDir.absolutePath(), false, 1);
		qApp->processEvents();

		for(int i=2; i<=bgsIterations; i++) {			
			//progressDialog->setWindowTitle("Iteration "+ QString::number(i) + " for BGS Model...");
			//progressDialog->setValue(1);

			if (progressDialog->wasCanceled()) {
				progressDialog->hide();
				return;
			}

			progressDialog->setWindowTitle(tr("BGS iteration %1 of %2").arg(i).arg(bgsIterations));
			progressDialog->show();

			iterationPath =  currentDir.absolutePath() + "\\bgs\\" + QString::number(i) + "\\";
			if(QDir().mkpath(iterationPath)) {
				openCVProcessor.computeBGSModel(currentDir.absolutePath(), true, i);
				qApp->processEvents();
			} else {
				qDebug() << "Cannot create path for iteration " << i << endl;
			}									
		}
	} else {
		qDebug() << "Cannot create path for iteration " << 1 << endl;
	}	
	bgsLoaded = true;
	bgsMaxIterations = bgsIterations;
	//ui->saveBGSData->setEnabled(true);
	ui->loadBGSData->setEnabled(true);		
	on_saveBGSData_clicked();
	on_loadBGSData_clicked();
	progressDialog->hide();
}

void TaggingWidget::on_computeDescriptors_clicked() {
	QList<QString> labels = data->labelsSummary.keys();
	int labelsSize = labels.size();	

	QString basePath = currentDir.path()+ "\\";
	FileProcessor fileProcessor = FileProcessor();
	OpenCVProcessor openCVProcessor = OpenCVProcessor();
	
	progressDialog->setCancelButtonText(tr("&Cancel"));	
	progressDialog->setWindowTitle(tr("Computing Descriptors.."));	
	progressDialog->setRange(0, labelsSize);
	progressDialog->setValue(0);
	progressDialog->show();	

	for(int i=0; i<labelsSize; i++) {
		qDebug() << "-- i " << i << endl;

		progressDialog->setWindowTitle(tr("Label %1 of %2, computing descriptors...").arg(i+1).arg(labelsSize));

		QList<DiagramROI*> rois = data->labelsSummary.value(labels.at(i));
		
		QString labelName = fileProcessor.removeForbiddenChars(labels.at(i));
		QString dirName = basePath + "rois\\"+ labelName;
		QString descriptorsSURFDirName = basePath + "descriptors\\SURF\\";
		QString descriptorsShapeAndColorDirName = basePath + "descriptors\\ShapeAndColor\\";		

		if(fileProcessor.createDir(descriptorsSURFDirName) && fileProcessor.createDir(descriptorsShapeAndColorDirName)) {
			QDir roisDir = QDir(dirName);
			QString labelFilenameSURF;
			QString labelFilenameShapeAndColor;

			if(ui->useBGSCheck->isChecked() && bgsLoaded) {
				labelFilenameSURF = descriptorsSURFDirName + "\\bgs_" + labelName + ".txt";
				labelFilenameShapeAndColor = descriptorsShapeAndColorDirName + "\\bgs_" + labelName + ".txt";				
			} else {
				labelFilenameSURF = descriptorsSURFDirName + "\\" + labelName + ".txt";
				labelFilenameShapeAndColor = descriptorsShapeAndColorDirName + "\\" + labelName + ".txt";
			}

			for(int j=0; j<rois.size(); j++) {
				qDebug() << "-- j " << j << endl;

				DiagramROI * roi = rois.at(j);
			
				progressDialog->setRange(0, rois.size());
				progressDialog->setValue(j+1);
				progressDialog->setLabelText(tr("Computing descriptor for roi %1 of %2").arg(j+1).arg(rois.size()));

				int tpxWithPadding = roi->getTpx() - ui->pixelPadding->value();								
				int tpyWithPadding = roi->getTpy() - ui->pixelPadding->value();
				int brxWithPadding = roi->getBrx() + ui->pixelPadding->value();
				int bryWithPadding = roi->getBry() + ui->pixelPadding->value();

				if(tpxWithPadding < 0) {
					tpxWithPadding = 0;
				}

				if(tpyWithPadding < 0) {
					tpyWithPadding = 0;
				}

				if(brxWithPadding > data->scenesInfos->at(0)->image->width()) {
					brxWithPadding = data->scenesInfos->at(0)->image->width();
				}

				if(bryWithPadding > data->scenesInfos->at(0)->image->height()) {
					bryWithPadding = data->scenesInfos->at(0)->image->height();
				}
								
				QPixmap roiImage;
				QString roiFileName;

				if(ui->useBGSCheck->isChecked() && bgsLoaded) {
					qDebug() << "-- before roi->getFrameId() " << roi->getFrameId() << endl;
					qDebug() << data->scenesInfos->at(roi->getFrameId())->imageAndBgsMask->width() << endl;
					roiImage = data->scenesInfos->at(roi->getFrameId())->imageAndBgsMask->copy(tpxWithPadding, tpyWithPadding, brxWithPadding-tpxWithPadding, bryWithPadding-tpyWithPadding);
					qDebug() << "-- after roi->getFrameId() " << roi->getFrameId() << endl;
					roiFileName.sprintf("frame%03d_roi%02d_%02d_px_padded_bgs.png", roi->getFrameId()+1, roi->getIndex(), ui->pixelPadding->value());
				} else {
					roiImage = data->scenesInfos->at(roi->getFrameId())->image->copy(tpxWithPadding, tpyWithPadding, brxWithPadding-tpxWithPadding, bryWithPadding-tpyWithPadding);
					roiFileName.sprintf("frame%03d_roi%02d_%02d_px_padded.png", roi->getFrameId()+1, roi->getIndex(), ui->pixelPadding->value());
				}
								
				QFile roiFile(dirName + "\\" +roiFileName);
				roiFile.open(QIODevice::WriteOnly);
				roiImage.save(&roiFile, "PNG");

				qDebug() << "-- after roiImage.save" << endl;

				cv::Mat cvRoiImage = imread(roiFile.fileName().toStdString());
				qDebug() << "-- after imread" << endl;

				openCVProcessor.computeSURFDescriptors(cvRoiImage, roi->getFrameId()+1, roi->getIndex(), labelFilenameSURF);
				qDebug() << "-- after computeSURFDescriptors" << endl;

				if(j==110) {
					qDebug() << "on 110!" << endl;
				}

				openCVProcessor.computeShapeAndColorDescriptors(cvRoiImage, roi->getFrameId()+1, roi->getIndex(), labelFilenameShapeAndColor, ui->useBGSCheck->isChecked() && bgsLoaded?1:0);
				qDebug() << "-- after computeShapeAndColorDescriptors" << endl;

				if (progressDialog->wasCanceled()) {
					progressDialog->hide();
					return;
				}

				qApp->processEvents();
			}

			/*QStringList roisFileNames;

			QStringList filters;
			filters << "*.png" << "*.jpg" << "*.jpeg";

			roisFileNames = roisDir.entryList(filters, QDir::Files | QDir::NoSymLinks);   
			QString labelFilenameSURF = descriptorsSURFDirName + "\\" + labelName + ".txt";
			QString labelFilenameShapeAndColor = descriptorsShapeAndColorDirName + "\\" + labelName + ".txt";

			for(int j=0; j<roisFileNames.size(); j++) {
				progressDialog->setRange(0, roisFileNames.size());
				progressDialog->setValue(j);
				progressDialog->setLabelText(tr("Computing descriptor for roi %1 on frame %2 of %3").arg(roisFileNames[j].mid(12, 2).toInt()).arg(roisFileNames[j].mid(5, 3).toInt()).arg(roisFileNames.size()));

				cv::Mat roiImage = imread(roisDir.absoluteFilePath(roisFileNames[j]).toStdString());
				openCVProcessor.computeSURFDescriptors(roiImage, roisFileNames[j].mid(5, 3).toInt(), roisFileNames[j].mid(12, 2).toInt(), labelFilenameSURF);
				openCVProcessor.computeShapeAndColorDescriptors(roiImage, roisFileNames[j].mid(5, 3).toInt(), roisFileNames[j].mid(12, 2).toInt(), labelFilenameShapeAndColor);
				qApp->processEvents();
			}*/			
		}

		if (progressDialog->wasCanceled()) {
			progressDialog->hide();
			return;
		}
	}	
	progressDialog->hide();
	qApp->processEvents();
}

void TaggingWidget::on_saveBGSData_clicked()
{
	bgsLoaded = true;

	OpenCVProcessor openCVProcessor = OpenCVProcessor();

	QDir saveDir = QDir(currentDir.absolutePath() + "\\bgs\\0\\");
	QDir maskDir = QDir(currentDir.absolutePath() + "\\bgs\\" + QString::number(bgsMaxIterations) + "\\");

	QDir().mkpath(saveDir.path());

    QStringList maskFileNames;

    QStringList filters;
    filters << "mask*.png";

    maskFileNames = maskDir.entryList(filters, QDir::Files | QDir::NoSymLinks);

	progressDialog->setCancelButtonText(tr("&Cancel"));
	progressDialog->setWindowTitle(tr("Saving BGS data"));
	progressDialog->setRange(0, maskFileNames.size());
	progressDialog->setValue(0);
	progressDialog->setLabelText(tr("Saving BGS data for frame %1 of %2").arg(0).arg(maskFileNames.size()));
	progressDialog->show();			
	qApp->processEvents();

	for (int i=0; i<maskFileNames.size(); i++) {
		cv::Mat image = openCVProcessor.QPixmapToCvMat(*data->scenesInfos->at(i)->image);		
		/*imshow(QString::number(i+1).toStdString() + " " + maskFileNames[i].toStdString(), image);		
		cv::waitKey();*/

		Mat mask = imread(maskDir.absoluteFilePath(maskFileNames[i]).toStdString(), CV_LOAD_IMAGE_GRAYSCALE);
		imwrite(saveDir.path().toStdString() + "\\bw_" + maskFileNames[i].toStdString(), mask);
		/*imshow(QString::number(i+1).toStdString() + " " + maskFileNames[i].toStdString(), mask);
		cv::waitKey();*/

		Mat img_bw;		
		threshold(mask, img_bw, 254, 1.00, THRESH_BINARY);
		//imwrite(saveDir.path().toStdString() + "\\bw_" + maskFileNames[i].toStdString(), img_bw);
		/*imshow(QString::number(i+1).toStdString() + " " + maskFileNames[i].toStdString(), img_bw);
		cv::waitKey();*/

		cv::Mat imageAndMask;
		image.copyTo(imageAndMask, img_bw);
		imwrite(saveDir.path().toStdString() + "\\iAm_" + maskFileNames[i].toStdString(), imageAndMask);
		/*imshow(QString::number(i+1).toStdString() + " " + maskFileNames[i].toStdString(), imageAndMask);
		cv::waitKey();*/

		//data->scenesInfos->at(i)->bgsMask = new QPixmap();
		//data->scenesInfos->at(i)->bgsMask->load(QString::fromStdString(saveDir.path().toStdString() + "\\bw_" + maskFileNames[i].toStdString()));
		///*qDebug() << "loading from " << QString::fromStdString(saveDir.path().toStdString() + "\\bw_" + maskFileNames[i].toStdString()) << endl;
		//QFile test_bgsMaskFile(QString::fromStdString(saveDir.path().toStdString() + "\\test_bw_" + maskFileNames[i].toStdString()));
		//test_bgsMaskFile.open(QIODevice::WriteOnly);
		//data->scenesInfos->at(i)->bgsMask->save(&test_bgsMaskFile, "PNG");
		//qDebug() << "saving to " << QString::fromStdString(saveDir.path().toStdString() + "\\test_bw_" + maskFileNames[i].toStdString()) << endl;*/

		//data->scenesInfos->at(i)->imageAndBgsMask = new QPixmap();
		//data->scenesInfos->at(i)->imageAndBgsMask->load(QString::fromStdString(saveDir.path().toStdString() + "\\iAm_" + maskFileNames[i].toStdString()));
		///*QFile test_imageAndBgsMaskFile(QString::fromStdString(saveDir.path().toStdString() + "\\test_iAm_" + maskFileNames[i].toStdString()));
		//test_imageAndBgsMaskFile.open(QIODevice::WriteOnly);
		//data->scenesInfos->at(i)->imageAndBgsMask->save(&test_imageAndBgsMaskFile, "PNG");*/

		progressDialog->setValue(i+1);
		progressDialog->setLabelText(tr("Saving BGS data for frame %1 of %2").arg(i+1).arg(maskFileNames.size()));
		qApp->processEvents();
	}
	progressDialog->hide();
	qApp->processEvents();
}

void TaggingWidget::on_eraseAllRois_clicked() {
	for(int i=0; i<data->scenesInfos->size(); i++) {
		data->scenesInfos->at(i)->rois->clear();
	}

	ui->roisListWidget->clear();
	ui->roiTable->setRowCount(0);
	scene->clear();
	updateTreeWidget();
	updateImage(data->currentSceneInfoIndex);
}

void TaggingWidget::on_labelsListWidgetTagging_itemPressed(QListWidgetItem *item)
{
	on_labelsListWidget_itemPressed(item);
}

void TaggingWidget::on_loadBGSData_clicked()
{
	OpenCVProcessor openCVProcessor = OpenCVProcessor();
	
	QDir maskDir = QDir(currentDir.absolutePath() + "\\bgs\\0\\");

    QStringList maskFileNames;

    QStringList filters;
    filters << "bw_*.png";

    maskFileNames = maskDir.entryList(filters, QDir::Files | QDir::NoSymLinks);

	progressDialog->setCancelButtonText(tr("&Cancel"));
	progressDialog->setWindowTitle(tr("Saving BGS data"));
	progressDialog->setRange(0, maskFileNames.size()*2);
	progressDialog->setValue(0);
	progressDialog->setLabelText(tr("Loading BGS data for frame %1 of %2").arg(0).arg(maskFileNames.size()*2));
	progressDialog->show();			
	qApp->processEvents();

	for (int i=0; i<maskFileNames.size(); i++) {
		data->scenesInfos->at(i)->bgsMask = new QPixmap();
		data->scenesInfos->at(i)->bgsMask->load(QString::fromStdString(maskDir.path().toStdString() + "\\" + maskFileNames[i].toStdString()));
		/*qDebug() << "loading from " << QString::fromStdString(saveDir.path().toStdString() + "\\bw_" + maskFileNames[i].toStdString()) << endl;
		QFile test_bgsMaskFile(QString::fromStdString(saveDir.path().toStdString() + "\\test_bw_" + maskFileNames[i].toStdString()));
		test_bgsMaskFile.open(QIODevice::WriteOnly);
		data->scenesInfos->at(i)->bgsMask->save(&test_bgsMaskFile, "PNG");
		qDebug() << "saving to " << QString::fromStdString(saveDir.path().toStdString() + "\\test_bw_" + maskFileNames[i].toStdString()) << endl;*/

		progressDialog->setValue(i+1);
		progressDialog->setLabelText(tr("Saving BGS data for frame %1 of %2").arg(i+1).arg(maskFileNames.size()*2));
		qApp->processEvents();
	}

	filters.clear();
    filters << "iAm_*.png";

    maskFileNames = maskDir.entryList(filters, QDir::Files | QDir::NoSymLinks);	

	for (int i=0; i<maskFileNames.size(); i++) {		
		data->scenesInfos->at(i)->imageAndBgsMask = new QPixmap();
		data->scenesInfos->at(i)->imageAndBgsMask->load(QString::fromStdString(maskDir.path().toStdString() + "\\" + maskFileNames[i].toStdString()));
		/*QFile test_imageAndBgsMaskFile(QString::fromStdString(saveDir.path().toStdString() + "\\test_iAm_" + maskFileNames[i].toStdString()));
		test_imageAndBgsMaskFile.open(QIODevice::WriteOnly);
		data->scenesInfos->at(i)->imageAndBgsMask->save(&test_imageAndBgsMaskFile, "PNG");*/

		progressDialog->setValue(maskFileNames.size()+i+1);
		progressDialog->setLabelText(tr("Saving BGS data for frame %1 of %2").arg(maskFileNames.size()+i+1).arg(maskFileNames.size()*2));
		qApp->processEvents();
	}

	ui->previewBGSCheckTagging->setEnabled(true);
	ui->previewFrameAndBGSCheckTagging->setEnabled(true);
	ui->previewBGSCheck->setEnabled(true);
	ui->previewFrameAndBGSCheck->setEnabled(true);
	ui->useBGSCheck->setEnabled(true);

	progressDialog->hide();
	bgsLoaded = true;
	qApp->processEvents();
}

void TaggingWidget::on_previewFrameCheckTagging_clicked()
{
	qDebug() << "previewFrameCheckTagging clicked!" << ui->previewFrameCheckTagging->isChecked() << endl;
	updateFiles(data->currentSceneInfoIndex);
}

void TaggingWidget::on_previewBGSCheckTagging_clicked()
{
	qDebug() << "previewBGSCheckTagging clicked!" << ui->previewBGSCheckTagging->isChecked() << endl;
	updateFiles(data->currentSceneInfoIndex);
}

void TaggingWidget::on_previewFrameAndBGSCheckTagging_clicked()
{
	qDebug() << "previewFrameAndBGSCheckTagging clicked!" << ui->previewFrameAndBGSCheckTagging->isChecked() << endl;
	updateFiles(data->currentSceneInfoIndex);
}

void TaggingWidget::on_loadROIsFromXML_clicked()
{
	QString basePath = currentDir.path()+ "\\rois\\";
	FileProcessor fileProcessor = FileProcessor();		
	XMLProcessor xmlProcessor = XMLProcessor(); 

	progressDialog->setWindowTitle(tr("Reading ROIs from XML..."));
	xmlProcessor.readRoisFromXML(data->scenesInfos, basePath + "rois.xml");

	int totalSize = data->scenesInfos->size();
	
	progressDialog->show();
	progressDialog->setCancelButtonText(tr("&Cancel"));
	progressDialog->setRange(0, totalSize);
	progressDialog->setWindowTitle(tr("Computing ROIs Summary..."));

	data->labelsSummary.clear();

	for(int i=0; i<totalSize; i++) {
		progressDialog->setValue(i+1);
		progressDialog->setLabelText(tr("Computing ROIs Summary for frame %1 of %2...").arg(i+1).arg(totalSize));

		if (progressDialog->wasCanceled()) {
			break;
		}
		
		for(int j=0; j<data->scenesInfos->at(i)->rois->size(); j++) {
			DiagramROI *roi = data->scenesInfos->at(i)->rois->at(j);

			if(!roi->isRemoved() && roi->getWidth() > data->minRoiWidth && roi->getHeight() > data->minRoiHeight) {
				QList<DiagramROI*> labelList;

				if(data->labelsSummary.contains(roi->getLabel())) {
					labelList = data->labelsSummary.value(roi->getLabel());				
				} else {
					labelList = QList<DiagramROI*>();
				}

				labelList.append(roi);
				data->labelsSummary.insert(roi->getLabel(), labelList);		
			}				
		}

		qApp->processEvents();
	}
	
	ui->summaryTabWidget->clear();

	QList<QString> labels = data->labelsSummary.keys();
	QPixmap tabIconColor(15,15);
    QPainter tabIconPainter(&tabIconColor);

	progressDialog->setRange(0, labels.size());
	progressDialog->show();
	progressDialog->setWindowTitle(tr("Displaying ROIs Summary..."));

	for(int i=0; i<labels.size(); i++) {
		progressDialog->setValue(i+1);
		progressDialog->setLabelText(tr("Displaying ROIs Summary for label %1 of %2...").arg(i+1).arg(labels.size()));

		QList<DiagramROI*> rois = data->labelsSummary.value(labels.at(i));
		QListWidget * labelList = new QListWidget();
		labelList->setViewMode(QListWidget::IconMode);
		labelList->setIconSize(QSize(100,100));

		for(int j=0; j<rois.size(); j++) {
			DiagramROI * roi = rois.at(j);

			if(!roi->isRemoved() && roi->getWidth() > data->minRoiWidth && roi->getHeight() > data->minRoiHeight) {
				QListWidgetItem *roiItem = new QListWidgetItem(labelList);
				QString frameLabel;
				frameLabel.sprintf("Frame %03d", roi->getFrameId()+1);
				roiItem->setText(frameLabel);
				roiItem->setFont(QFont("Newyork", 14));
				QPixmap roiImage = data->scenesInfos->at(roi->getFrameId())->image->copy(roi->getTpx(), roi->getTpy(), roi->getWidth(), roi->getHeight()).scaledToHeight(roi->getHeight()*2);
				QIcon roiIcon(roiImage);
				roiItem->setIcon(roiIcon);
				roiItem->setTextAlignment(Qt::AlignBottom | Qt::AlignHCenter);
				roiItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
			}			
		}
		
		tabIconPainter.setBrush(rois.at(0)->getColor());
        tabIconPainter.drawRect(QRect(QPoint(0,0), QPoint(15,15) - QPoint(2,2)));
		ui->summaryTabWidget->addTab(labelList, QIcon(tabIconColor), labels.at(i));		

		if (progressDialog->wasCanceled()) {
			break;
		}

		qApp->processEvents();
	}			

	ui->summaryTabWidget->setEnabled(true);
	ui->saveRoisToDiskButton->setEnabled(true);
	ui->saveBGSFrameCheckbox->setEnabled(true);
	ui->saveBGSMaskCheckbox->setEnabled(true);

	progressDialog->hide();
	qApp->processEvents();

	updateTreeWidget();
	updateImage(0);
}

void TaggingWidget::on_saveLabelsToXML_clicked()
{
	QString basePath = currentDir.path()+ "\\";
	FileProcessor fileProcessor = FileProcessor();		
	XMLProcessor xmlProcessor = XMLProcessor(); 

	//progressDialog->setWindowTitle(tr("Saving Labels to XML..."));
	xmlProcessor.saveLabelsToXML(data->scenesLabels, basePath + "labels.xml");
}

void TaggingWidget::on_loadLabelsFromXML_clicked()
{
	QString basePath = currentDir.path()+ "\\";
	FileProcessor fileProcessor = FileProcessor();
	XMLProcessor xmlProcessor = XMLProcessor(); 

	//progressDialog->setWindowTitle(tr("Reading Labels from XML..."));
	xmlProcessor.readLabelsFromXML(data->scenesLabels, basePath + "labels.xml");
	data->sceneLabelsCounter = data->scenesLabels->size();

	if(data->sceneLabelsCounter > 0) {
		ui->labelsListWidget->clear();
		ui->labelsListWidgetTagging->clear();

		for(int i=0; i<data->sceneLabelsCounter; i++) {
			DiagramROILabel *label = data->scenesLabels->at(i);
			if(!label->isRemoved()) {
				addLabel(label->getId(), label->getName(), label->getColor(), false);
			}			
		}
	}	
}

void TaggingWidget::loadData() {
	on_loadLabelsFromXML_clicked();
	on_loadROIsFromXML_clicked();
}

void TaggingWidget::saveData() {
	on_saveLabelsToXML_clicked();
	on_computeRoiSummary_clicked();
	on_saveRoisToDiskButton_clicked();
}
void TaggingWidget::on_eraseUntilLast_clicked()
{
	for(int i=data->currentSceneInfoIndex; i<data->scenesInfos->size(); i++) {
		data->scenesInfos->at(i)->rois->clear();
	}

	ui->roisListWidget->clear();
	ui->roiTable->setRowCount(0);
	scene->clear();
	updateTreeWidget();
	updateImage(data->currentSceneInfoIndex);
}

void TaggingWidget::on_eraseCurrent_clicked()
{
	data->scenesInfos->at(data->currentSceneInfoIndex)->rois->clear();

	ui->roisListWidget->clear();
	ui->roiTable->setRowCount(0);
	scene->clear();
	updateTreeWidget();
	updateImage(data->currentSceneInfoIndex);
}

void TaggingWidget::on_eraseSubsampled_clicked()
{
	QList<int> targetIndexes = QList<int>();
	generateChildIndexesList(data->currentSceneInfoIndex+1, &targetIndexes);

	for(int i=0; i<targetIndexes.size(); i++) {
		data->scenesInfos->at(targetIndexes.at(i))->rois->clear();
	}

	ui->roisListWidget->clear();
	ui->roiTable->setRowCount(0);
	scene->clear();
	updateTreeWidget();
	updateImage(data->currentSceneInfoIndex);
}

void TaggingWidget::on_playPreviewButton_clicked()
{
	if(stopPreview) {
		stopPreview = false;
        int fpsPreview = ui->fpsPreview->text().toInt();
        currentPreviewIndex = 0;
        currentTopLevelItems = subsampledItems.size();
//        qDebug() << "playing " << currentTopLevelItems << endl;
        ui->playPreviewButton->setText("Stop");
        ui->fpsPreview->setEnabled(false);
        ui->subsamplingCheck->setEnabled(false);
        ui->subsamplingSlider->setEnabled(false);
        ui->subsamplingValue->setEnabled(false);
        //ui->subsamplingUpdateButton->setEnabled(false);
        previewPlayerTimer->setInterval(1000/fpsPreview);
        previewPlayerTimer->start();
        ui->playPreviewProgressBar->setRange(0, currentTopLevelItems);
    } else {
		stopPreview = true;
        previewPlayerTimer->stop();
        ui->playPreviewButton->setText("Play");
        ui->fpsPreview->setEnabled(true);
        ui->subsamplingCheck->setEnabled(true);
        ui->subsamplingSlider->setEnabled(true);
        ui->subsamplingValue->setEnabled(true);
        //ui->subsamplingUpdateButton->setEnabled(true);
    }
}
