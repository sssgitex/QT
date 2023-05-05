#ifndef TODOMODEL_H
#define TODOMODEL_H

#include <QAbstractListModel>
#include <QVariant>
#include <QHash>

#include <QModelIndex>
#include <QByteArray>

#include "todolist.h"

//class ToDoList;

class ToDoModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ToDoList *list READ list WRITE setList NOTIFY listChanged)

public:
    explicit ToDoModel(QObject *parent = nullptr);

    enum TaskRoles
    {
        DescriptionRole = Qt::UserRole,
        DeadlineRole,
        ProgressRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    ToDoList *list() ;
    void setList(ToDoList *list);

signals:

    void listChanged();

private:

    ToDoList *mList;

};

#endif // TODOMODEL_H
