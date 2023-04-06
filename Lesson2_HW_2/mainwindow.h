#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ButtonUp_clicked();

    void on_ButtonDown_clicked();

    void on_ButtonAdd_clicked();

    void on_ButtonDel_clicked();

    void on_IconsCheck_stateChanged(int arg1);

private:

    Ui::MainWindow *ui;
    QStandardItemModel *model;
};
#endif // MAINWINDOW_H
