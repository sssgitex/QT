#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QTextDocument>
#include <QAction>
#include <QMenu>
#include <QMenuBar>

#include <QTranslator>
#include <QLocale>

#define APP_NAME tr("Lesson 04. Task 1.")

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
    void actionNewFile();
    void actionTextChanged();
    void actionLoadFile(const bool);
    void actionSaveFile();
    void showAbout();
    void setLanguage(const QLocale);

private: // свойства
    Ui::MainWindow *ui;

    // Сохраненное имя файла
    QString fileName{""};

    QTranslator translator;
    QLocale locale;

private: // методы
    void closeEvent (QCloseEvent*) override;

    bool onSave(QString&);
    bool onLoad();

    void setAccessed(const bool access = true);

};



#endif // MAINWINDOW_H
