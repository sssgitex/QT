#include "todolist.h"

ToDoList::ToDoList(QObject *parent) : QObject(parent)
{

}

QVector<ToDoItem> ToDoList::items() const
{
    return mItems;
}

// определяет, были ли данные успешно изменены или нет
bool ToDoList::setItemAt(int index, const ToDoItem &item)
{
    // проверка индекса
    if (index < 0 || index >= mItems.size())
        return false;

    const ToDoItem &oldItem = mItems.at(index);
    /*
     * checks if new item has identical
     * values or not to check whether we are changing
     * the data or not
     */
    if (//item.done == oldItem.done &&
        !item.description.compare(oldItem.description, Qt::CaseInsensitive) &&
        item.deadLine == oldItem.deadLine &&
        item.progress == oldItem.progress)
    {
        return false;
    }

    mItems [index] = item;

    return true;
}

void ToDoList::appendItem()
{
    emit preItemAppend();

    ToDoItem item;
    //item.done = false;
    item.description = "new item" + QString::number (mItems.count());
    item.deadLine = QDate::currentDate().addDays(7);
    item.progress = 0;
    mItems.append(item);

    emit postItemAppended();
}

void ToDoList::addItemFromString(QString string)
{
    QStringList _parts = string.split(",");
    if (_parts.size() == 3)
    {
        QString description = _parts.at(0);
        QDate deadline = QDate::fromString(_parts.at(1), "dd.MM.yyyy");
        uint progress = static_cast<uint>(_parts.at(2).toInt());
        mItems.append({description, deadline, progress});
    }
}

QString ToDoList::toString(const ToDoItem& item) const
{
    return QString("%1,%2,%3").arg(item.description).arg(item.deadLine.toString("dd.MM.yyyy")).arg(item.progress);
}



void ToDoList::removeItem(int index)
{
    emit preItemRemoved(index);
    mItems.removeAt(index);
    //qDebug() << "item at " << index << " removed";
    emit postItemRemoved(index);
}
