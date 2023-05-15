#include "taskmodel.h"
#include "dbhelper.h"

#include <QSqlRecord>
#include <QFile>

TaskModel::TaskModel(QObject *parent)
    : QAbstractListModel(parent)
    , isDirty (false)
{
    connect(this, &TaskModel::listLoaded,  this, [=]() { setDirty(false); });
    connect(this, &TaskModel::listSaved,   this, [=]() { setDirty(false); });
    connect(this, &TaskModel::taskAdded,   this, [=]() { setDirty(true);  });
    connect(this, &TaskModel::taskChanged, this, [=]() { setDirty(true);  });
    connect(this, &TaskModel::taskRemoved, this, [=]() { setDirty(true);  });

    loadAllTasks();

    //addTask(QStringLiteral("Wash the car"), QDate::currentDate().addDays(7), 1);
    //addTask(QStringLiteral("Cleaning"), QDate::currentDate().addDays(7), 5);
}

void TaskModel::addTask(int id, QString name, QDate deadline, int progress)
{
    int count = this->rowCount();
    beginInsertRows(QModelIndex(), count, count);
    m_tasks.append(new Task(id, name, deadline, progress, this));
    endInsertRows();

    emit taskAdded(m_tasks.size() - 1);
}

int TaskModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_tasks.size();
}

QVariant TaskModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    Task* task = m_tasks.at(index.row());

    switch (role)
    {
        case IdRole:
            return QVariant(task->id());
        case NameRole:
            return QVariant(task->name());
        case DeadlineRole:
            return QVariant(task->deadline());
        case ProgressRole:
            return QVariant(task->progress());
    }

    return QVariant();
}

bool TaskModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
    {
        return false;
    }

    bool changed = false;
    Task *task   = m_tasks.at(index.row());

    switch (role)
    {
        case IdRole:
        {
            auto newValue = value.toInt();
            if (newValue != task->id())
            {
                task->setId (newValue);
                changed = true;
            }
            break;
        }

        case NameRole:
        {
            auto newValue = value.toString();
            if (newValue != task->name())
            {
                task->setName (value.toString());
                changed = true;
            }
            break;
        }

        case DeadlineRole:
        {
            auto newValue = value.toDate();
            if (newValue != task->deadline())
            {
                task->setDeadline (newValue);
                changed = true;
            }
            break;
        }

        case ProgressRole:
        {
            auto newValue = value.toInt();
            if (newValue != task->progress())
            {
                task->setProgress (newValue);
                changed = true;
            }
            break;
        }

    }

    // check whether data has changed
    if (changed)
    {
        emit dataChanged(index, index, QVector<int>() << role);
        emit taskChanged(index.row());
        return true;
    }

    return false;
}

Qt::ItemFlags TaskModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        //return Qt::NoItemFlags;
        return Qt::ItemIsEnabled;

    //return Qt::ItemIsEditable;
    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

QHash<int, QByteArray> TaskModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole]       = "id";
    roles[NameRole]     = "name";
    roles[DeadlineRole] = "deadline";
    roles[ProgressRole] = "progress";

    return roles;
}

void TaskModel::removeTask(int index)
{
    if (index >= 0 && index < m_tasks.size())
    {
        beginRemoveRows(QModelIndex(), index, index);
        delete m_tasks.takeAt(index);
        endRemoveRows();

        emit taskRemoved(index);
    }
}


[[nodiscard]] bool TaskModel::loadAllTasks()
{
    bool result = false;

    DbHelper &dbh = DbHelper::getInstance();
    QSqlQueryModel *model = dbh.getAllRecords();
    //int rowCount = records->rowCount();
    m_tasks.clear();

    if (model != nullptr)
    {
        for(int i = 0; i < model->rowCount(); ++i)
        {
            int _id         = model->record(i).value("id").toInt();
            QString _name   = model->record(i).value("name").toString();
            QString _date   = model->record(i).value("deadline").toString();
            QDate _deadline = QDate::fromString(_date, "dd.MM.yyyy");
            int _progress   = model->record(i).value("progress").toInt();
            // add
            addTask(_id, _name, _deadline, _progress);
        }
        result = true;
    }
    delete (model);

    emit listLoaded(result);
    return result;
}

[[nodiscard]] bool TaskModel::saveAllTasks()
{
    bool result = true;

    DbHelper &dbh = DbHelper::getInstance();
    QString idsString{""}; // перечень всех id модели QList<Task*>

    for (int i = 0; i < rowCount(); i++)
    {
        Task* task = m_tasks.at(i);

        if (!dbh.saveRecord(task))
        { result = false; }

        idsString += (i) ? "," : "";
        idsString += QString::number(task->id());
    }

    // Удаляем все те записи из БД, которых нет в модели QList<Task*>
    if (!dbh.removeOther(idsString))
    { result = false; }

    emit listSaved(result);
    return result;
}

bool TaskModel::dirty() const
{
    return isDirty;
}

void TaskModel::setDirty(bool value)
{
    isDirty = value;
}
