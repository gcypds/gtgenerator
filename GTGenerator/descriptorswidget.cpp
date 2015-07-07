#include "taggingwidget.h"
#include "ui_taggingwidget.h"

#include <QDebug>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QProgressDialog>
#include <QApplication>
#include <QCoreApplication>

#include "diagramitem.h"
#include "diagramscene.h"
#include "colorlistwidgetitem.h"
#include "diagramsceneinfo.h"
#include "diagramroi.h"

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
#include <time.h>

const QString DEFAULT_DIR_KEY("default_dir");
const int InsertTextButton = 10;
const float scalePercentageWidth = 0.88;
const float scalePercentageHeight = 0.88;
double gridWidth;
int currentPreviewIndex = 0;
int currentTopLevelItems = 0;
int subsamplingStep = 0;
int imagesLength = 0;
QList<int> subsampledItems;

QTimer *previewPlayerTimer;
const QFont roiItemFont = QFont("Newyork", 18);

#define qApp (static_cast<QApplication *>(QCoreApplication::instance()))

TaggingWidget::TaggingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaggingWidget)
{
     dirSettingsPath = QApplication::applicationDirPath() + "/settings.ini";
//    qDebug() << "Creating settings file: " << dirSettingsPath << endl;

    QSettings dirSettings(dirSettingsPath, QSettings::IniFormat);
    //dirSettings.setValue(DEFAULT_DIR_KEY, "G:\\data\\sebastianvilla139\\work\\datasets\\survmantics\\00001");
    dirSettings.setValue(DEFAULT_DIR_KEY, "Z:\\master\\survmantics\\dataset\\processed\\00001");

    ui->setupUi(this);

//    QPixmap pix( "Z:\\master\\survmantics\\dataset\\processed\\00001\\image00001.png" );
    //QPixmap pix( "Z:\\master\\fish_contest\\dataset\\videos\\test_video\\0.png" );

    scene = new DiagramScene(ui->imageArea);
    //scene->setSceneRect(QRectF(0, 0, pix.width()*scalePercentageWidth, pix.height()*scalePercentageHeight));
    //scene->setSceneRect(QRectF(0, 0, width()*scalePercentageWidth, height()*scalePercentageHeight));

    view = new DiagramView(scene);

//    QPixmap finalPix = pix.scaledToWidth(width()*scalePercentageWidth);

//    scene->addPixmap( finalPix );

    //imageArea = new ImageArea(true, "", ui->imageArea);

    //filesTable = new QTableWidget(0, 2);
    ui->roiTable->setRowCount(0);
    ui->roiTable->setColumnCount(8);
    QStringList roiTableHeader;
    roiTableHeader << tr("Numero ROI") << tr("Etiqueta") << tr("W") << tr("H") << tr("TLX") << tr("TLY") << tr("BRX") << tr("BRY");    

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
    treeTableHeader << tr("Frame") << tr("Image") << tr("Processed");
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
    previewView = new QGraphicsView(previewScene);

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

    ui->imageTree->setStyleSheet("QTreeWidget::item:selected { background-color: yellow; border-width:1px; color:black;}");

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
                int division = index/subsamplingStep;
//                qDebug() << "division: " << division << endl;

                int parentIndex = division*subsamplingStep;
//                qDebug() << "parentIndex: " << parentIndex << endl;

                int childIndex = index - parentIndex - 1;
//                qDebug() << "childIndex: " << childIndex << endl;

//                qDebug() << "subsamplingStep:" << subsamplingStep << endl;
//                qDebug() << "calculusIndex:" << calculusIndex << endl;
                ui->imageTree->collapseAll();
                ui->imageTree->topLevelItem(parentIndex)->child(childIndex)->setExpanded(true);
                ui->imageTree->setCurrentItem(ui->imageTree->topLevelItem(parentIndex)->child(childIndex));
                ui->imageTree->scrollToItem(ui->imageTree->topLevelItem(parentIndex)->child(childIndex));
            } else {
//                qDebug() << "not hidden..." << endl;
                ui->imageTree->collapseAll();
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
                int division = index/subsamplingStep;
//                qDebug() << "division: " << division << endl;

                int parentIndex = division*subsamplingStep;
//                qDebug() << "parentIndex: " << parentIndex << endl;

                int childIndex = index - parentIndex - 1;
//                qDebug() << "childIndex: " << childIndex << endl;

//                qDebug() << "subsamplingStep:" << subsamplingStep << endl;
//                qDebug() << "calculusIndex:" << calculusIndex << endl;
                ui->imageTree->collapseAll();
                ui->imageTree->topLevelItem(parentIndex)->child(childIndex)->setExpanded(true);
                ui->imageTree->setCurrentItem(ui->imageTree->topLevelItem(parentIndex)->child(childIndex));
                ui->imageTree->scrollToItem(ui->imageTree->topLevelItem(parentIndex)->child(childIndex));
            } else {
//                qDebug() << "not hidden..." << endl;
                ui->imageTree->collapseAll();
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
        } else if (ke->key() == Qt::Key_Delete ) {
            ui->labelsListWidget->takeItem(ui->labelsListWidget->currentRow());
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
    }
    else
        return false;
}

