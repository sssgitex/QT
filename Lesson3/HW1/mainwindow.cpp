#include <QMessageBox>
#include <QFileDialog>
#include <QPushButton>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEdit->document()->setModified(false);
    this->setWindowTitle(tr(APP_NAME));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show_about ()
{
    AboutDialog window;

    window.setModal(true);
    window.exec();
}

void MainWindow::closeEvent (QCloseEvent *event)
{

    if (ui->textEdit->document()->isModified())
    {
        QMessageBox::StandardButton resBtn = QMessageBox::question( this, APP_NAME,
                                                                   tr("Current changes are not saved, are you sure?\n"),
                                                                   QMessageBox::No | QMessageBox::Yes,
                                                                   QMessageBox::No);
        if (resBtn != QMessageBox::Yes)
            event->ignore();
        else
            event->accept();
    }
}

bool MainWindow::on_save(QString& _file_name)
{
    if (_file_name.isEmpty())
        return false;

    QFile file(_file_name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, tr("Error"), tr("Unable to open file for writing"));
        return false;
    }

    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    out.flush();

    if (file.error() != QFile::NoError)
    {
        QMessageBox::critical(this, tr("Error"), tr("File writing error: %1").arg(file.errorString()));
        if (file.isOpen())
            file.close();
        return false;
    }

    if (file.isOpen())
        file.close();

    ui->textEdit->document()->setModified(false);

    return true;
}

bool MainWindow::on_load()
{

    QString newFileName = QFileDialog::getOpenFileName(this, tr("Load File"), "", tr("Текстовые файлы (*.txt);;Все файлы (*.*)"));
    if (newFileName.isEmpty())
        return false;

    QFile file(newFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, tr("Error"), tr("Unable to open file for reading"));
        return false;
    }

    QTextStream in(&file);
    ui->textEdit->setText(in.readAll());
    file.close();

    ui->textEdit->document()->setModified(false);
    fileName = newFileName;

    return true;
}

void MainWindow::on_actionNew_triggered()
{

    if (ui->textEdit->document()->isModified())
    {
        QMessageBox::StandardButton resBtn = QMessageBox::question( this, APP_NAME,
                                                                   tr("Current changes are not saved, are you sure?\n"),
                                                                   QMessageBox::No | QMessageBox::Yes,
                                                                   QMessageBox::No);
        if (resBtn == QMessageBox::Yes)
        {
            fileName = "";
            ui->textEdit->clear();
            ui->textEdit->document()->setModified(false);
        }
    }

}


void MainWindow::on_textEdit_textChanged()
{
    ui->textEdit->document()->setModified();
}


void MainWindow::on_actionLoad_triggered()
{

    if (ui->textEdit->document()->isModified())
    {
        QMessageBox::StandardButton resBtn = QMessageBox::question( this, APP_NAME,
                                                                   tr("Current changes are not saved, are you sure?\n"),
                                                                   QMessageBox::No | QMessageBox::Yes,
                                                                   QMessageBox::No);
        if (resBtn != QMessageBox::Yes)
            return;
    }

    on_load();
}


void MainWindow::on_actionSave_triggered()
{
    QString newFileName;

    if (fileName.isEmpty())
        newFileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Текстовые файлы (*.txt);;Все файлы (*.*)"));
    else
        newFileName = fileName;

    if (on_save(newFileName))
        fileName = newFileName;
}

void MainWindow::on_buttonBox_clicked(QAbstractButton *button)
{
    if (qobject_cast<QPushButton*>(button) == ui->buttonBox->button(QDialogButtonBox::Close))
    {
        close();
    }
    else if  (qobject_cast<QPushButton*>(button) == ui->buttonBox->button(QDialogButtonBox::Help))
    {
        show_about();
    }
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

