#pragma once

#include <QDialog>
#include <QWidget>
#include <QDir>

#include "ThreadFinder.h"

class QLineEdit;
class QTextEdit;

class FileFinder : public QDialog
{
    Q_OBJECT

private:

    QLineEdit* m_ptxtDir;
    QLineEdit* m_ptxtMask;
    QTextEdit* m_ptxtResult;

    QSharedPointer<ThreadFinder>findThread;

public:
    FileFinder(QDir folder, QWidget* pwgt = nullptr);
    ~FileFinder();
    //FileFinder(QWidget* pwgt = nullptr);

    void start(const QDir& dir);

public slots:
    void slotFind  ();
    void slotBrowse();

    void newSearchStarted(); //
    void deleteThread(); // Удаляем поток при завершение работы
    void getFiles(QStringList); // Получаем найденные файлы
};

