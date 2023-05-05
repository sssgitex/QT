
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "qlistviewexplorermodel.h"

#include <QFileInfoList>
#include <QWidget>

#define APP_NAME tr("Lesson 08. Task 2.")


QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget

{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void on_doIt(const QModelIndex &index);
    void on_levelUp();
    void on_iconsView();
    void on_listView();
    void on_findFiles();

private:
    Ui::MainWidget *ui;
    QFileInfoList *aDirList;
    QListViewExplorerModel *model;
    QDir currentFolder;
};

#endif // MAINWIDGET_H
