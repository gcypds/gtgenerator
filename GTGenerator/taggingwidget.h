#ifndef TAGGINGWIDGET_H
#define TAGGINGWIDGET_H

#include <QWidget>
#include <QDir>
#include <QSettings>
#include <QList>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include <QColorDialog>
#include <QProgressDialog>
#include "gtprojectdata.h"
#include "gtenums.h"
#include "gttreeitem.h"
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

	void updateTreeWidget();
	void updateRoiCopyOptions(int index);
	void selectGTProject(QString directory);
	void loadData();
	void saveData();
	void saveThumbnails(const QStringList &files);

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

	void on_playPreviewButton_clicked();

    void playPreview();

    void on_showROIsCheckbox_toggled(bool checked);

    void on_roisListWidget_pressed(const QModelIndex &index);

    void on_labelsListWidget_itemDoubleClicked(QListWidgetItem *item);	

	void on_copyROIsButton_clicked();

	void on_showFirstFrameButton_clicked();

	void on_showPreviousFrameButton_clicked();

	void on_showPreviousParentFrameButton_clicked();

	void on_showNextParentFrameButton_clicked();

	void on_showNextFrameButton_clicked();

	void on_showLastFrameButton_clicked();

	void on_computeRoiSummary_clicked();

	void on_saveRoisToDiskButton_clicked();

	void on_computeBGS_clicked();

	void on_computeDescriptors_clicked();

	void on_saveBGSData_clicked();

	void on_eraseAllRois_clicked();

	void on_labelsListWidgetTagging_itemPressed(QListWidgetItem *item);

	void on_loadBGSData_clicked();

	void on_previewFrameCheckTagging_clicked();

	void on_previewBGSCheckTagging_clicked();

	void on_previewFrameAndBGSCheckTagging_clicked();

	void on_loadROIsFromXML_clicked();

	void on_saveLabelsToXML_clicked();

	void on_loadLabelsFromXML_clicked();

	void addLabel(int id, QString label, QColor color, bool appendToSceneLabels);

	void on_eraseUntilLast_clicked();

	void on_eraseCurrent_clicked();

	void on_eraseSubsampled_clicked();

	void on_insert_roi_button_clicked();

private:
    Ui::TaggingWidget *ui;
	GTProjectData *data;
	DiagramScene *scene;
    DiagramView *view;
    QGraphicsScene *previewScene;
    DiagramView *previewView;    
    QString dirSettingsPath;
    QSettings dirSettings;
    QAction *deleteAction;    
    QColor colorToAdd;
    bool manualColor;
    QColorDialog *colorDialog;
	bool stopPreview;

    void showFiles(const QStringList &files);
	void updateFiles(int index);
    void updateImage(int index);
    void selectItemFromModel(const QAbstractItemModel * model, int row);	
	RoiLabelsStatus getRoiLabelsStatus(int frameId);
	void copyRois(int sourceIndex, QList<int> targetIndexes);
	void copySelfRois(int sourceIndex);
	void generateIndexesList(int start, int size, QList<int> * indexList);	
	void generateParentIndexesList(int start, QList<int> * indexList);
	void generateChildIndexesList(int start, QList<int> * indexList);
	void createLabelSummary();

	QString DEFAULT_DIR_KEY;
	float scalePercentageWidth;
	float scalePercentageHeight;

	double gridWidth;
	int currentPreviewIndex;
	int currentTopLevelItems;
	int subsamplingStep;
	int imagesLength;
	QList<int> subsampledItems;

	QTimer *previewPlayerTimer;
	QTimer *autosaverTimer;
	QFont roiItemFont;

	QList<GTTreeItem*> treeItems;

	QProgressDialog *progressDialog;

	QFileInfo videoFile;	
};

#endif // TAGGINGWIDGET_H
