#include <QtWidgets>
#include <QPushButton>
#include <QFile>
#include <QTextStream>

#include "Downloader.h"
#include "DownloaderGui.h"


DownloaderGui::DownloaderGui(QWidget* pwgt /*=0*/)
    : QMainWindow(pwgt)
{ 
    m_pdl  = new Downloader(this);

    m_ppb  = new QProgressBar(this);

    m_ptxt = new QLineEdit(this);
    m_ptxt->setFixedHeight(20);

    m_pcmd = new QPushButton(tr("&Go"), this);
    m_pcmd->setFixedHeight(20);

    connect(m_pcmd, &QPushButton::clicked,
            this,   &DownloaderGui::slotGo);

    connect(m_pdl,  &Downloader::downloadProgress,
            this,   &DownloaderGui::slotDownloadProgress);

//  connect(m_pdl,  &Downloader::done,
//          this,   &DownloaderGui::slotDone);

    QGridLayout* pLayout = new QGridLayout();
    pLayout->addWidget(m_ptxt, 0, 0);
    pLayout->addWidget(m_pcmd, 0, 1);
    pLayout->addWidget(m_ppb, 1, 0, 1, 2);

    QWidget *wgt = new QWidget();
    setCentralWidget(wgt);
    wgt->setLayout(pLayout);
}

void DownloaderGui::slotGo()
{
    if (m_ptxt->text().isEmpty())
    {
        QMessageBox::critical(this, "Search query", "The search query is empty!", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    // Создаем поисковый запрос
    QUrl url(m_find);
    QUrlQuery query;
    query.addQueryItem("text", m_ptxt->text());
    url.setQuery(query);

    connect( m_pdl, &Downloader::downloadProgress,
             this,  &DownloaderGui::slotDownloadProgress);

    connect( m_pdl, &Downloader::done,
             this,  &DownloaderGui::slotDone);

    disconnect( m_pdl, &Downloader::done,
                this,  &DownloaderGui::imageDone);

    m_pdl->download(url);
}

void DownloaderGui::slotDownloadProgress(qint64 nReceived, qint64 nTotal)
{
    if (nReceived <= 0)
    {
        qDebug() << "Error! Received: " << nReceived
                 << " Total: " << nTotal;
        slotError();
        return;
    }
    m_ppb->setValue(100 * nReceived / nTotal);
}

void DownloaderGui::slotDone(const QUrl& url, const QByteArray& ba)
{
    Q_UNUSED(url)

    QString _name = m_ptxt->text() + ".html";
    QFile _file(_name);
    if (_file.open(QIODevice::WriteOnly))
    {
        _file.write(ba);
        _file.close();

        parseHtml(_name);
    }
}

bool DownloaderGui::parseHtml(const QString& _name)
{
    QFile file(_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open cash file: " << _name;
        return false;
    }

    QTextStream in(&file);
    QString htmlContent = in.readAll();
    file.close();

    QRegularExpression regex("<img.*?src=\"(.*?)\"");
    QRegularExpressionMatchIterator matchIter = regex.globalMatch(htmlContent);

    QVector<QUrl> imageUrls;

    while (matchIter.hasNext())
    {
        QRegularExpressionMatch match = matchIter.next();
        if (match.hasMatch())
        {
            QString imageUrl = match.captured(1);
            if (!imageUrl.isEmpty() && imageUrls.count() <= 10)
                imageUrls.append(QUrl("https:" + imageUrl));
        }
    }

    if (imageUrls.isEmpty())
    {
        QMessageBox::critical(this, "Download", "Dump file is empty!", QMessageBox::Ok, QMessageBox::Ok);
        return false;
    }

    QMessageBox::information(this, "Pictures",
                             "HTML dump saved: " +
                             QString::number(imageUrls.count()) +
                             " images URLs found.",
                             QMessageBox::Ok, QMessageBox::Ok);

    disconnect( m_pdl, &Downloader::downloadProgress,
                this,  &DownloaderGui::slotDownloadProgress);

    disconnect( m_pdl, &Downloader::done,
               this,   &DownloaderGui::slotDone);

    connect( m_pdl,    &Downloader::done,
               this,   &DownloaderGui::imageDone);


    mutex.lock();

    m_images.clear();
    m_count = imageUrls.count();

    mutex.unlock();

    // Загрузка найденных картинок в коллекцию (в память)
    for (const QUrl& imageUrl : imageUrls)
    {
        //qDebug() << imageUrl;
        m_pdl->download(imageUrl);
    }

    return true;
}

void DownloaderGui::slotError()
{
    QMessageBox::critical(0, 
                          tr("Error"), 
                          tr("An error while download is occured")
                         );
}

void DownloaderGui::imageDone(const QUrl& url, const QByteArray& ba)
{
    Q_UNUSED(url)

    mutex.lock();

    QByteArray* temp = new QByteArray(ba);
    m_images << temp;

    mutex.unlock();

    if (m_count == m_images.count())
        showPics();

}

void DownloaderGui::showPics()
{
    QDialog* dialog = new QDialog;
    QVBoxLayout* layout = new QVBoxLayout(dialog);

    QScrollArea* scrollArea = new QScrollArea;
    QWidget* contentWidget = new QWidget;
    QVBoxLayout* contentLayout = new QVBoxLayout(contentWidget);

    int numImages = m_images.size();

    QGridLayout* gridLayout = new QGridLayout;
    contentLayout->addLayout(gridLayout);

    int numColumns = 3;

    // Ограничиваем количество строк в сетке
    int numRows = (numImages + numColumns - 1) / numColumns;
    numRows = qMin(3, numRows);

    for (int i = 0; i < numImages; ++i) {
        // Создаем QLabel для каждой картинки
        QLabel* label = new QLabel;
        QPixmap pix;
        pix.loadFromData(*m_images[i]);
        pix = pix.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        label->setPixmap(pix);
        label->setFixedSize(pix.size());

        // Определяем координаты ячейки в сетке
        int row = i / numColumns;
        int column = i % numColumns;

        gridLayout->addWidget(label, row, column);
    }

    // Устанавливаем политику прокрутки и контент в области прокрутки
    scrollArea->setWidget(contentWidget);
    scrollArea->setWidgetResizable(true);

    // Добавляем область прокрутки в макет диалога
    layout->addWidget(scrollArea);

    // Устанавливаем размер диалога
    int dialogWidth = numColumns * 150 + scrollArea->verticalScrollBar()->sizeHint().width() + 65;
    int dialogHeight = numRows * 150 + scrollArea->horizontalScrollBar()->sizeHint().height() - 40;
    dialog->setFixedSize(dialogWidth, dialogHeight);

    dialog->setModal(true);

    dialog->exec();
}
