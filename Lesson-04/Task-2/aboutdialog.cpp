#include <QLocale>
#include <QFile>

#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(const QLocale locale, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    QString aboutFile {""};
    ui->setupUi(this);

    ui->label->setTextFormat(Qt::MarkdownText);
    ui->label->setWordWrap(true);

    /*
    QString lang = QLocale::languageToString(QLocale::system().language());
    auto loc = QLocale::system().language();
    auto ru = (loc == QLocale::Russian);
    auto en = (loc == QLocale::English);*/

    if (locale == QLocale(QLocale::Russian))
        aboutFile = ":/md/about.MD";
    else
        aboutFile = ":/md/about_en.MD";

    QFile mdFile(aboutFile); // Путь к файлу в ресурсах
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
