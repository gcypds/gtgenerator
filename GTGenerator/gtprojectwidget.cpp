#include "gtprojectwidget.h"
#include "ui_gtprojectwidget.h"
#include <QtGui>
#include <QDebug>

GTProjectWidget::GTProjectWidget(int pwidth, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GTProjectWidget)
{
	parentWidth = pwidth;

    ui->setupUi(this);
	
    ui->projectStepListWidget->setViewMode(QListView::IconMode);
	ui->projectStepListWidget->setStyleSheet("QListWidget::item:selected { background-color: #A3A3A3; border-width:1px; color:black;}");
    /*qDebug() << "parent width: " << ui->projectStepListWidget->width() << endl;*/
    qDebug() << "setting iconWidth: " << parentWidth/7 << endl;
    ui->projectStepListWidget->setIconSize(QSize(50, 50));
    ui->projectStepListWidget->setGridSize(QSize(0.99*parentWidth/7, 68));
    //ui->projectStepListWidget->setMovement(QListView::Static);
    //ui->projectStepListWidget->setMaximumWidth(128);
    //ui->projectStepListWidget->setSpacing(12);
	ui->projectStepListWidget->setWrapping(false);
	
    //ui->projectStackedWidget = new QStackedWidget;
    taggingWidget = new TaggingWidget();    
    ui->projectStackedWidget->addWidget(taggingWidget);
	
	//ui->projectStackedWidget->addWidget(new ConfigurationPage());
    //ui->projectStackedWidget->addWidget(new UpdatePage());
	//ui->projectStackedWidget->addWidget(new QueryPage());	

   /* QPushButton *closeButton = new QPushButton(tr("Close"));
*/
    QListWidgetItem *imagesButton = new QListWidgetItem(ui->projectStepListWidget);
    imagesButton->setIcon(QIcon(":/Resources/steplist_images/01_images.png"));
    imagesButton->setText(tr("Images"));
	imagesButton->setTextAlignment(Qt::AlignHCenter | Qt::AlignTop);
    imagesButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *labelsButton = new QListWidgetItem(ui->projectStepListWidget);
    labelsButton->setIcon(QIcon(":/Resources/steplist_images/02_labels.png"));
    labelsButton->setText(tr("Labels"));
    labelsButton->setTextAlignment(Qt::AlignHCenter | Qt::AlignTop);
    labelsButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *subsamplingButton = new QListWidgetItem(ui->projectStepListWidget);
    subsamplingButton->setIcon(QIcon(":/Resources/steplist_images/03_subsampling.png"));
    subsamplingButton->setText(tr("Subsampling"));
    subsamplingButton->setTextAlignment(Qt::AlignHCenter | Qt::AlignTop);
    subsamplingButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *taggingButton = new QListWidgetItem(ui->projectStepListWidget);
    taggingButton->setIcon(QIcon(":/Resources/steplist_images/04_tagging.png"));
    taggingButton->setText(tr("ROI Tagging"));
    taggingButton->setTextAlignment(Qt::AlignHCenter | Qt::AlignTop);
    taggingButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *globalSummaryButton = new QListWidgetItem(ui->projectStepListWidget);
    globalSummaryButton->setIcon(QIcon(":/Resources/steplist_images/05_global.png"));
    globalSummaryButton->setText(tr("Global Summary"));
    globalSummaryButton->setTextAlignment(Qt::AlignHCenter | Qt::AlignTop);
    globalSummaryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *bgsButton = new QListWidgetItem(ui->projectStepListWidget);
    bgsButton->setIcon(QIcon(":/Resources/steplist_images/06_bgs.png"));
    bgsButton->setText(tr("BGS"));
    bgsButton->setTextAlignment(Qt::AlignHCenter | Qt::AlignTop);
    bgsButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *descriptorsButton = new QListWidgetItem(ui->projectStepListWidget);
    descriptorsButton->setIcon(QIcon(":/Resources/steplist_images/07_descriptors.png"));
    descriptorsButton->setText(tr("Descriptors"));
	descriptorsButton->setTextAlignment(Qt::AlignHCenter | Qt::AlignTop);
    descriptorsButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    connect(ui->projectStepListWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));

    ui->projectStepListWidget->setCurrentRow(0);

	//qDebug() << "Created GTProjectWidget" << endl;
    /*connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(ui->projectStepListWidget);
    horizontalLayout->addWidget(ui->projectStackedWidget, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);*/
}

GTProjectWidget::~GTProjectWidget()
{
    delete ui;
}

void GTProjectWidget::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

	qDebug() << "changePage " << current << " " << previous << endl;
	qDebug() << "ui->projectStepListWidget->row(current) " << ui->projectStepListWidget->row(current) << endl;
	qDebug() << "ui->projectStackedWidget->size() " << ui->projectStackedWidget->size() << endl;
	qDebug() << "ui->projectStackedWidget->count() " << ui->projectStackedWidget->count() << endl;
	
    ui->projectStackedWidget->setCurrentIndex(ui->projectStepListWidget->row(current));
}
