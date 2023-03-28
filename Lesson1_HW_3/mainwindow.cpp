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


void MainWindow::on_AddTextButton_clicked()
{
    QString text_1 = ui->FirstTextEdit->toPlainText();
    ui->SecondTextEdit->setPlainText(text_1);
}


void MainWindow::on_SwapButton_clicked()
{
    QString text_2 = ui->SecondTextEdit->toPlainText();
    ui->FirstTextEdit->setPlainText(text_2);
}


void MainWindow::on_AddHTMLButton_clicked()
{

    QTextEdit* text = new QTextEdit;
    text->setHtml("<font color='red'>Hello</font>");
    ui->SecondTextEdit->setPlainText(text->toHtml());

}