void TaggingWidget::on_selectVideo_clicked()
{
    QString directory = QFileDialog::getOpenFileName(this, tr("Seleccionar video:"), QDir::currentPath(), tr("Videos (*.avi *.flv *.mp4)"));

    if (!directory.isEmpty()) {
//        qDebug() << "Selected video: " << directory << endl;
        ui->videoDirPath->setText(directory);
    }
}

void TaggingWidget::on_selectDir_clicked()
{
    QSettings dirSettings(dirSettingsPath, QSettings::IniFormat);
//    qDebug() << "Reading dir settings as: " << dirSettings.value(DEFAULT_DIR_KEY).toString() << endl;
    QString directory = QFileDialog::getExistingDirectory(this, tr("Seleccionar directorio:"), dirSettings.value(DEFAULT_DIR_KEY).toString());
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

        scene->scenesInfos->clear();
        //qDebug() << "Showing files.." << endl;
        showFiles(files);

    }
}

//! [8]
void TaggingWidget::showFiles(const QStringList &files)
{
    QProgressDialog progressDialog(this);
    progressDialog.show();
    progressDialog.setCancelButtonText(tr("&Cancel"));
    progressDialog.setRange(0, files.size());
    progressDialog.setWindowTitle(tr("Listing Images..."));

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
    ui->subsamplingUpdateButton->setEnabled(false);
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
    previewScene->clear();

    gridWidth = (double)ui->subsamplingMonitor->width()/(double)files.size();

//    qDebug() << "ui->subsamplingMonitor->width()" << ui->subsamplingMonitor->width() << endl;
//    qDebug() << "files.size()" << files.size() << endl;
//    qDebug() << "gridWidth" << gridWidth << endl;
//    qDebug() << "(int)gridWidth*files.size()" << ((int)gridWidth)*files.size() << endl;
//    qDebug() << "gridWidth*files.size()" << gridWidth*files.size() << endl;

    ui->subsamplingMonitor->setGridSize(QSize(gridWidth, 33));
    ui->subsamplingMonitor->setIconSize(QSize(gridWidth, 30));

    int intSize = ((int)gridWidth)*files.size();
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

        progressDialog.setValue(i+1);
        progressDialog.setLabelText(tr("Loading image number %1 of %2...").arg(i+1).arg(files.size()));       

        DiagramSceneInfo info = DiagramSceneInfo();

        if (progressDialog.wasCanceled()) {

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
            ui->subsamplingUpdateButton->setEnabled(false);
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
            previewScene->clear();

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

        QPixmap fileImage;
        fileImage.load(currentDir.absoluteFilePath(files[i]));
        info.image = fileImage;
        info.imageName = files[i];
        info.imagePath = currentDir.absoluteFilePath(files[i]);
//        info.imageSize = QString::number(size);

        QIcon fileIcon(fileImage);
        //fileIcon.setIconSize(QSize(50, 50));
        pieceItem->setIcon(fileIcon);

        //qDebug() << "Setting image for " << currentDir.absoluteFilePath(files[i]) << endl;
        pieceItem->setData(Qt::UserRole, QVariant(fileImage));
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
        scene->scenesInfos->append(info);

        QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->imageTree);

        // QTreeWidgetItem::setText(int column, const QString & text)
        QString treeLabel;
        treeLabel.sprintf("%03d", i+1);

        treeItem->setText(0, treeLabel);
        //treeItem->setIcon();
        treeItem->setText(1, files[i]);
        treeItem->setText(2, "false");

        treeItem->setBackgroundColor(0, QColor(51, 153, 255));
        treeItem->setBackgroundColor(1, QColor(51, 153, 255));
        treeItem->setBackgroundColor(2, QColor(51, 153, 255));

        treeItem->setTextAlignment(0, Qt::AlignCenter);
        treeItem->setTextAlignment(1, Qt::AlignCenter);
        treeItem->setTextAlignment(2, Qt::AlignCenter);

        treeItem->setData(0, Qt::UserRole, QVariant(fileImage));
        treeItem->setData(0, Qt::UserRole+2, i);
//        treeItem->setData(1, Qt::UserRole+2, i);
//        treeItem->setData(2, Qt::UserRole+2, i);
        treeItem->setIcon(1, fileIcon);
        //treeItem->setForeground(1, QBrush(fileImage));

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

    progressDialog.hide();

    QString totalLabel;
    totalLabel.sprintf("Total frames: %d", files.size());
    ui->totalFramesLabel->setEnabled(true);
    ui->totalFramesLabel->setText(totalLabel);

    QString showingLabel;
    showingLabel.sprintf("Mostrando  %d  frames de  %d - %.1f%", files.size(), files.size(), 100.0);
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
}

