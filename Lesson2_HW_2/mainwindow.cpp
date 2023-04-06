#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    model = new QStandardItemModel(this);
    ui->listView->setModel(model);

    auto *item1 = new QStandardItem(QIcon("/C++.png"),"С++");
    item1->setFlags(item1->flags() | Qt::ItemIsEditable);
    model->appendRow(item1);

    auto *item2 = new QStandardItem(QIcon("/C#_100.png"),"C#");
    item2->setFlags(item2->flags() | Qt::ItemIsEditable);
    model->appendRow(item2);

    auto *item3 = new QStandardItem(QIcon("/java_100.png"),"java");
    item3->setFlags(item3->flags() | Qt::ItemIsEditable);
    model->appendRow(item3);

    auto *item4 = new QStandardItem(QIcon("/python_100.png"),"python");
    item4->setFlags(item4->flags() | Qt::ItemIsEditable);
    model->appendRow(item4);

    ui->listView->setEditTriggers(QAbstractItemView::EditTrigger::DoubleClicked);

    ui->listView->setCurrentIndex(model->indexFromItem(item1));
    ui->listView->setFocus();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ButtonDel_clicked()
{
    int row_idx = ui->listView->currentIndex().row();
    if (row_idx >= 0 && row_idx < model->rowCount())
        model->removeRow(row_idx);
}


void MainWindow::on_ButtonDown_clicked()
{
    if (model->rowCount() < 2)
        return;

    int row1_idx = ui->listView->currentIndex().row();

    // Последняя строка
    if (row1_idx == model->rowCount() - 1)
        return;

    int row2_idx = row1_idx + 1;

    // Запомнить фокус
    //auto sel_txt = model->item(row1_idx, 0)->text();

    // Удаление элементов из модели [row2 > row1]
    QList<QStandardItem*> row2 = model->takeRow(row2_idx);
    QList<QStandardItem*> row1 = model->takeRow(row1_idx);

    // Перемещение элементов в нужный порядок
    model->insertRow(row1_idx, row2);
    model->insertRow(row2_idx, row1);

    // Восстановить фокус
    //auto founds = model->findItems(sel_txt, Qt::MatchExactly);
    //ui->listView->setCurrentIndex(model->indexFromItem(founds.first()));

    QModelIndex index = model->index(row2_idx, 0);
    ui->listView->setCurrentIndex(index);
}


void MainWindow::on_ButtonUp_clicked()
{
    if (model->rowCount() < 2)
        return;

    int row1_idx = ui->listView->currentIndex().row();

    // Первая строка
    if (!row1_idx)
        return;

    int row2_idx = row1_idx - 1;

    // Запомнить фокус
    //auto sel_txt = model->item(row1_idx, 0)->text();

    // Удаление элементов из модели  [row2 < row1]
    QList<QStandardItem*> row1 = model->takeRow(row1_idx);
    QList<QStandardItem*> row2 = model->takeRow(row2_idx);

    // Перемещение элементов в нужный порядок
    model->insertRow(row2_idx, row1);
    model->insertRow(row1_idx, row2);

    // Восстановить фокус
    //auto founds = model->findItems(sel_txt, Qt::MatchExactly);
    //ui->listView->setCurrentIndex(model->indexFromItem(founds.first()));

    QModelIndex index = model->index(row2_idx, 0);
    ui->listView->setCurrentIndex(index);
}


void MainWindow::on_ButtonAdd_clicked()
{
    auto *item = new QStandardItem(QIcon("./img/default.png"),"new language");
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    model->appendRow(item);

    int lastRow = model->rowCount() - 1;
    QModelIndex index = model->index(lastRow, 0);

    ui->listView->setCurrentIndex(index);
}


void MainWindow::on_IconsCheck_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
    {
        ui->listView->setViewMode(QListView::IconMode);
        ui->listView->setIconSize(QSize(32, 32));
    }
    else
    {
        ui->listView->setViewMode(QListView::ListMode);
        ui->listView->setIconSize(QSize(-1, -1));
    }
}

