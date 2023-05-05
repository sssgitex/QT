#ifndef TODOLIST_H
#define TODOLIST_H

#include <QObject>
#include <QVector>
#include <QDate>

// структура задачи
struct ToDoItem
{
    QString description;
    QDate deadLine;
    uint progress;
};

class ToDoList : public QObject
{

    Q_OBJECT

public:

    ToDoList(QObject *parent = nullptr);

    QVector<ToDoItem> items() const;

    // определяет, были ли данные успешно изменены или нет
    bool setItemAt(int index, const ToDoItem &item);

    void addItemFromString(QString string);
    QString toString(const ToDoItem& item) const;

    Q_INVOKABLE void removeItem(int index);

signals:

    // сигналы не требуют определений

    void preItemAppend();
    void postItemAppended();

    void preItemRemoved(int);
    void postItemRemoved(int);

public slots:

    void appendItem();
    //void removeCompletedItems();

private:

    QVector<ToDoItem> mItems;

};

#endif // TODOLIST_H
