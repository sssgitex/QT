#include <QtWidgets>
#include <QGridLayout>
#include <QMessageBox>

#include "FileFinder.h"

FileFinder::FileFinder(QDir folder, QWidget* pwgt/*= 0*/) : QDialog(pwgt)// QWidget(pwgt)
//FileFinder::FileFinder(QWidget* pwgt/*= 0*/) : QWidget(pwgt)
{
    setWindowTitle ("File finder");

    //m_ptxtDir    = new QLineEdit(QDir::current().absolutePath());
    m_ptxtDir    = new QLineEdit(folder.absolutePath());
    m_ptxtMask   = new QLineEdit("*.cpp *.h");
    m_ptxtResult = new QTextEdit;

    QLabel*      plblDir  = new QLabel("&Directory");
    QLabel*      plblMask = new QLabel("&Mask");
    QPushButton* pcmdDir  = new QPushButton(QPixmap(":/img/folder.png"), "");
    QPushButton* pcmdFind = new QPushButton("&Find");

    connect(pcmdDir, SIGNAL(clicked()), SLOT(slotBrowse()));
    connect(pcmdFind, SIGNAL(clicked()), SLOT(slotFind()));

    plblDir->setBuddy(m_ptxtDir);
    plblMask->setBuddy(m_ptxtMask);

    //Layout setup
    QGridLayout* pgrdLayout = new QGridLayout;
    //pgrdLayout->setMargin(5);
    pgrdLayout->setSpacing(15);
    pgrdLayout->addWidget(plblDir, 0, 0);
    pgrdLayout->addWidget(plblMask, 1, 0);
    pgrdLayout->addWidget(m_ptxtDir, 0, 1);
    pgrdLayout->addWidget(m_ptxtMask, 1, 1);
    pgrdLayout->addWidget(pcmdDir, 0, 2);
    pgrdLayout->addWidget(pcmdFind, 1, 2);
    pgrdLayout->addWidget(m_ptxtResult, 2, 0, 1, 3);
    setLayout(pgrdLayout);

}

FileFinder::~FileFinder()
{
    // При завершении нужно остановить поток
    if (findThread) // != nullptr)
    {
        // Проверяем, работает ли поток
        if (findThread->isRunning())
        {
            // Меняем флаг для завершения ThreadFinder::proceed()
            findThread->findStop();
            // Ожидаем завершения потока
            findThread->terminate();
        }
        // Сбрасываем поток, вызывая деструктор
        findThread.reset();
    }
}

// ----------------------------------------------------------------------
void FileFinder::slotBrowse()
{
    QString str = QFileDialog::getExistingDirectory(0, 
                                                    "Select a Directory", 
                                                    m_ptxtDir->text()
                                                   );

    if (!str.isEmpty()) {
        m_ptxtDir->setText(str);
    }
}

// ----------------------------------------------------------------------
void FileFinder::slotFind()
{
    start(QDir(m_ptxtDir->text()));
}

// ----------------------------------------------------------------------
void FileFinder::start(const QDir& dir)
{
    QApplication::processEvents();

    if (findThread.get())
    {
        findThread->findStop();
        findThread->terminate();
        findThread.reset();
        return;
    }

    //m_ptxtResult->clear();

    QStringList mask = m_ptxtMask->text().split(" ");
    findThread = QSharedPointer<ThreadFinder>::create(dir, mask, this);
    findThread->start(QThread::NormalPriority);

    connect(findThread.get(), SIGNAL(startedThread()),
            this, SLOT(newSearchStarted()));

    connect(findThread.get(), SIGNAL(stopedThread()),
            this, SLOT(deleteThread()));



    connect(findThread.get(), SIGNAL(foundFiles(QStringList)),
            this, SLOT(getFiles(QStringList)));

}

void FileFinder::newSearchStarted()
{
    m_ptxtResult->clear();
}

void FileFinder::deleteThread()
{
    findThread.reset();
    //QMessageBox::information(this, "File search", "File search completed...", QMessageBox::Ok, QMessageBox::Information);
    QMessageBox* msgBox = new QMessageBox (
        QMessageBox::Icon::Information,
        "File search",
        "File search completed...",
        QMessageBox::StandardButton::Ok,
        this);
    msgBox->exec();
    delete msgBox;

}

void FileFinder::getFiles(QStringList listFiles)
{
    //m_ptxtResult->clear();

    foreach (QString file, listFiles)
    {
        m_ptxtResult->append(file);
    }

}
