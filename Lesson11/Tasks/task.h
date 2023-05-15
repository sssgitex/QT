#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QString>
#include <QDate>

class Task : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(quint32 id READ id WRITE setId NOTIFY idChanged)
//    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
//    Q_PROPERTY(QDate deadline READ deadline WRITE setDeadline NOTIFY deadlineChanged)
//    Q_PROPERTY(int progress READ progress WRITE setProgress NOTIFY progressChanged)

public:

    Task(quint32 id, QString name, QDate deadline, int progress, QObject *parent = nullptr);
    Task() = delete;
    Task(const Task&) = delete;

    int id() const;
    void setId(const int &id);

    QString name() const;
    void setName(const QString &name);

    QDate deadline() const;
    void setDeadline(const QDate &deadline);

    int progress() const;
    void setProgress(int progress);
//    QString toString() const;

signals:

    void idChanged();
    void nameChanged();
    void deadlineChanged();
    void progressChanged();

private:
    int     m_id;
    QString m_name;
    QDate   m_deadline;
    int     m_progress;
};

#endif // TASK_H
