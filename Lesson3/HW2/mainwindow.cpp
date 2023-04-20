#include <QUrl>
#include <QNetworkRequest>
#include <QRegularExpression>

#include <QMessageBox>
#include <QDebug>
#include <QVariant>
//#include <QRegExp>

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(tr(APP_NAME));
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    connect(ui->buttonBox->button(QDialogButtonBox::Ok),
            &QPushButton::clicked, &QCoreApplication::quit);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete networkManager;
}

void MainWindow::parseHtml(QByteArray& _data)
{
    ui->lblCurrency->setText("Курсы валют -> ");
    QString strTmp{""}, strOut{"not found"};

    qsizetype idx = _data.indexOf(QString{"currency:item:usd"}.toUtf8());
    if (idx != -1)
    {
        strTmp = _data.mid(idx, 100);
        idx    = strTmp.indexOf(QString{"data-value="}.toUtf8());
        if (idx != -1)
        {
            strTmp = strTmp.mid (idx + 12, 8);
            idx    = strTmp.indexOf('\"');
            if (idx != -1)
            {
                strTmp = strTmp.left(idx);
                strOut = strTmp;
            }
        }
    }
    ui->lblCurrency->setText(ui->lblCurrency->text() + "USD: " + strOut);


    strOut = "not found";
    static QRegularExpression reEuro("id=\"currency:item:eur\".*?data-value=\"(\\d+\\.\\d+)\"");
    QRegularExpressionMatch match = reEuro.match(QString::fromUtf8(_data));

    if (match.hasMatch())
    {

        strOut = match.captured(1);


    }
    ui->lblCurrency->setText(ui->lblCurrency->text() + " | EUR: " + strOut);

    ui->lblWeather->setText("Погода -> ");

    strOut = "not found";
    static QRegularExpression reCity("<a[^>]*class=\"regional-info__cityselection__link\"[^>]*>.*?<span[^>]*class=\"regional-info__cityselection__link__text\"[^>]*>(.*?)</span></a>");
    match  = reCity.match(QString::fromUtf8(_data));
    if (match.hasMatch())
    {
        strOut = match.captured(1);
    }
    ui->lblWeather->setText(ui->lblWeather->text() + strOut);


    strOut = "not found";
    static QRegularExpression reWeather("<a id=\"weather:link\" class=\"weather clearfix\"[^>]+title=\"([^\"]+)\"");
    match  = reWeather.match(_data);
    if (match.hasMatch())
    {
        strOut = match.captured(1);
        ui->lblWeather->setText(ui->lblWeather->text() + " | " + strOut);
    }



    strOut = "not found";
    static QRegularExpression reTemp("id=\"weather:item:now_temp\".*data-value=\"([-+]?\\d+)\"");
    match  = reTemp.match(QString(_data));

    if (match.hasMatch())
    {
        strOut = match.captured(1);
        ui->lblWeather->setText(ui->lblWeather->text() + " | " + strOut);
    }

    QMessageBox::information(this, tr(APP_NAME), tr(QString("information updated...").toStdString().c_str()));

}


void MainWindow::replyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray dataToWrite = (QByteArray)reply->readAll();

        parseHtml(dataToWrite);
    }
    else
    {
        qDebug() << "Error: " << reply->errorString();
    }

    reply->deleteLater();
}


void MainWindow::on_btnGet_pressed()
{
    QUrl url("https://mail.ru/");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));

    networkManager->get(request);
}

