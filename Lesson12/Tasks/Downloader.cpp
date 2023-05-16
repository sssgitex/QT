#include <QtNetwork>
#include "Downloader.h"


Downloader::Downloader(QObject* pobj/*=0*/) : QObject(pobj)
{ 
    m_pnam = new QNetworkAccessManager(this);
    connect(m_pnam, SIGNAL(finished(QNetworkReply*)), 
            this,   SLOT(slotFinished(QNetworkReply*))
           );
}

void Downloader::download(const QUrl& url)
{
    QNetworkRequest request(url);
    // Отключение HTTP/2
    request.setAttribute(QNetworkRequest::Http2AllowedAttribute, false);

    QNetworkReply*  pnr = m_pnam->get(request);

    QObject::connect( pnr,  &QNetworkReply::downloadProgress,
                      this, &Downloader::downloadProgress );
}

void Downloader::slotFinished(QNetworkReply* pnr)
{
    if (pnr->error() != QNetworkReply::NoError)
    {
        qDebug() << "error:" << pnr->error();
        emit error();

    }
    else
    {
        emit done(pnr->url(), pnr->readAll());
    }
    pnr->deleteLater();
}
