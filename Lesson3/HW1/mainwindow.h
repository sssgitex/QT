#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QTextDocument>
#include <QAbstractButton>

#define APP_NAME "Lesson 03. Task 1."

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
    void on_actionNew_triggered();

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_textEdit_textChanged();

    void on_actionLoad_triggered();

    void on_actionSave_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;

    void closeEvent (QCloseEvent*) override;

    bool on_save(QString&);
    bool on_load();
    void show_about();

    // Сохраненное имя файла
    QString fileName{""};
};

#endif // MAINWINDOW_H
