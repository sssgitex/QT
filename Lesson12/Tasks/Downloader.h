#pragma once

#include <QObject>
#include <QUrl>

class QNetworkAccessManager;
class QNetworkReply;


class Downloader : public QObject
{
Q_OBJECT

private:
    QNetworkAccessManager* m_pnam;

public:
    Downloader(QObject* pobj = 0);

    void download(const QUrl&);

signals:
    void downloadProgress (qint64, qint64);
    void done (const QUrl&, const QByteArray&);
    void error ();

private slots:
    void slotFinished (QNetworkReply*);
};

