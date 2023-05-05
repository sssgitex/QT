#include "ThreadFinder.h"

ThreadFinder::ThreadFinder(const QDir& dir, const QStringList& mask, QObject *parent)
    : QThread (parent)
    , m_dir(dir)
    , m_mask(mask)
    , m_work (true)
{

}

void ThreadFinder::run()
{

    emit startedThread();
    //m_result.clear();
    proceed(m_dir);
    //emit foundFiles(m_result);
    emit stopedThread();

}

void ThreadFinder::proceed(const QDir& _dir)
{
    if (!m_work)
        return;

    QStringList _listFiles =
        _dir.entryList(m_mask, QDir::Files);

    QStringList _result;

    foreach (QString _file, _listFiles)
    {
        _result.append(_dir.absoluteFilePath(_file));
    }

    emit foundFiles(_result);

    QStringList _listDir = _dir.entryList(QDir::Dirs);
    foreach (QString _subdir, _listDir)
    {
        if (_subdir == "." || _subdir == "..")
        {
            continue;
        }
        proceed(QDir(_dir.absoluteFilePath(_subdir)));
    }

}
