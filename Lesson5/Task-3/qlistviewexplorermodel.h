
#ifndef QLISTVIEWEXPLORERMODEL_H
#define QLISTVIEWEXPLORERMODEL_H

#include <QAbstractListModel>
#include <QDir>
#include <QModelIndex>


class QListViewExplorerModel : public QAbstractListModel
{
    Q_OBJECT
public:
    QListViewExplorerModel(QObject *parent=nullptr);
    int rowCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;

    void getFolderList(QString folderPath, QFileInfoList *dirList);

private:
    QFileInfoList *aDirList;
};

#endif // QLISTVIEWEXPLORERMODEL_H
