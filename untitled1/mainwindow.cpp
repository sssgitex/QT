#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_AnsweButton_clicked()
{
    int x = ui->GetLine->text().toInt();
    int base = 2;
    if (ui->BinaryButton->isChecked()) base = 2;

    if (ui->OctalButton->isChecked())base = 8;

    if (ui->HexButton->isChecked()) base = 16;

    QString answer = QString::number(x, base);
    ui->AnswerLine->setText(answer);
}

