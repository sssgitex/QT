#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "speccharclass.h"

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


void MainWindow::on_plainTextEdit_textChanged()
{
//    SpecCharClass sc;

//    qint32 pos = 0;
//    while(1)
//    {
//        QString text = ui->plainTextEdit->toPlainText();
//        qint32 fnd = text.indexOf("#@", pos);
//        if (fnd == -1) return;
//        pos = fnd;
//        fnd = text.indexOf("@", pos+2);
//        if (pos-fnd > 1)
//        {
//            sc.replace(text);
//        }
//}
}


void MainWindow::on_pushButton_clicked()
{
    SpecCharClass sc;
    QString text = sc.replace(ui->plainTextEdit->toPlainText());
    ui->plainTextEdit->clear();
    ui->plainTextEdit->setPlainText(text);
}

