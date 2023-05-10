#include "taskmodel.h"

#include <QFile>

TaskModel::TaskModel(QObject *parent)
    : QAbstractListModel(parent)
    , isDirty (false)
{
    connect(this, &TaskModel::listLoaded, this, [=]() { setDirty(false); });
    connect(this, &TaskModel::listSaved, this, [=]() { setDirty(false); });
    connect(this, &TaskModel::taskAdded, this, [=]() { setDirty(true); });
    connect(this, &TaskModel::taskChanged, this, [=]() { setDirty(true); });
    connect(this, &TaskModel::taskRemoved, this, [=]() { setDirty(true); });

    loadTasksFromFile ();

    //addTask(QStringLiteral("Wash the car"), QDate::currentDate().addDays(7), 1);
    //addTask(QStringLiteral("Cleaning"), QDate::currentDate().addDays(7), 5);
}

void TaskModel::addTask(QString name, QDate deadline, int progress)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_tasks.append(new Task(name, deadline, progress, this));
    endInsertRows();

    emit taskAdded(m_tasks.size() - 1);
}

void TaskModel::addTaskFromString(QString string)
{
    QStringList parts = string.split(",");
    if (parts.size() == 3)
    {
        QString name = parts.at(0);
        QDate deadline = QDate::fromString(parts.at(1), "dd.MM.yyyy");
        int progress = parts.at(2).toInt();
        addTask(name, deadline, progress);
    }
}

Task* TaskModel::getTask(int index)
{
    if (index >= 0 && index < m_tasks.size())
    {
        return m_tasks.at(index);
    }
    else
    {
        return nullptr;
    }
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
        case NameRole:
            return task->name();
        case DeadlineRole:
            return task->deadline();
        case ProgressRole:
            return task->progress();
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
    roles[NameRole] = "name";
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


[[nodiscard]] bool TaskModel::loadTasksFromFile()
{
    bool result = false;

    // загружаем данные из файла tasks.txt, если он существует
    QFile file(m_file);
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            addTaskFromString(line);
        }
        file.close();
        result = true;
    }

    emit listLoaded(result);
    return result;
}

[[nodiscard]] bool TaskModel::saveTasksToFile()
{
    bool result = false;

    // сохраняем данные в файл
    QFile file(m_file);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        for (int i = 0; i < rowCount(); i++)
        {
            Task* task = getTask(i);
            out << task->toString() << "\n";
        }
        file.close();
        result = true;
    }

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
