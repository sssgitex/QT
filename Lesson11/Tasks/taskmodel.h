
#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include "task.h"

class TaskModel : public QAbstractListModel
{
    Q_OBJECT

public:

    enum TaskRoles
    {
        IdRole = Qt::UserRole + 1,
        NameRole,
        DeadlineRole,
        ProgressRole
    };

    explicit TaskModel(QObject *parent = nullptr);

    Q_INVOKABLE void addTask(int id, QString name, QDate deadline, int progress);
    Q_INVOKABLE void removeTask(int index);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QHash<int, QByteArray> roleNames() const override;

public:

    Q_INVOKABLE bool saveAllTasks ();
    Q_INVOKABLE bool dirty() const;
    void setDirty(bool);

private:

    bool loadAllTasks ();

    QList<Task*> m_tasks;
    bool isDirty; // Has the m_tasks got unsaved changes?

signals:

    void listLoaded(bool result);
    void listSaved(bool result);

    void taskAdded(int index);
    void taskChanged(int index);
    void taskRemoved(int index);
};

#endif // TASKMODEL_H
