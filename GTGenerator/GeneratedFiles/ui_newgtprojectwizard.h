/********************************************************************************
** Form generated from reading UI file 'newgtprojectwizard.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWGTPROJECTWIZARD_H
#define UI_NEWGTPROJECTWIZARD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWizard>
#include <QtGui/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_NewGTProjectWizard
{
public:
    QWizardPage *basicInfo;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QLabel *label;
    QLineEdit *gtProjectName;

    void setupUi(QWizard *NewGTProjectWizard)
    {
        if (NewGTProjectWizard->objectName().isEmpty())
            NewGTProjectWizard->setObjectName(QString::fromUtf8("NewGTProjectWizard"));
        NewGTProjectWizard->setWindowModality(Qt::ApplicationModal);
        NewGTProjectWizard->resize(422, 204);
        NewGTProjectWizard->setModal(true);
        NewGTProjectWizard->setWizardStyle(QWizard::ModernStyle);
        NewGTProjectWizard->setOptions(QWizard::HelpButtonOnRight|QWizard::NoBackButtonOnStartPage);
        basicInfo = new QWizardPage();
        basicInfo->setObjectName(QString::fromUtf8("basicInfo"));
        verticalLayout = new QVBoxLayout(basicInfo);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_2 = new QGroupBox(basicInfo);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setMinimumSize(QSize(0, 100));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(27, 32, 31, 20));
        gtProjectName = new QLineEdit(groupBox_2);
        gtProjectName->setObjectName(QString::fromUtf8("gtProjectName"));
        gtProjectName->setGeometry(QRect(73, 35, 301, 20));

        verticalLayout->addWidget(groupBox_2);

        NewGTProjectWizard->addPage(basicInfo);

        retranslateUi(NewGTProjectWizard);

        QMetaObject::connectSlotsByName(NewGTProjectWizard);
    } // setupUi

    void retranslateUi(QWizard *NewGTProjectWizard)
    {
        NewGTProjectWizard->setWindowTitle(QApplication::translate("NewGTProjectWizard", "Create new GT Project", 0, QApplication::UnicodeUTF8));
        basicInfo->setTitle(QApplication::translate("NewGTProjectWizard", "Create new GT Project", 0, QApplication::UnicodeUTF8));
        basicInfo->setSubTitle(QString());
        groupBox_2->setTitle(QApplication::translate("NewGTProjectWizard", "GT Project Name", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewGTProjectWizard", "Name", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewGTProjectWizard: public Ui_NewGTProjectWizard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWGTPROJECTWIZARD_H
