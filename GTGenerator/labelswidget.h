#ifndef TAGGINGWIDGET_H
#define TAGGINGWIDGET_H

#include <QWidget>
#include <QDir>
#include <QSettings>
#include <QList>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include <QColorDialog>
#include "diagramitem.h"
#include "diagramscene.h"
#include "diagramview.h"

namespace Ui {
class TaggingWidget;
}

class TaggingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TaggingWidget(QWidget *parent = 0);
    ~TaggingWidget();

	private slots:
    void on_selectVideo_clicked();

    void on_selectDir_clicked();   

    void on_fileListWidget_itemDoubleClicked(QListWidgetItem *item);

    bool eventFilter(QObject *object, QEvent *event);

    void on_labelsListWidget_itemPressed(QListWidgetItem *item);

    void deleteItem();

    void on_roiTable_itemPressed(QTableWidgetItem *item);

    void on_roiTable_pressed(const QModelIndex &index);

    void handleSelectionChanged(const QItemSelection &selection);

    void sceneSelectionChanged();

    void on_addLabel_clicked();

    void on_selectLabelColor_clicked();   

    void on_subsamplingCheck_toggled(bool checked);

    void on_subsamplingSlider_valueChanged(int value);

    void on_subsamplingUpdateButton_clicked();

    void on_imageTree_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_subsamplingSlider_sliderMoved(int position);

    void on_subsamplingSlider_sliderReleased();

    void on_subsamplingMonitor_itemDoubleClicked(QListWidgetItem *item);

    void on_playPreviewButton_toggled(bool checked);

    void playPreview();

    void on_showROIsCheckbox_toggled(bool checked);

    void on_roisListWidget_pressed(const QModelIndex &index);

    void on_labelsListWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::TaggingWidget *ui;
	DiagramScene *scene;
    DiagramView *view;
    QGraphicsScene *previewScene;
    QGraphicsView *previewView;
    QDir currentDir;
    QString dirSettingsPath; // Will be using application informations for correct location of your settings
    QSettings dirSettings;
    QAction *deleteAction;    
    QColor colorToAdd;
    bool manualColor;
    QColorDialog *colorDialog;

    void showFiles(const QStringList &files);
    void updateImage(int index);
    void selectItemFromModel(const QAbstractItemModel * model, int row);

};

#endif // TAGGINGWIDGET_H
