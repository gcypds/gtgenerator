#ifndef NEWGTPROJECTWIZARD_H
#define NEWGTPROJECTWIZARD_H

#include <QWizard>

namespace Ui {
class NewGTProjectWizard;
}

class NewGTProjectWizard : public QWizard
{
    Q_OBJECT

public:
    explicit NewGTProjectWizard(QWidget *parent = 0);
    ~NewGTProjectWizard();

	QString getGTProjectName();
private:
    Ui::NewGTProjectWizard *ui;
};

#endif // NEWGTPROJECTWIZARD_H