void TaggingWidget::on_fileListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //imageArea->clearSelection();
    int index = item->data(Qt::UserRole+2).toString().toInt();
    ui->subsamplingMonitor->setCurrentRow(index);

    if(ui->imageTree->topLevelItem(index)->isHidden()) {
        int division = index/subsamplingStep;
//                qDebug() << "division: " << division << endl;

        int parentIndex = division*subsamplingStep;
//                qDebug() << "parentIndex: " << parentIndex << endl;

        int childIndex = index - parentIndex - 1;
//                qDebug() << "childIndex: " << childIndex << endl;

//                qDebug() << "subsamplingStep:" << subsamplingStep << endl;
//                qDebug() << "calculusIndex:" << calculusIndex << endl;
        ui->imageTree->collapseAll();
        ui->imageTree->topLevelItem(parentIndex)->child(childIndex)->setExpanded(true);
        ui->imageTree->setCurrentItem(ui->imageTree->topLevelItem(parentIndex)->child(childIndex));
        ui->imageTree->scrollToItem(ui->imageTree->topLevelItem(parentIndex)->child(childIndex));
    } else {
//                qDebug() << "not hidden..." << endl;
        ui->imageTree->collapseAll();
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

    scene->currentSceneInfoIndex = index;
    //qDebug() << "scene->currentSceneInfoIndex" << scene->currentSceneInfoIndex << endl;
    scene->currentSceneInfo = scene->scenesInfos->at(scene->currentSceneInfoIndex);

    scene->clear();
    ui->imageNameLabel->setText(scene->scenesInfos->at(scene->currentSceneInfoIndex).imageName + " - " + scene->scenesInfos->at(scene->currentSceneInfoIndex).imagePath);
    scene->addPixmap( scene->scenesInfos->at(scene->currentSceneInfoIndex).image );
    scene->setSceneRect(QRectF(0, 0, scene->scenesInfos->at(scene->currentSceneInfoIndex).image.width(), scene->scenesInfos->at(scene->currentSceneInfoIndex).image.height()));

//    qDebug() << "loading sceneInfo for " << scene->currentSceneInfoIndex << endl;
//    qDebug() << "scene->scenesInfos->at(scene->currentSceneInfoIndex).rois.size() " << scene->scenesInfos->at(scene->currentSceneInfoIndex).rois->size() << endl;

    scene->roiCounter = scene->scenesInfos->at(scene->currentSceneInfoIndex).rois->size();
    scene->roiTable->setRowCount(0);
    ui->roisListWidget->clear();
    ui->roisListWidget->setIconSize(QSize(300, 400));

    for(int i=0; i<scene->scenesInfos->at(scene->currentSceneInfoIndex).rois->size();i++) {
        DiagramROI * roi = scene->scenesInfos->at(scene->currentSceneInfoIndex).rois->at(i);

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
            DiagramItem *itemToAdd = new DiagramItem(*roi, i, scene->scenesInfos, scene->currentSceneInfoIndex, scene->roiTable, scene->roiList, NULL, NULL);
            scene->addItem(itemToAdd);
    //        qDebug() << "***item added!" << endl;
    //        qDebug() << "roi table[4]: " << bryItem->text() << endl;
        }

        QString itemLabel;
        itemLabel.sprintf("%03d", roi->getIndex());

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

        scene->roiTable->insertRow(roi->getIndex()-1);

        if(roi->isRemoved()) {
            scene->roiTable->hideRow(roi->getIndex()-1);
        } else {
            scene->roiTable->setItem(roi->getIndex()-1, 0, roiNameItem);
    //        qDebug() << "roi table[0]: " << roiNameItem->text() << endl;

            scene->roiTable->setItem(roi->getIndex()-1, 1, labelItem);

            scene->roiTable->setItem(roi->getIndex()-1, 2, widthItem);

            scene->roiTable->setItem(roi->getIndex()-1, 3, heightItem);

            scene->roiTable->setItem(roi->getIndex()-1, 4, tpxItem);
    //        qDebug() << "roi table[1]: " << tpxItem->text() << endl;

            scene->roiTable->setItem(roi->getIndex()-1, 5, tpyItem);
    //        qDebug() << "roi table[2]: " << tpyItem->text() << endl;

            scene->roiTable->setItem(roi->getIndex()-1, 6, brxItem);
    //        qDebug() << "roi table[3]: " << brxItem->text() << endl;

            scene->roiTable->setItem(roi->getIndex()-1, 7, bryItem);
        }

        QListWidgetItem *roiItem = new QListWidgetItem(ui->roisListWidget);
        roiItem->setText(roi->getLabel() + " " + itemLabel);
        roiItem->setTextColor(roi->isLabeled()?roi->getColor():Qt::black);
        roiItem->setFont(roiItemFont);
        roiItem->setData(Qt::UserRole, roi->getIndex());
        roiItem->setData(Qt::UserRole+1, roi->getTpx());
        roiItem->setData(Qt::UserRole+2, roi->getTpy());
        roiItem->setData(Qt::UserRole+3, roi->getWidth());
        roiItem->setData(Qt::UserRole+4, roi->getHeight());
        //roiItem->setBackground(roi->isLabeled()?roi->getColor():Qt::white);
        QPixmap roiImage = scene->scenesInfos->at(scene->currentSceneInfoIndex).image.copy(roi->getTpx(), roi->getTpy(), roi->getWidth(), roi->getHeight()).scaledToHeight(roi->getHeight()*2);
        QIcon roiIcon(roiImage);
        roiItem->setIcon(roiIcon);
        roiItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        roiItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
    }

    //ui->roisListWidget->sortItems();
    scene->showingImage = true;

