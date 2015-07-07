#ifndef GTPROJECTWIDGET_H
#define GTPROJECTWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include "taggingwidget.h"

namespace Ui {
class GTProjectWidget;
}

class GTProjectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GTProjectWidget(int parentWidth, QWidget *parent = 0);
    ~GTProjectWidget();	

private:
    Ui::GTProjectWidget *ui;
	int parentWidth;

   /* QListWidget * projectStepList;
    QStackedWidget * stackedWidget;*/

    TaggingWidget * taggingWidget;

private slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
};

#endif // GTPROJECTWIDGET_H
