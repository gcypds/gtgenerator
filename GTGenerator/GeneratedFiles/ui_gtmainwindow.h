/********************************************************************************
** Form generated from reading UI file 'gtmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GTMAINWINDOW_H
#define UI_GTMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GTMainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gtStatusWidget;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *gtProjectName_title;
    QFrame *line;
    QLabel *statusValue_frameCount;
    QLabel *statusValue_fps;
    QLabel *statusValue_frameSize;
    QLabel *statusValue_labelCount;
    QLabel *statusValue_bgsState;
    QSpacerItem *horizontalSpacer_2;
    QLabel *statusValue_subsamplingState;
    QSpacerItem *horizontalSpacer;
    QLabel *statusValue_roisDrawnP;
    QLabel *statusValue_fullLabeledP;
    QLabel *statusValue_labeledP;
    QLabel *statusValue_autoLabeledP;
    QLabel *statusValue_descriptorsState;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GTMainWindow)
    {
        if (GTMainWindow->objectName().isEmpty())
            GTMainWindow->setObjectName(QString::fromUtf8("GTMainWindow"));
        GTMainWindow->resize(1292, 806);
        centralwidget = new QWidget(GTMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gtStatusWidget = new QWidget(centralwidget);
        gtStatusWidget->setObjectName(QString::fromUtf8("gtStatusWidget"));
        gtStatusWidget->setGeometry(QRect(10, 10, 1241, 25));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gtStatusWidget->sizePolicy().hasHeightForWidth());
        gtStatusWidget->setSizePolicy(sizePolicy);
        gtStatusWidget->setMinimumSize(QSize(0, 25));
        gtStatusWidget->setMaximumSize(QSize(16777215, 25));
        QFont font;
        font.setPointSize(8);
        gtStatusWidget->setFont(font);
        gtStatusWidget->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(gtStatusWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(5, 0, 5, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout_2->setContentsMargins(-1, 0, -1, -1);
        gtProjectName_title = new QLabel(gtStatusWidget);
        gtProjectName_title->setObjectName(QString::fromUtf8("gtProjectName_title"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gtProjectName_title->sizePolicy().hasHeightForWidth());
        gtProjectName_title->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(gtProjectName_title);

        line = new QFrame(gtStatusWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line);

        statusValue_frameCount = new QLabel(gtStatusWidget);
        statusValue_frameCount->setObjectName(QString::fromUtf8("statusValue_frameCount"));
        sizePolicy1.setHeightForWidth(statusValue_frameCount->sizePolicy().hasHeightForWidth());
        statusValue_frameCount->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(statusValue_frameCount);

        statusValue_fps = new QLabel(gtStatusWidget);
        statusValue_fps->setObjectName(QString::fromUtf8("statusValue_fps"));
        sizePolicy1.setHeightForWidth(statusValue_fps->sizePolicy().hasHeightForWidth());
        statusValue_fps->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(statusValue_fps);

        statusValue_frameSize = new QLabel(gtStatusWidget);
        statusValue_frameSize->setObjectName(QString::fromUtf8("statusValue_frameSize"));
        sizePolicy1.setHeightForWidth(statusValue_frameSize->sizePolicy().hasHeightForWidth());
        statusValue_frameSize->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(statusValue_frameSize);

        statusValue_labelCount = new QLabel(gtStatusWidget);
        statusValue_labelCount->setObjectName(QString::fromUtf8("statusValue_labelCount"));
        sizePolicy1.setHeightForWidth(statusValue_labelCount->sizePolicy().hasHeightForWidth());
        statusValue_labelCount->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(statusValue_labelCount);

        statusValue_bgsState = new QLabel(gtStatusWidget);
        statusValue_bgsState->setObjectName(QString::fromUtf8("statusValue_bgsState"));
        sizePolicy1.setHeightForWidth(statusValue_bgsState->sizePolicy().hasHeightForWidth());
        statusValue_bgsState->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(statusValue_bgsState);

        horizontalSpacer_2 = new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        statusValue_subsamplingState = new QLabel(gtStatusWidget);
        statusValue_subsamplingState->setObjectName(QString::fromUtf8("statusValue_subsamplingState"));
        sizePolicy1.setHeightForWidth(statusValue_subsamplingState->sizePolicy().hasHeightForWidth());
        statusValue_subsamplingState->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(statusValue_subsamplingState);

        horizontalSpacer = new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        statusValue_roisDrawnP = new QLabel(gtStatusWidget);
        statusValue_roisDrawnP->setObjectName(QString::fromUtf8("statusValue_roisDrawnP"));
        sizePolicy1.setHeightForWidth(statusValue_roisDrawnP->sizePolicy().hasHeightForWidth());
        statusValue_roisDrawnP->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(statusValue_roisDrawnP);

        statusValue_fullLabeledP = new QLabel(gtStatusWidget);
        statusValue_fullLabeledP->setObjectName(QString::fromUtf8("statusValue_fullLabeledP"));
        sizePolicy1.setHeightForWidth(statusValue_fullLabeledP->sizePolicy().hasHeightForWidth());
        statusValue_fullLabeledP->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(statusValue_fullLabeledP);

        statusValue_labeledP = new QLabel(gtStatusWidget);
        statusValue_labeledP->setObjectName(QString::fromUtf8("statusValue_labeledP"));
        sizePolicy1.setHeightForWidth(statusValue_labeledP->sizePolicy().hasHeightForWidth());
        statusValue_labeledP->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(statusValue_labeledP);

        statusValue_autoLabeledP = new QLabel(gtStatusWidget);
        statusValue_autoLabeledP->setObjectName(QString::fromUtf8("statusValue_autoLabeledP"));
        sizePolicy1.setHeightForWidth(statusValue_autoLabeledP->sizePolicy().hasHeightForWidth());
        statusValue_autoLabeledP->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(statusValue_autoLabeledP);

        statusValue_descriptorsState = new QLabel(gtStatusWidget);
        statusValue_descriptorsState->setObjectName(QString::fromUtf8("statusValue_descriptorsState"));
        sizePolicy1.setHeightForWidth(statusValue_descriptorsState->sizePolicy().hasHeightForWidth());
        statusValue_descriptorsState->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(statusValue_descriptorsState, 0, Qt::AlignLeft);


        horizontalLayout->addLayout(horizontalLayout_2);

        GTMainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(GTMainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        GTMainWindow->setStatusBar(statusbar);

        retranslateUi(GTMainWindow);

        QMetaObject::connectSlotsByName(GTMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GTMainWindow)
    {
        GTMainWindow->setWindowTitle(QApplication::translate("GTMainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        gtProjectName_title->setText(QApplication::translate("GTMainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">GTProjectName</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        statusValue_frameCount->setText(QApplication::translate("GTMainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">FC:</span> 250</p></body></html>", 0, QApplication::UnicodeUTF8));
        statusValue_fps->setText(QApplication::translate("GTMainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">FPS:</span> 20.5</p></body></html>", 0, QApplication::UnicodeUTF8));
        statusValue_frameSize->setText(QApplication::translate("GTMainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">FS:</span> W X H</p></body></html>", 0, QApplication::UnicodeUTF8));
        statusValue_labelCount->setText(QApplication::translate("GTMainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">LC:</span> 250</p></body></html>", 0, QApplication::UnicodeUTF8));
        statusValue_bgsState->setText(QApplication::translate("GTMainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">BGS: </span>YES, iters =4</p></body></html>", 0, QApplication::UnicodeUTF8));
        statusValue_subsamplingState->setText(QApplication::translate("GTMainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">SUB:</span> ENABLED, 50%, 2</p></body></html>", 0, QApplication::UnicodeUTF8));
        statusValue_roisDrawnP->setText(QApplication::translate("GTMainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">DRAWN:</span> 15%</p></body></html>", 0, QApplication::UnicodeUTF8));
        statusValue_fullLabeledP->setText(QApplication::translate("GTMainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">FULL:</span> 15%</p></body></html>", 0, QApplication::UnicodeUTF8));
        statusValue_labeledP->setText(QApplication::translate("GTMainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">MANUAL:</span> 15%</p></body></html>", 0, QApplication::UnicodeUTF8));
        statusValue_autoLabeledP->setText(QApplication::translate("GTMainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">AUTO:</span> 15%</p></body></html>", 0, QApplication::UnicodeUTF8));
        statusValue_descriptorsState->setText(QApplication::translate("GTMainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">DESC: </span>YES</p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GTMainWindow: public Ui_GTMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GTMAINWINDOW_H
