#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QUrl>
#include <QMutex>

class Downloader;
class QProgressBar;
class QLineEdit;
class QPushButton;

class DownloaderGui : public QMainWindow
{
    Q_OBJECT

private:

    const QString m_find{"https://yandex.ru/images/search"};
    Downloader*   m_pdl;
    QProgressBar* m_ppb;
    QLineEdit*    m_ptxt;
    QPushButton*  m_pcmd;

    QMutex mutex;
    QVector<QByteArray*> m_images;
    uint m_count;

    bool parseHtml(const QString&);

public:

    DownloaderGui(QWidget* pwgt = 0);

private slots:

    void slotGo ();
    void slotError ();
    void slotDownloadProgress (qint64, qint64);
    void slotDone (const QUrl& , const QByteArray& );
    void imageDone (const QUrl& , const QByteArray& );
    void showPics();
};

