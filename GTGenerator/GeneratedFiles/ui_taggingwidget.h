/********************************************************************************
** Form generated from reading UI file 'taggingwidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAGGINGWIDGET_H
#define UI_TAGGINGWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QToolButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaggingWidget
{
public:
    QVBoxLayout *verticalLayout_7;
    QTabWidget *globalTabs;
    QWidget *tab_8;
    QVBoxLayout *verticalLayout_11;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLineEdit *videoDirPath;
    QPushButton *selectDir;
    QPushButton *selectVideo;
    QListWidget *fileListWidget;
    QSpacerItem *verticalSpacer;
    QWidget *tab_21;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_2;
    QLineEdit *labelToAdd;
    QLabel *label_3;
    QToolButton *selectLabelColor;
    QSpacerItem *horizontalSpacer;
    QPushButton *addLabel;
    QPushButton *saveLabelsToXML;
    QPushButton *loadLabelsFromXML;
    QListWidget *labelsListWidget;
    QWidget *tab;
    QLabel *label_5;
    QPushButton *computeBGS;
    QSpinBox *bgsIterations;
    QPushButton *loadBGSData;
    QWidget *tab_10;
    QHBoxLayout *horizontalLayout_6;
    QTabWidget *tabWidget_3;
    QWidget *tab_22;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_8;
    QCheckBox *subsamplingCheck;
    QSlider *subsamplingSlider;
    QLabel *subsamplingValue;
    QLabel *subsamplingValuePercentage;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *showFirstFrameButton;
    QToolButton *showPreviousParentFrameButton;
    QToolButton *showPreviousFrameButton;
    QHBoxLayout *horizontalLayout_13;
    QLabel *imageNameLabel;
    QLabel *copyOptionsLabel;
    QComboBox *copyComboBox;
    QPushButton *copyROIsButton;
    QLabel *currentLabelColor;
    QToolButton *showNextFrameButton;
    QToolButton *showNextParentFrameButton;
    QToolButton *showLastFrameButton;
    QCheckBox *copyOnNextCheck;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_8;
    QListWidget *labelsListWidgetTagging;
    QListWidget *roisListWidget;
    QVBoxLayout *verticalLayout_4;
    QWidget *imageArea;
    QTableWidget *roiTable;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QLabel *showingFramesLabel;
    QLabel *totalFramesLabel;
    QLabel *subsamplingStepLabel;
    QGroupBox *groupBox_4;
    QRadioButton *previewFrameCheckTagging;
    QRadioButton *previewBGSCheckTagging;
    QRadioButton *previewFrameAndBGSCheckTagging;
    QGroupBox *groupBox_5;
    QPushButton *eraseAllRois;
    QPushButton *eraseUntilLast;
    QPushButton *eraseCurrent;
    QPushButton *eraseSubsampled;
    QTreeWidget *imageTree;
    QHBoxLayout *horizontalLayout_9;
    QListWidget *subsamplingMonitor;
    QWidget *tab_23;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_2;
    QPushButton *playPreviewButton;
    QLabel *fpsLabel;
    QLabel *showROIsLabel;
    QCheckBox *showROIsCheckbox;
    QCheckBox *showOnlyLabeledROIsCheckbox;
    QLabel *showOnlyLabeledROIsLabel;
    QGroupBox *groupBox_3;
    QRadioButton *previewFrameCheck;
    QRadioButton *previewBGSCheck;
    QRadioButton *previewFrameAndBGSCheck;
    QSpinBox *fpsPreview;
    QVBoxLayout *verticalLayout_3;
    QWidget *previewWidget;
    QProgressBar *playPreviewProgressBar;
    QWidget *tab_3;
    QCheckBox *saveBGSFrameCheckbox;
    QPushButton *saveRoisToDiskButton;
    QPushButton *computeRoiSummary;
    QCheckBox *saveBGSMaskCheckbox;
    QTabWidget *summaryTabWidget;
    QWidget *tab_7;
    QPushButton *loadROIsFromXML;
    QWidget *tab_2;
    QCheckBox *useBGSCheck;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QSpinBox *pixelPadding;
    QLabel *label_7;
    QPushButton *computeDescriptors;

    void setupUi(QWidget *TaggingWidget)
    {
        if (TaggingWidget->objectName().isEmpty())
            TaggingWidget->setObjectName(QString::fromUtf8("TaggingWidget"));
        TaggingWidget->resize(1118, 724);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TaggingWidget->sizePolicy().hasHeightForWidth());
        TaggingWidget->setSizePolicy(sizePolicy);
        verticalLayout_7 = new QVBoxLayout(TaggingWidget);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        globalTabs = new QTabWidget(TaggingWidget);
        globalTabs->setObjectName(QString::fromUtf8("globalTabs"));
        tab_8 = new QWidget();
        tab_8->setObjectName(QString::fromUtf8("tab_8"));
        verticalLayout_11 = new QVBoxLayout(tab_8);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalSpacer_2 = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_11->addItem(verticalSpacer_2);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(tab_8);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(label);

        videoDirPath = new QLineEdit(tab_8);
        videoDirPath->setObjectName(QString::fromUtf8("videoDirPath"));

        horizontalLayout_4->addWidget(videoDirPath);

        selectDir = new QPushButton(tab_8);
        selectDir->setObjectName(QString::fromUtf8("selectDir"));

        horizontalLayout_4->addWidget(selectDir);

        selectVideo = new QPushButton(tab_8);
        selectVideo->setObjectName(QString::fromUtf8("selectVideo"));

        horizontalLayout_4->addWidget(selectVideo);


        verticalLayout_10->addLayout(horizontalLayout_4);

        fileListWidget = new QListWidget(tab_8);
        fileListWidget->setObjectName(QString::fromUtf8("fileListWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(fileListWidget->sizePolicy().hasHeightForWidth());
        fileListWidget->setSizePolicy(sizePolicy2);
        fileListWidget->setMinimumSize(QSize(0, 0));
        fileListWidget->setMaximumSize(QSize(16777215, 150));
        fileListWidget->setBaseSize(QSize(100, 150));
        fileListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        fileListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        fileListWidget->setAutoScroll(true);
        fileListWidget->setAutoScrollMargin(50);
        fileListWidget->setDragEnabled(false);
        fileListWidget->setDragDropMode(QAbstractItemView::DragDrop);
        fileListWidget->setIconSize(QSize(100, 150));
        fileListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
        fileListWidget->setProperty("isWrapping", QVariant(false));
        fileListWidget->setResizeMode(QListView::Fixed);
        fileListWidget->setGridSize(QSize(110, 95));
        fileListWidget->setViewMode(QListView::IconMode);
        fileListWidget->setUniformItemSizes(false);
        fileListWidget->setBatchSize(100);

        verticalLayout_10->addWidget(fileListWidget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer);


        verticalLayout_11->addLayout(verticalLayout_10);

        globalTabs->addTab(tab_8, QString());
        tab_21 = new QWidget();
        tab_21->setObjectName(QString::fromUtf8("tab_21"));
        verticalLayout_5 = new QVBoxLayout(tab_21);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_2 = new QLabel(tab_21);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy3);

        horizontalLayout_10->addWidget(label_2);

        labelToAdd = new QLineEdit(tab_21);
        labelToAdd->setObjectName(QString::fromUtf8("labelToAdd"));
        sizePolicy3.setHeightForWidth(labelToAdd->sizePolicy().hasHeightForWidth());
        labelToAdd->setSizePolicy(sizePolicy3);
        labelToAdd->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_10->addWidget(labelToAdd);

        label_3 = new QLabel(tab_21);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy3.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy3);

        horizontalLayout_10->addWidget(label_3);

        selectLabelColor = new QToolButton(tab_21);
        selectLabelColor->setObjectName(QString::fromUtf8("selectLabelColor"));
        sizePolicy3.setHeightForWidth(selectLabelColor->sizePolicy().hasHeightForWidth());
        selectLabelColor->setSizePolicy(sizePolicy3);
        selectLabelColor->setMaximumSize(QSize(50, 50));

        horizontalLayout_10->addWidget(selectLabelColor);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer);

        addLabel = new QPushButton(tab_21);
        addLabel->setObjectName(QString::fromUtf8("addLabel"));
        sizePolicy3.setHeightForWidth(addLabel->sizePolicy().hasHeightForWidth());
        addLabel->setSizePolicy(sizePolicy3);

        horizontalLayout_10->addWidget(addLabel);

        saveLabelsToXML = new QPushButton(tab_21);
        saveLabelsToXML->setObjectName(QString::fromUtf8("saveLabelsToXML"));
        sizePolicy3.setHeightForWidth(saveLabelsToXML->sizePolicy().hasHeightForWidth());
        saveLabelsToXML->setSizePolicy(sizePolicy3);

        horizontalLayout_10->addWidget(saveLabelsToXML);

        loadLabelsFromXML = new QPushButton(tab_21);
        loadLabelsFromXML->setObjectName(QString::fromUtf8("loadLabelsFromXML"));
        sizePolicy3.setHeightForWidth(loadLabelsFromXML->sizePolicy().hasHeightForWidth());
        loadLabelsFromXML->setSizePolicy(sizePolicy3);

        horizontalLayout_10->addWidget(loadLabelsFromXML);


        verticalLayout_5->addLayout(horizontalLayout_10);

        labelsListWidget = new QListWidget(tab_21);
        labelsListWidget->setObjectName(QString::fromUtf8("labelsListWidget"));
        sizePolicy2.setHeightForWidth(labelsListWidget->sizePolicy().hasHeightForWidth());
        labelsListWidget->setSizePolicy(sizePolicy2);
        labelsListWidget->setMinimumSize(QSize(0, 300));
        labelsListWidget->setMaximumSize(QSize(16777215, 16777215));
        labelsListWidget->setDragEnabled(true);
        labelsListWidget->setDragDropMode(QAbstractItemView::DragDrop);
        labelsListWidget->setIconSize(QSize(50, 50));

        verticalLayout_5->addWidget(labelsListWidget);

        globalTabs->addTab(tab_21, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label_5 = new QLabel(tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(210, 50, 61, 20));
        computeBGS = new QPushButton(tab);
        computeBGS->setObjectName(QString::fromUtf8("computeBGS"));
        computeBGS->setGeometry(QRect(170, 80, 161, 31));
        bgsIterations = new QSpinBox(tab);
        bgsIterations->setObjectName(QString::fromUtf8("bgsIterations"));
        bgsIterations->setGeometry(QRect(280, 50, 42, 22));
        bgsIterations->setMinimum(2);
        bgsIterations->setMaximum(10);
        bgsIterations->setValue(3);
        loadBGSData = new QPushButton(tab);
        loadBGSData->setObjectName(QString::fromUtf8("loadBGSData"));
        loadBGSData->setEnabled(false);
        loadBGSData->setGeometry(QRect(360, 85, 75, 23));
        globalTabs->addTab(tab, QString());
        tab_10 = new QWidget();
        tab_10->setObjectName(QString::fromUtf8("tab_10"));
        horizontalLayout_6 = new QHBoxLayout(tab_10);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        tabWidget_3 = new QTabWidget(tab_10);
        tabWidget_3->setObjectName(QString::fromUtf8("tabWidget_3"));
        tab_22 = new QWidget();
        tab_22->setObjectName(QString::fromUtf8("tab_22"));
        verticalLayout_6 = new QVBoxLayout(tab_22);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        subsamplingCheck = new QCheckBox(tab_22);
        subsamplingCheck->setObjectName(QString::fromUtf8("subsamplingCheck"));

        horizontalLayout_8->addWidget(subsamplingCheck);

        subsamplingSlider = new QSlider(tab_22);
        subsamplingSlider->setObjectName(QString::fromUtf8("subsamplingSlider"));
        subsamplingSlider->setEnabled(false);
        subsamplingSlider->setMaximum(100);
        subsamplingSlider->setValue(100);
        subsamplingSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_8->addWidget(subsamplingSlider);

        subsamplingValue = new QLabel(tab_22);
        subsamplingValue->setObjectName(QString::fromUtf8("subsamplingValue"));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        subsamplingValue->setFont(font);

        horizontalLayout_8->addWidget(subsamplingValue);

        subsamplingValuePercentage = new QLabel(tab_22);
        subsamplingValuePercentage->setObjectName(QString::fromUtf8("subsamplingValuePercentage"));

        horizontalLayout_8->addWidget(subsamplingValuePercentage);


        verticalLayout_6->addLayout(horizontalLayout_8);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        showFirstFrameButton = new QToolButton(tab_22);
        showFirstFrameButton->setObjectName(QString::fromUtf8("showFirstFrameButton"));
        showFirstFrameButton->setEnabled(false);
        showFirstFrameButton->setMinimumSize(QSize(40, 25));
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(true);
        font1.setWeight(75);
        showFirstFrameButton->setFont(font1);

        horizontalLayout_5->addWidget(showFirstFrameButton);

        showPreviousParentFrameButton = new QToolButton(tab_22);
        showPreviousParentFrameButton->setObjectName(QString::fromUtf8("showPreviousParentFrameButton"));
        showPreviousParentFrameButton->setEnabled(false);
        showPreviousParentFrameButton->setMinimumSize(QSize(40, 25));
        showPreviousParentFrameButton->setFont(font1);

        horizontalLayout_5->addWidget(showPreviousParentFrameButton);

        showPreviousFrameButton = new QToolButton(tab_22);
        showPreviousFrameButton->setObjectName(QString::fromUtf8("showPreviousFrameButton"));
        showPreviousFrameButton->setEnabled(false);
        showPreviousFrameButton->setMinimumSize(QSize(40, 25));
        showPreviousFrameButton->setFont(font1);

        horizontalLayout_5->addWidget(showPreviousFrameButton);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        imageNameLabel = new QLabel(tab_22);
        imageNameLabel->setObjectName(QString::fromUtf8("imageNameLabel"));
        sizePolicy3.setHeightForWidth(imageNameLabel->sizePolicy().hasHeightForWidth());
        imageNameLabel->setSizePolicy(sizePolicy3);
        imageNameLabel->setMinimumSize(QSize(80, 10));

        horizontalLayout_13->addWidget(imageNameLabel);

        copyOptionsLabel = new QLabel(tab_22);
        copyOptionsLabel->setObjectName(QString::fromUtf8("copyOptionsLabel"));
        copyOptionsLabel->setEnabled(false);
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(copyOptionsLabel->sizePolicy().hasHeightForWidth());
        copyOptionsLabel->setSizePolicy(sizePolicy4);
        copyOptionsLabel->setMinimumSize(QSize(70, 0));
        copyOptionsLabel->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_13->addWidget(copyOptionsLabel);

        copyComboBox = new QComboBox(tab_22);
        copyComboBox->setObjectName(QString::fromUtf8("copyComboBox"));
        copyComboBox->setEnabled(false);
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(copyComboBox->sizePolicy().hasHeightForWidth());
        copyComboBox->setSizePolicy(sizePolicy5);
        copyComboBox->setMinimumSize(QSize(200, 0));
        copyComboBox->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_13->addWidget(copyComboBox);

        copyROIsButton = new QPushButton(tab_22);
        copyROIsButton->setObjectName(QString::fromUtf8("copyROIsButton"));
        copyROIsButton->setEnabled(false);
        sizePolicy3.setHeightForWidth(copyROIsButton->sizePolicy().hasHeightForWidth());
        copyROIsButton->setSizePolicy(sizePolicy3);
        copyROIsButton->setMinimumSize(QSize(40, 0));
        copyROIsButton->setMaximumSize(QSize(65, 16777215));

        horizontalLayout_13->addWidget(copyROIsButton);

        currentLabelColor = new QLabel(tab_22);
        currentLabelColor->setObjectName(QString::fromUtf8("currentLabelColor"));
        sizePolicy4.setHeightForWidth(currentLabelColor->sizePolicy().hasHeightForWidth());
        currentLabelColor->setSizePolicy(sizePolicy4);
        currentLabelColor->setMinimumSize(QSize(90, 0));
        currentLabelColor->setMaximumSize(QSize(90, 16777215));
        currentLabelColor->setAlignment(Qt::AlignCenter);

        horizontalLayout_13->addWidget(currentLabelColor);


        horizontalLayout_5->addLayout(horizontalLayout_13);

        showNextFrameButton = new QToolButton(tab_22);
        showNextFrameButton->setObjectName(QString::fromUtf8("showNextFrameButton"));
        showNextFrameButton->setEnabled(false);
        showNextFrameButton->setMinimumSize(QSize(40, 25));
        showNextFrameButton->setFont(font1);

        horizontalLayout_5->addWidget(showNextFrameButton);

        showNextParentFrameButton = new QToolButton(tab_22);
        showNextParentFrameButton->setObjectName(QString::fromUtf8("showNextParentFrameButton"));
        showNextParentFrameButton->setEnabled(false);
        showNextParentFrameButton->setMinimumSize(QSize(40, 25));
        showNextParentFrameButton->setFont(font1);

        horizontalLayout_5->addWidget(showNextParentFrameButton);

        showLastFrameButton = new QToolButton(tab_22);
        showLastFrameButton->setObjectName(QString::fromUtf8("showLastFrameButton"));
        showLastFrameButton->setEnabled(false);
        showLastFrameButton->setMinimumSize(QSize(40, 25));
        showLastFrameButton->setFont(font1);

        horizontalLayout_5->addWidget(showLastFrameButton);

        copyOnNextCheck = new QCheckBox(tab_22);
        copyOnNextCheck->setObjectName(QString::fromUtf8("copyOnNextCheck"));

        horizontalLayout_5->addWidget(copyOnNextCheck);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout_6->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        labelsListWidgetTagging = new QListWidget(tab_22);
        labelsListWidgetTagging->setObjectName(QString::fromUtf8("labelsListWidgetTagging"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(labelsListWidgetTagging->sizePolicy().hasHeightForWidth());
        labelsListWidgetTagging->setSizePolicy(sizePolicy6);
        labelsListWidgetTagging->setMinimumSize(QSize(0, 300));
        labelsListWidgetTagging->setMaximumSize(QSize(150, 350));
        labelsListWidgetTagging->setDragEnabled(true);
        labelsListWidgetTagging->setDragDropMode(QAbstractItemView::DragDrop);
        labelsListWidgetTagging->setIconSize(QSize(50, 50));

        verticalLayout_8->addWidget(labelsListWidgetTagging);

        roisListWidget = new QListWidget(tab_22);
        roisListWidget->setObjectName(QString::fromUtf8("roisListWidget"));
        QSizePolicy sizePolicy7(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(roisListWidget->sizePolicy().hasHeightForWidth());
        roisListWidget->setSizePolicy(sizePolicy7);
        roisListWidget->setMaximumSize(QSize(150, 16777215));
        roisListWidget->setViewMode(QListView::IconMode);
        roisListWidget->setSortingEnabled(false);

        verticalLayout_8->addWidget(roisListWidget);


        horizontalLayout_7->addLayout(verticalLayout_8);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        imageArea = new QWidget(tab_22);
        imageArea->setObjectName(QString::fromUtf8("imageArea"));
        sizePolicy2.setHeightForWidth(imageArea->sizePolicy().hasHeightForWidth());
        imageArea->setSizePolicy(sizePolicy2);
        imageArea->setMinimumSize(QSize(0, 0));
        imageArea->setMaximumSize(QSize(16777215, 16777215));
        imageArea->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_4->addWidget(imageArea);

        roiTable = new QTableWidget(tab_22);
        roiTable->setObjectName(QString::fromUtf8("roiTable"));
        QSizePolicy sizePolicy8(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(roiTable->sizePolicy().hasHeightForWidth());
        roiTable->setSizePolicy(sizePolicy8);
        roiTable->setMinimumSize(QSize(0, 150));
        roiTable->setMaximumSize(QSize(16777215, 150));

        verticalLayout_4->addWidget(roiTable);


        horizontalLayout_7->addLayout(verticalLayout_4);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(tab_22);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy3.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy3);
        groupBox->setMinimumSize(QSize(0, 180));
        groupBox->setMaximumSize(QSize(280, 180));
        showingFramesLabel = new QLabel(groupBox);
        showingFramesLabel->setObjectName(QString::fromUtf8("showingFramesLabel"));
        showingFramesLabel->setEnabled(false);
        showingFramesLabel->setGeometry(QRect(11, 33, 201, 20));
        totalFramesLabel = new QLabel(groupBox);
        totalFramesLabel->setObjectName(QString::fromUtf8("totalFramesLabel"));
        totalFramesLabel->setEnabled(false);
        totalFramesLabel->setGeometry(QRect(11, 17, 191, 16));
        subsamplingStepLabel = new QLabel(groupBox);
        subsamplingStepLabel->setObjectName(QString::fromUtf8("subsamplingStepLabel"));
        subsamplingStepLabel->setEnabled(false);
        subsamplingStepLabel->setGeometry(QRect(11, 54, 111, 16));
        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 80, 101, 91));
        groupBox_4->setAlignment(Qt::AlignCenter);
        previewFrameCheckTagging = new QRadioButton(groupBox_4);
        previewFrameCheckTagging->setObjectName(QString::fromUtf8("previewFrameCheckTagging"));
        previewFrameCheckTagging->setGeometry(QRect(10, 21, 71, 17));
        previewFrameCheckTagging->setChecked(true);
        previewBGSCheckTagging = new QRadioButton(groupBox_4);
        previewBGSCheckTagging->setObjectName(QString::fromUtf8("previewBGSCheckTagging"));
        previewBGSCheckTagging->setEnabled(false);
        previewBGSCheckTagging->setGeometry(QRect(10, 40, 41, 17));
        previewBGSCheckTagging->setChecked(false);
        previewFrameAndBGSCheckTagging = new QRadioButton(groupBox_4);
        previewFrameAndBGSCheckTagging->setObjectName(QString::fromUtf8("previewFrameAndBGSCheckTagging"));
        previewFrameAndBGSCheckTagging->setEnabled(false);
        previewFrameAndBGSCheckTagging->setGeometry(QRect(10, 60, 91, 17));
        groupBox_5 = new QGroupBox(groupBox);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(117, 52, 131, 121));
        eraseAllRois = new QPushButton(groupBox_5);
        eraseAllRois->setObjectName(QString::fromUtf8("eraseAllRois"));
        eraseAllRois->setGeometry(QRect(17, 18, 81, 23));
        eraseAllRois->setMinimumSize(QSize(0, 23));
        eraseUntilLast = new QPushButton(groupBox_5);
        eraseUntilLast->setObjectName(QString::fromUtf8("eraseUntilLast"));
        eraseUntilLast->setGeometry(QRect(11, 42, 91, 23));
        eraseCurrent = new QPushButton(groupBox_5);
        eraseCurrent->setObjectName(QString::fromUtf8("eraseCurrent"));
        eraseCurrent->setGeometry(QRect(16, 66, 81, 23));
        eraseSubsampled = new QPushButton(groupBox_5);
        eraseSubsampled->setObjectName(QString::fromUtf8("eraseSubsampled"));
        eraseSubsampled->setGeometry(QRect(4, 92, 121, 23));

        verticalLayout_2->addWidget(groupBox);

        imageTree = new QTreeWidget(tab_22);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        imageTree->setHeaderItem(__qtreewidgetitem);
        imageTree->setObjectName(QString::fromUtf8("imageTree"));
        QSizePolicy sizePolicy9(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(imageTree->sizePolicy().hasHeightForWidth());
        imageTree->setSizePolicy(sizePolicy9);
        imageTree->setMinimumSize(QSize(0, 0));
        imageTree->setMaximumSize(QSize(280, 16777215));
        imageTree->setTextElideMode(Qt::ElideMiddle);
        imageTree->setIndentation(20);
        imageTree->setExpandsOnDoubleClick(false);

        verticalLayout_2->addWidget(imageTree);


        horizontalLayout_7->addLayout(verticalLayout_2);


        verticalLayout_6->addLayout(horizontalLayout_7);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        subsamplingMonitor = new QListWidget(tab_22);
        subsamplingMonitor->setObjectName(QString::fromUtf8("subsamplingMonitor"));
        sizePolicy5.setHeightForWidth(subsamplingMonitor->sizePolicy().hasHeightForWidth());
        subsamplingMonitor->setSizePolicy(sizePolicy5);
        subsamplingMonitor->setMaximumSize(QSize(16777215, 40));
        subsamplingMonitor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        subsamplingMonitor->setIconSize(QSize(2, 33));
        subsamplingMonitor->setTextElideMode(Qt::ElideMiddle);
        subsamplingMonitor->setProperty("isWrapping", QVariant(false));
        subsamplingMonitor->setGridSize(QSize(2, 33));
        subsamplingMonitor->setViewMode(QListView::IconMode);

        horizontalLayout_9->addWidget(subsamplingMonitor);


        verticalLayout_6->addLayout(horizontalLayout_9);

        tabWidget_3->addTab(tab_22, QString());
        tab_23 = new QWidget();
        tab_23->setObjectName(QString::fromUtf8("tab_23"));
        horizontalLayout_3 = new QHBoxLayout(tab_23);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        groupBox_2 = new QGroupBox(tab_23);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(130, 0));
        groupBox_2->setAlignment(Qt::AlignCenter);
        playPreviewButton = new QPushButton(groupBox_2);
        playPreviewButton->setObjectName(QString::fromUtf8("playPreviewButton"));
        playPreviewButton->setEnabled(false);
        playPreviewButton->setGeometry(QRect(33, 47, 41, 23));
        playPreviewButton->setCheckable(true);
        fpsLabel = new QLabel(groupBox_2);
        fpsLabel->setObjectName(QString::fromUtf8("fpsLabel"));
        fpsLabel->setEnabled(false);
        fpsLabel->setGeometry(QRect(44, 117, 21, 16));
        showROIsLabel = new QLabel(groupBox_2);
        showROIsLabel->setObjectName(QString::fromUtf8("showROIsLabel"));
        showROIsLabel->setEnabled(false);
        showROIsLabel->setGeometry(QRect(22, 198, 61, 41));
        QFont font2;
        font2.setPointSize(8);
        showROIsLabel->setFont(font2);
        showROIsLabel->setAlignment(Qt::AlignCenter);
        showROIsLabel->setWordWrap(true);
        showROIsCheckbox = new QCheckBox(groupBox_2);
        showROIsCheckbox->setObjectName(QString::fromUtf8("showROIsCheckbox"));
        showROIsCheckbox->setEnabled(false);
        showROIsCheckbox->setGeometry(QRect(44, 231, 21, 21));
        showOnlyLabeledROIsCheckbox = new QCheckBox(groupBox_2);
        showOnlyLabeledROIsCheckbox->setObjectName(QString::fromUtf8("showOnlyLabeledROIsCheckbox"));
        showOnlyLabeledROIsCheckbox->setEnabled(false);
        showOnlyLabeledROIsCheckbox->setGeometry(QRect(46, 330, 21, 21));
        showOnlyLabeledROIsLabel = new QLabel(groupBox_2);
        showOnlyLabeledROIsLabel->setObjectName(QString::fromUtf8("showOnlyLabeledROIsLabel"));
        showOnlyLabeledROIsLabel->setEnabled(false);
        showOnlyLabeledROIsLabel->setGeometry(QRect(23, 287, 61, 51));
        showOnlyLabeledROIsLabel->setFont(font2);
        showOnlyLabeledROIsLabel->setAlignment(Qt::AlignCenter);
        showOnlyLabeledROIsLabel->setWordWrap(true);
        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 378, 111, 101));
        groupBox_3->setAlignment(Qt::AlignCenter);
        previewFrameCheck = new QRadioButton(groupBox_3);
        previewFrameCheck->setObjectName(QString::fromUtf8("previewFrameCheck"));
        previewFrameCheck->setGeometry(QRect(10, 31, 71, 17));
        previewFrameCheck->setChecked(true);
        previewBGSCheck = new QRadioButton(groupBox_3);
        previewBGSCheck->setObjectName(QString::fromUtf8("previewBGSCheck"));
        previewBGSCheck->setEnabled(false);
        previewBGSCheck->setGeometry(QRect(10, 50, 41, 17));
        previewBGSCheck->setChecked(false);
        previewFrameAndBGSCheck = new QRadioButton(groupBox_3);
        previewFrameAndBGSCheck->setObjectName(QString::fromUtf8("previewFrameAndBGSCheck"));
        previewFrameAndBGSCheck->setEnabled(false);
        previewFrameAndBGSCheck->setGeometry(QRect(10, 70, 91, 17));
        fpsPreview = new QSpinBox(groupBox_2);
        fpsPreview->setObjectName(QString::fromUtf8("fpsPreview"));
        fpsPreview->setEnabled(false);
        fpsPreview->setGeometry(QRect(34, 138, 42, 22));
        fpsPreview->setMinimum(1);
        fpsPreview->setMaximum(100);
        fpsPreview->setValue(20);

        horizontalLayout_3->addWidget(groupBox_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        previewWidget = new QWidget(tab_23);
        previewWidget->setObjectName(QString::fromUtf8("previewWidget"));
        sizePolicy2.setHeightForWidth(previewWidget->sizePolicy().hasHeightForWidth());
        previewWidget->setSizePolicy(sizePolicy2);
        previewWidget->setMinimumSize(QSize(0, 0));

        verticalLayout_3->addWidget(previewWidget);

        playPreviewProgressBar = new QProgressBar(tab_23);
        playPreviewProgressBar->setObjectName(QString::fromUtf8("playPreviewProgressBar"));
        playPreviewProgressBar->setEnabled(false);
        sizePolicy5.setHeightForWidth(playPreviewProgressBar->sizePolicy().hasHeightForWidth());
        playPreviewProgressBar->setSizePolicy(sizePolicy5);
        playPreviewProgressBar->setValue(0);
        playPreviewProgressBar->setAlignment(Qt::AlignCenter);
        playPreviewProgressBar->setTextVisible(false);

        verticalLayout_3->addWidget(playPreviewProgressBar);


        horizontalLayout_3->addLayout(verticalLayout_3);

        tabWidget_3->addTab(tab_23, QString());

        horizontalLayout_6->addWidget(tabWidget_3);

        globalTabs->addTab(tab_10, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        saveBGSFrameCheckbox = new QCheckBox(tab_3);
        saveBGSFrameCheckbox->setObjectName(QString::fromUtf8("saveBGSFrameCheckbox"));
        saveBGSFrameCheckbox->setEnabled(false);
        saveBGSFrameCheckbox->setGeometry(QRect(273, 363, 101, 17));
        saveRoisToDiskButton = new QPushButton(tab_3);
        saveRoisToDiskButton->setObjectName(QString::fromUtf8("saveRoisToDiskButton"));
        saveRoisToDiskButton->setEnabled(false);
        saveRoisToDiskButton->setGeometry(QRect(420, 20, 111, 31));
        computeRoiSummary = new QPushButton(tab_3);
        computeRoiSummary->setObjectName(QString::fromUtf8("computeRoiSummary"));
        computeRoiSummary->setGeometry(QRect(150, 20, 131, 31));
        saveBGSMaskCheckbox = new QCheckBox(tab_3);
        saveBGSMaskCheckbox->setObjectName(QString::fromUtf8("saveBGSMaskCheckbox"));
        saveBGSMaskCheckbox->setEnabled(false);
        saveBGSMaskCheckbox->setGeometry(QRect(152, 364, 101, 17));
        summaryTabWidget = new QTabWidget(tab_3);
        summaryTabWidget->setObjectName(QString::fromUtf8("summaryTabWidget"));
        summaryTabWidget->setEnabled(false);
        summaryTabWidget->setGeometry(QRect(47, 53, 511, 291));
        tab_7 = new QWidget();
        tab_7->setObjectName(QString::fromUtf8("tab_7"));
        summaryTabWidget->addTab(tab_7, QString());
        loadROIsFromXML = new QPushButton(tab_3);
        loadROIsFromXML->setObjectName(QString::fromUtf8("loadROIsFromXML"));
        loadROIsFromXML->setGeometry(QRect(292, 20, 121, 31));
        globalTabs->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        useBGSCheck = new QCheckBox(tab_2);
        useBGSCheck->setObjectName(QString::fromUtf8("useBGSCheck"));
        useBGSCheck->setEnabled(false);
        useBGSCheck->setGeometry(QRect(310, 70, 70, 17));
        layoutWidget = new QWidget(tab_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(161, 21, 111, 22));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);

        pixelPadding = new QSpinBox(layoutWidget);
        pixelPadding->setObjectName(QString::fromUtf8("pixelPadding"));
        pixelPadding->setMaximum(30);
        pixelPadding->setValue(5);

        horizontalLayout_2->addWidget(pixelPadding);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_2->addWidget(label_7);

        computeDescriptors = new QPushButton(tab_2);
        computeDescriptors->setObjectName(QString::fromUtf8("computeDescriptors"));
        computeDescriptors->setGeometry(QRect(150, 60, 141, 41));
        globalTabs->addTab(tab_2, QString());

        verticalLayout_7->addWidget(globalTabs);


        retranslateUi(TaggingWidget);

        globalTabs->setCurrentIndex(0);
        tabWidget_3->setCurrentIndex(0);
        summaryTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TaggingWidget);
    } // setupUi

    void retranslateUi(QWidget *TaggingWidget)
    {
        TaggingWidget->setWindowTitle(QApplication::translate("TaggingWidget", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TaggingWidget", "Path", 0, QApplication::UnicodeUTF8));
        selectDir->setText(QApplication::translate("TaggingWidget", "Load Directory", 0, QApplication::UnicodeUTF8));
        selectVideo->setText(QApplication::translate("TaggingWidget", "Load Video", 0, QApplication::UnicodeUTF8));
        globalTabs->setTabText(globalTabs->indexOf(tab_8), QApplication::translate("TaggingWidget", "Video Source", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("TaggingWidget", "Label Name", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("TaggingWidget", "Label Color", 0, QApplication::UnicodeUTF8));
        selectLabelColor->setText(QApplication::translate("TaggingWidget", "...", 0, QApplication::UnicodeUTF8));
        addLabel->setText(QApplication::translate("TaggingWidget", "Add Label", 0, QApplication::UnicodeUTF8));
        saveLabelsToXML->setText(QApplication::translate("TaggingWidget", "Save Labels To XML", 0, QApplication::UnicodeUTF8));
        loadLabelsFromXML->setText(QApplication::translate("TaggingWidget", "Load Labels From XML", 0, QApplication::UnicodeUTF8));
        globalTabs->setTabText(globalTabs->indexOf(tab_21), QApplication::translate("TaggingWidget", "Labels", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("TaggingWidget", "Iterations", 0, QApplication::UnicodeUTF8));
        computeBGS->setText(QApplication::translate("TaggingWidget", "Generate Background Model", 0, QApplication::UnicodeUTF8));
        loadBGSData->setText(QApplication::translate("TaggingWidget", "Load BGS", 0, QApplication::UnicodeUTF8));
        globalTabs->setTabText(globalTabs->indexOf(tab), QApplication::translate("TaggingWidget", "BGS", 0, QApplication::UnicodeUTF8));
        subsamplingCheck->setText(QApplication::translate("TaggingWidget", "Subsampling", 0, QApplication::UnicodeUTF8));
        subsamplingValue->setText(QApplication::translate("TaggingWidget", "100", 0, QApplication::UnicodeUTF8));
        subsamplingValuePercentage->setText(QApplication::translate("TaggingWidget", "%", 0, QApplication::UnicodeUTF8));
        showFirstFrameButton->setText(QApplication::translate("TaggingWidget", "<<", 0, QApplication::UnicodeUTF8));
        showPreviousParentFrameButton->setText(QApplication::translate("TaggingWidget", "-<", 0, QApplication::UnicodeUTF8));
        showPreviousFrameButton->setText(QApplication::translate("TaggingWidget", "<", 0, QApplication::UnicodeUTF8));
        imageNameLabel->setText(QString());
        copyOptionsLabel->setText(QApplication::translate("TaggingWidget", "Copy Options", 0, QApplication::UnicodeUTF8));
        copyROIsButton->setText(QApplication::translate("TaggingWidget", "Copy ROIs", 0, QApplication::UnicodeUTF8));
        currentLabelColor->setText(QString());
        showNextFrameButton->setText(QApplication::translate("TaggingWidget", ">", 0, QApplication::UnicodeUTF8));
        showNextParentFrameButton->setText(QApplication::translate("TaggingWidget", ">-", 0, QApplication::UnicodeUTF8));
        showLastFrameButton->setText(QApplication::translate("TaggingWidget", ">>", 0, QApplication::UnicodeUTF8));
        copyOnNextCheck->setText(QApplication::translate("TaggingWidget", "Copy on Next", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("TaggingWidget", "Summary", 0, QApplication::UnicodeUTF8));
        showingFramesLabel->setText(QApplication::translate("TaggingWidget", "Showing X frames of N", 0, QApplication::UnicodeUTF8));
        totalFramesLabel->setText(QApplication::translate("TaggingWidget", "Total frames:", 0, QApplication::UnicodeUTF8));
        subsamplingStepLabel->setText(QApplication::translate("TaggingWidget", "Subsampling Step: ", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("TaggingWidget", "Type", 0, QApplication::UnicodeUTF8));
        previewFrameCheckTagging->setText(QApplication::translate("TaggingWidget", "Frame", 0, QApplication::UnicodeUTF8));
        previewBGSCheckTagging->setText(QApplication::translate("TaggingWidget", "BGS", 0, QApplication::UnicodeUTF8));
        previewFrameAndBGSCheckTagging->setText(QApplication::translate("TaggingWidget", "FrameAndBGS", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("TaggingWidget", "Erase ROIs", 0, QApplication::UnicodeUTF8));
        eraseAllRois->setText(QApplication::translate("TaggingWidget", "Erase All", 0, QApplication::UnicodeUTF8));
        eraseUntilLast->setText(QApplication::translate("TaggingWidget", "Erase Until Last", 0, QApplication::UnicodeUTF8));
        eraseCurrent->setText(QApplication::translate("TaggingWidget", "Erase Current", 0, QApplication::UnicodeUTF8));
        eraseSubsampled->setText(QApplication::translate("TaggingWidget", "Erase Until Subsampled", 0, QApplication::UnicodeUTF8));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_22), QApplication::translate("TaggingWidget", "Editor", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("TaggingWidget", "Controls", 0, QApplication::UnicodeUTF8));
        playPreviewButton->setText(QApplication::translate("TaggingWidget", "Play", 0, QApplication::UnicodeUTF8));
        fpsLabel->setText(QApplication::translate("TaggingWidget", "FPS", 0, QApplication::UnicodeUTF8));
        showROIsLabel->setText(QApplication::translate("TaggingWidget", "Show ROIs", 0, QApplication::UnicodeUTF8));
        showROIsCheckbox->setText(QString());
        showOnlyLabeledROIsCheckbox->setText(QString());
        showOnlyLabeledROIsLabel->setText(QApplication::translate("TaggingWidget", "Show only labeled ROIs", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("TaggingWidget", "Type", 0, QApplication::UnicodeUTF8));
        previewFrameCheck->setText(QApplication::translate("TaggingWidget", "Frame", 0, QApplication::UnicodeUTF8));
        previewBGSCheck->setText(QApplication::translate("TaggingWidget", "BGS", 0, QApplication::UnicodeUTF8));
        previewFrameAndBGSCheck->setText(QApplication::translate("TaggingWidget", "FrameAndBGS", 0, QApplication::UnicodeUTF8));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_23), QApplication::translate("TaggingWidget", "Preview", 0, QApplication::UnicodeUTF8));
        globalTabs->setTabText(globalTabs->indexOf(tab_10), QApplication::translate("TaggingWidget", "Tagging", 0, QApplication::UnicodeUTF8));
        saveBGSFrameCheckbox->setText(QApplication::translate("TaggingWidget", "Save BGS&Frame", 0, QApplication::UnicodeUTF8));
        saveRoisToDiskButton->setText(QApplication::translate("TaggingWidget", "Save ROIs to Disk", 0, QApplication::UnicodeUTF8));
        computeRoiSummary->setText(QApplication::translate("TaggingWidget", "Compute ROI Summary", 0, QApplication::UnicodeUTF8));
        saveBGSMaskCheckbox->setText(QApplication::translate("TaggingWidget", "Save BGS Mask", 0, QApplication::UnicodeUTF8));
        summaryTabWidget->setTabText(summaryTabWidget->indexOf(tab_7), QApplication::translate("TaggingWidget", "Labels", 0, QApplication::UnicodeUTF8));
        loadROIsFromXML->setText(QApplication::translate("TaggingWidget", "Load ROIs from XML", 0, QApplication::UnicodeUTF8));
        globalTabs->setTabText(globalTabs->indexOf(tab_3), QApplication::translate("TaggingWidget", "Global Summary", 0, QApplication::UnicodeUTF8));
        useBGSCheck->setText(QApplication::translate("TaggingWidget", "Use BGS", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("TaggingWidget", "Padding", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("TaggingWidget", "px", 0, QApplication::UnicodeUTF8));
        computeDescriptors->setText(QApplication::translate("TaggingWidget", "Compute Descriptors", 0, QApplication::UnicodeUTF8));
        globalTabs->setTabText(globalTabs->indexOf(tab_2), QApplication::translate("TaggingWidget", "Descriptors", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TaggingWidget: public Ui_TaggingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAGGINGWIDGET_H
