
#include "mainwidget.h"
#include "FileFinder.h"
#include "ui_mainwidget.h"

#include <QThread>
#include <QDesktopServices>
#include <QUrl>


MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setWindowTitle (APP_NAME);

    // Привязка обработчиков событий
    connect(ui->btnLevelUp,   &QPushButton::clicked, this, &MainWidget::on_levelUp);
    connect(ui->btnListView,  &QPushButton::clicked, this, &MainWidget::on_listView);
    connect(ui->btnIconsView, &QPushButton::clicked, this, &MainWidget::on_iconsView);
    connect(ui->listView,     &QAbstractItemView::doubleClicked, this, &MainWidget::on_doIt);

    connect(ui->btnFindFiles, &QPushButton::clicked, this, &MainWidget::on_findFiles);

    this->aDirList = new QFileInfoList();
    this->model    = new QListViewExplorerModel();
    this->currentFolder = QDir(QDir::currentPath());
    this->model->getFolderList(this->currentFolder.absolutePath(),this->aDirList);

    this->ui->listView->setModel(model);
    this->ui->lineEdit->setText(QDir::currentPath());
    this->ui->listView->setWordWrap(true);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_doIt(const QModelIndex &index)
{
    if (this->aDirList->at(index.row()).isDir())
    {
        QString tmp = this->aDirList->at(index.row()).absoluteFilePath();
        model->getFolderList(this->aDirList->at(index.row()).absoluteFilePath(),this->aDirList);
        this->ui->lineEdit->setText(tmp);
    }
    else
    {
        QDesktopServices::openUrl(QUrl(this->aDirList->at(index.row()).absoluteFilePath()));
    }
}

void MainWidget::on_levelUp()
{
    currentFolder.cdUp();

    this->ui->lineEdit->setText(currentFolder.absolutePath());
    model->getFolderList(currentFolder.absolutePath(),this->aDirList);
}

void MainWidget::on_listView()
{
    this->ui->listView->setUniformItemSizes(false);
    this->ui->listView->setViewMode(QListView::ListMode);
}

void MainWidget::on_iconsView()
{
    this->ui->listView->setUniformItemSizes(true);
    this->ui->listView->setViewMode(QListView::IconMode);
}

void MainWidget::on_findFiles()
{

    FileFinder fileFinder(this->currentFolder, this);
//    FileFinder fileFinder(this);

    fileFinder.resize(370, 240);
    fileFinder.exec();

}






