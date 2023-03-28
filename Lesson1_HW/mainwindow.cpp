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


void MainWindow::on_AnswerButton_clicked()
{
    ui->AnswerLine->clear();
    long a = 0, b = 0, c = 0, D = 0 , status = 0;
    a = ui->A_Line->text().toLong();
    b = ui->B_Line->text().toLong();
    c = ui->C_Line->text().toLong();
    if (a == 0 && b == 0 && c == 0)
    {
        ui->AnswerLine->setText("Введите данные!");
        status = 1;
    }
    if (a == 0 && status == 0)
    {
        c = ~c + 1;
        ui->AnswerLine->setText("x = ");
        ui->AnswerLine->setText(ui->AnswerLine->text() + QString::number(c / b));
    }
    if (qFabs(a) > 0 && qFabs(b) >= 0 && qFabs(c) >= 0)
    {
        D = qPow(b, 2) - (4*a*c);
        if (D < 0)
            ui->AnswerLine->setText("Нет корней");
        if (D == 0)
        {
            ui->AnswerLine->setText("x = ");
            ui->AnswerLine->setText(ui->AnswerLine->text() + QString::number(-(b / 2*a)));
        }
        if (D > 0)
        {
            ui->AnswerLine->setText("x1 = ");
            ui->AnswerLine->setText(ui->AnswerLine->text() + QString::number((-b+qSqrt(D))/(2*a)));
            ui->AnswerLine->setText(ui->AnswerLine->text() + " x2 = ");
            ui->AnswerLine->setText(ui->AnswerLine->text() + QString::number((-b-qSqrt(D))/(2*a)));
        }
    }
}

