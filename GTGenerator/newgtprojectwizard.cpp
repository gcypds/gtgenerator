#include "newgtprojectwizard.h"
#include "ui_newgtprojectwizard.h"

#include <QDebug>

NewGTProjectWizard::NewGTProjectWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::NewGTProjectWizard)
{
    ui->setupUi(this);
}

NewGTProjectWizard::~NewGTProjectWizard() {
    delete ui;
}

QString NewGTProjectWizard::getGTProjectName() {
	return ui->gtProjectName->text();
}