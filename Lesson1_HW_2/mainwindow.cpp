#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmath.h"

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


void MainWindow::on_pushButton_clicked()
{

}


void MainWindow::on_AnswerButton_clicked()
{
    float b = ui->B_Line->text().toFloat();
    float c = ui->C_Line->text().toFloat();
    float angle = ui->AngleLine->text().toFloat();
    if (b != 0 && c != 0 && angle != 0)
    {
        if (ui->DegreeButton->isChecked())
        {

           ui->AnswerLine->setText(QString::number(qSqrt(qPow(b, 2) + qPow(c, 2) - 2*b*c * qCos((angle*3.14) / 180))));
        }

        if (ui->RadianButton->isChecked())
        {
            ui->AnswerLine->setText(QString::number(qSqrt(qPow(b, 2) + qPow(c, 2) - 2*b*c * qCos(angle))));
        }
    }

}