//    imageArea->zoomImage(0.0);
//    imageArea->open(filename);
//    imageArea->zoomImage(2.0);
//    imageArea->repaint();
//    DataSingleton::Instance()->setInstrument(CURSOR);
    scene->roiList = ui->roisListWidget;
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

    mime->setColorData(item->data(Qt::UserRole));
    mime->setText(item->text());
//    qDebug() << "item->text()" << item->text() << endl;
    drag->exec();
}

void TaggingWidget::deleteItem()
{
    qDebug() << "deleteItem" << endl;
    foreach (QGraphicsItem *item, scene->selectedItems()) {
         int removedIndex = qgraphicsitem_cast<DiagramItem *>(item)->itemIndex;
         scene->roiTable->hideRow(removedIndex);
         scene->removeItem(item);
         scene->scenesInfos->at(scene->currentSceneInfoIndex).rois->at(removedIndex)->setRemoved(true);
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

void TaggingWidget::on_addLabel_clicked()
{
    if(!ui->labelToAdd->text().isEmpty()) {

        QString label = ui->labelToAdd->text().toUpper();

        if(ui->labelsListWidget->findItems(label, Qt::MatchExactly).size() == 0) {
            QPixmap colorItemButton(50,50);
            QPainter painterButton(&colorItemButton);
            painterButton.setBrush(colorToAdd);
            painterButton.drawRect(QRect(QPoint(0,0), QPoint(50, 50) - QPoint(2,2)));
            ui->selectLabelColor->setIcon(QIcon(colorItemButton));

            ColorListWidgetItem *pieceItem = new ColorListWidgetItem(ui->labelsListWidget);

            QPixmap colorItem(100,100);

            QPainter painter(&colorItem);

            pieceItem->setText(label);
            pieceItem->setToolTip(label);
            pieceItem->setTextAlignment(Qt::AlignVCenter);

            //painter.setBrush(Qt::SolidPattern);
            //painter.setPen(QPen(color, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.setBrush(colorToAdd);
            //painter.setPen(Qt::darkGreen);
            painter.drawRect(QRect(QPoint(0,0), QPoint(100,100) - QPoint(2,2)));

            pieceItem->setData(Qt::UserRole, colorToAdd);
//            pieceItem->setData(Qt::UserRole+1, label);
//            pieceItem->setData(Qt::UserRole+2, label);
            pieceItem->setData(Qt::UserRole+3, colorItem);

            pieceItem->setIcon(QIcon(colorItem));
            pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEditable);
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
//        qDebug() << "item.at(" << i << ") " << scene->items().at(i)->type() << endl;
        DiagramItem *item = qgraphicsitem_cast<DiagramItem *>(scene->items().at(i));

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
    ui->subsamplingUpdateButton->setEnabled(checked);

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

    imagesLength = scene->scenesInfos->size();    

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

            QProgressDialog progressDialog(this);
            progressDialog.show();
            progressDialog.setCancelButtonText(tr("&Cancel"));
            progressDialog.setRange(0, subsamplingAmount);
            progressDialog.setWindowTitle(tr("Subsampling images..."));

    //        for(int i=0;i<imagesLength; i=i+subsamplingStep) {
    //            subsampledCounter++;
    //            progressDialog.setValue(subsampledCounter);
    //            progressDialog.setLabelText(tr("Subsampling image number %1 of %2...").arg(subsampledCounter).arg(subsamplingAmount));
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

                    treeItem->setHidden(false);
                    treeItem->setBackgroundColor(0, QColor(51, 153, 255));
                    treeItem->setBackgroundColor(1, QColor(51, 153, 255));
                    treeItem->setBackgroundColor(2, QColor(51, 153, 255));

//                    treeItem->setTextAlignment(0, Qt::AlignCenter);
//                    treeItem->setTextAlignment(1, Qt::AlignCenter);
//                    treeItem->setTextAlignment(2, Qt::AlignCenter);

                    if(subsampledCounter <= subsamplingAmount) {
                        progressDialog.setValue(subsampledCounter);
                        progressDialog.setLabelText(tr("Subsampling image number %1 of %2...").arg(subsampledCounter).arg(subsamplingAmount));
//                        qDebug() << "subsampledCounter " << subsampledCounter << endl;
//                        qDebug() << "subsamplingAmount " << subsamplingAmount << endl;                                                
                    }

                    qApp->processEvents();
                } else {
                    painter.fillRect(QRect(QPoint(0,0), QPoint(gridWidth*0.9, 33)), Qt::white);

                    if(lastParentItem != NULL) {
                        //ui->imageTree->takeTopLevelItem(i);
//                        qDebug() << "adding child " << i << " to parent " << lastSubsamplingParentIndex << endl;
                        treeItem->setHidden(true);
                        treeItem->takeChildren();
                        QTreeWidgetItem *clonedChild = treeItem->clone();
                        clonedChild->setBackgroundColor(0, Qt::white);
                        clonedChild->setBackgroundColor(1, Qt::white);
                        clonedChild->setBackgroundColor(2, Qt::white);
                        //clonedChild->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
                        lastParentItem->addChild(clonedChild);
                    }
//                    lastSubsamplingParentCounter++;
                }
                monitorItem->setIcon(QIcon(colorItem));
            }
            ui->subsamplingMonitor->setCurrentRow(-1);
            progressDialog.hide();
//            qApp->processEvents();
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

            lastParentItem->setHidden(false);
            lastParentItem->setBackgroundColor(0, QColor(51, 153, 255));
            lastParentItem->setBackgroundColor(1, QColor(51, 153, 255));
            lastParentItem->setBackgroundColor(2, QColor(51, 153, 255));

            qApp->processEvents();

            for(int i=1; i<imagesLength; i++) {
                painter.fillRect(QRect(QPoint(0,0), QPoint(gridWidth*0.9, 33)), Qt::white);

                if(lastParentItem != NULL) {
                    QTreeWidgetItem *treeItem = ui->imageTree->topLevelItem(i);
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
    showingLabel.sprintf("Mostrando  %d  frames de  %d - %.1f%", subsampledItems.size(), imagesLength, showingPercentage);
    ui->showingFramesLabel->setEnabled(true);
    ui->showingFramesLabel->setText(showingLabel);
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
        int division = index/subsamplingStep;
//                qDebug() << "division: " << division << endl;

        int parentIndex = division*subsamplingStep;
//                qDebug() << "parentIndex: " << parentIndex << endl;

        int childIndex = index - parentIndex - 1;
//                qDebug() << "childIndex: " << childIndex << endl;

//                qDebug() << "subsamplingStep:" << subsamplingStep << endl;
//                qDebug() << "calculusIndex:" << calculusIndex << endl;
        ui->imageTree->collapseAll();
        ui->imageTree->topLevelItem(parentIndex)->child(childIndex)->setExpanded(true);
        ui->imageTree->setCurrentItem(ui->imageTree->topLevelItem(parentIndex)->child(childIndex));
        ui->imageTree->scrollToItem(ui->imageTree->topLevelItem(parentIndex)->child(childIndex));
    } else {
//                qDebug() << "not hidden..." << endl;
        ui->imageTree->collapseAll();
        ui->imageTree->setCurrentItem(ui->imageTree->topLevelItem(index));
        ui->imageTree->scrollToItem(ui->imageTree->topLevelItem(index));
    }
    updateImage(index);
}

void TaggingWidget::playPreview() {
//    qDebug() << "playing preview at " << currentPreviewIndex << endl;
    QTreeWidgetItem *treeItem = ui->imageTree->topLevelItem(subsampledItems.at(currentPreviewIndex));
//    qDebug() << "got treeitem at " << subsampledItems.at(currentPreviewIndex) << endl;
    QPixmap image = qvariant_cast<QPixmap>(treeItem->data(0, Qt::UserRole));    
    QPainter painter(&image);
    painter.setPen(QPen(QBrush(Qt::yellow), 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    QFont tooltipFont = QFont("Newyork", 18);
    painter.setFont(tooltipFont);
    QString frameLabel;
    frameLabel.sprintf("Frame %03d", subsampledItems.at(currentPreviewIndex)+1);
    painter.drawText(QPoint(10,30), frameLabel);

    if(ui->showROIsCheckbox->isChecked()) {
        //qDebug() << "scene->currentSceneInfoIndex" << scene->currentSceneInfoIndex << endl;
//        qDebug() << "ui->showROIsCheckbox->isChecked()" << ui->showROIsCheckbox->isChecked() << endl;

        //DiagramSceneInfo currentSceneInfo = scene->scenesInfos->at(subsampledItems.at(currentPreviewIndex));

        int previewRoiCount = scene->scenesInfos->at(subsampledItems.at(currentPreviewIndex)).rois->size();

//        qDebug() << "previewRoiCount" << previewRoiCount << endl;

        for(int i=0; i<previewRoiCount;i++) {
            DiagramROI * roi = scene->scenesInfos->at(subsampledItems.at(currentPreviewIndex)).rois->at(i);

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
                    painter.drawRect(roi->getTpx(), roi->getTpy(), roi->getWidth(), roi->getHeight());
                } else {
//                    qDebug() << "roi->isLabeled()" << roi->isLabeled() << endl;
                    if(!ui->showOnlyLabeledROIsCheckbox->isChecked()) {
//                        qDebug() << "ui->showOnlyLabeledROIsCheckbox->isChecked()" << ui->showOnlyLabeledROIsCheckbox->isChecked() << endl;
                        painter.setPen(QPen(QBrush(Qt::white), 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                        painter.drawRect(roi->getTpx(), roi->getTpy(), roi->getWidth(), roi->getHeight());
                    }
                }
            }
        }
    }

    previewScene->clear();
    QPixmap scaled = image.scaledToWidth(ui->previewWidget->width()*0.9);
    previewScene->addPixmap(scaled);
    previewScene->setSceneRect(QRectF(0, 0, scaled.width(), scaled.height()));
    currentPreviewIndex++;

    //qDebug() << "ui->imageTree->topLevelItemCount() " << ui->imageTree->topLevelItemCount() << endl;

    ui->playPreviewProgressBar->setValue(currentPreviewIndex);

    if(currentPreviewIndex >= currentTopLevelItems) {
//        qDebug() << "before reseting..." << currentPreviewIndex << endl;
        currentPreviewIndex = 0;
//        qDebug() << "reseting currentPreviewIndex ..." << currentPreviewIndex << endl;
    }
}

void TaggingWidget::on_playPreviewButton_toggled(bool checked)
{
    if(checked) {
        if(previewPlayerTimer != NULL) {
            delete previewPlayerTimer;
        }

        previewPlayerTimer = new QTimer(this);
        connect(previewPlayerTimer, SIGNAL(timeout()), this, SLOT(playPreview()));

        int fpsPreview = ui->fpsPreview->text().toInt();
        currentPreviewIndex = 0;
        currentTopLevelItems = subsampledItems.size();
//        qDebug() << "playing " << currentTopLevelItems << endl;
        ui->playPreviewButton->setText("Stop");
        ui->fpsPreview->setEnabled(false);
        ui->subsamplingCheck->setEnabled(false);
        ui->subsamplingSlider->setEnabled(false);
        ui->subsamplingValue->setEnabled(false);
        ui->subsamplingUpdateButton->setEnabled(false);
        previewPlayerTimer->setInterval(1000/fpsPreview);
        previewPlayerTimer->start();
        ui->playPreviewProgressBar->setRange(0, currentTopLevelItems);
    } else {
        previewPlayerTimer->stop();
        ui->playPreviewButton->setText("Play");
        ui->fpsPreview->setEnabled(true);
        ui->subsamplingCheck->setEnabled(true);
        ui->subsamplingSlider->setEnabled(true);
        ui->subsamplingValue->setEnabled(true);
        ui->subsamplingUpdateButton->setEnabled(true);
    }
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
    QColor itemColor = qvariant_cast<QColor>(item->data(Qt::UserRole));
    QColor selectedColor = colorDialog->getColor(itemColor);

    if(selectedColor != itemColor) {
        QPixmap colorItem(100, 100);
        QPainter painter(&colorItem);
        painter.setBrush(selectedColor);
        painter.drawRect(QRect(QPoint(0,0), QPoint(100, 100) - QPoint(2,2)));
        item->setIcon(QIcon(colorItem));
        item->setData(Qt::UserRole, selectedColor);
        item->setData(Qt::UserRole+3, colorItem);
    }

    ui->labelsListWidget->openPersistentEditor(item);
}