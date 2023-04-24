#include <QFile>

#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    ui->label->setTextFormat(Qt::MarkdownText);
    ui->label->setWordWrap(true);

    QFile mdFile(":/md/about.MD"); // Путь к файлу в ресурсах
    if (mdFile.open(QIODevice::ReadOnly | QIODevice::Text))
        ui->label->setText(mdFile.readAll());
    else
        ui->label->setText(tr("error while reading"));

    if (mdFile.isOpen())
        mdFile.close();
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
