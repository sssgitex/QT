
#ifndef THREADFINDER_H
#define THREADFINDER_H

#include <QThread>
#include <QObject>

#include <QDir>


class ThreadFinder: public QThread
{

    Q_OBJECT

public:

    ThreadFinder(const QDir& dir, const QStringList& mask, QObject *parent = nullptr);

    void findStop() // Прекращение работы потока
    {
        m_work = false;
    };

protected:

    void run() override;

private:

    void proceed(const QDir&);

    QDir m_dir;
    QStringList m_mask;
    //QStringList m_result;

    bool m_work; // Завершение потока извне

signals:

    void startedThread(); // Сигнал старта поиска
    void foundFiles(QStringList); // Сообщение о найденных файлах
    void stopedThread(); // Сигнал завершения поиска

};

#endif // THREADFINDER_H
