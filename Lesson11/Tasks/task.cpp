#include "task.h"

Task::Task(quint32 id, QString name, QDate deadline, int progress, QObject *parent)
    : QObject(parent)
    , m_id (id)
    , m_name(name)
    , m_deadline(deadline)
    , m_progress(progress)
{
}

int Task::id() const
{
    return m_id;
}

void Task::setId(const int &id)
{
    if (m_id != id)
    {
        m_id = id;
        emit idChanged();
    }
}


QString Task::name() const
{
    return m_name;
}

void Task::setName(const QString &name)
{
    if (m_name != name)
    {
        m_name = name;
        emit nameChanged();
    }
}

QDate Task::deadline() const
{
    return m_deadline;
}

void Task::setDeadline(const QDate &deadline)
{
    if (m_deadline != deadline)
    {
        m_deadline = deadline;
        emit deadlineChanged();
    }
}

int Task::progress() const
{
    return m_progress;
}

void Task::setProgress(int progress)
{
    if (m_progress != progress)
    {
        m_progress = progress;
        emit progressChanged();
    }
}

//QString Task::toString() const
//{
//    return QString("%1,%2,%3").arg(m_name).arg(m_deadline.toString("dd.MM.yyyy")).arg(m_progress);
//}


