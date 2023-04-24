#include <QCoreApplication>

#include <QPushButton>
#include <QDialogButtonBox>

#include <QMessageBox>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEdit->document()->setModified(false);
    this->setWindowTitle(APP_NAME);


    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);


    QMenu *fileMenu = new QMenu(tr("Файл"));
    QAction *newFileAction = new QAction(tr("Новый"), this);
    QAction *loadFileAction = new QAction(tr("Открыть"), this);
    QAction *loadFileROAction = new QAction(tr("Открыть только для чтения"), this);
    QAction *saveFileAction = new QAction(tr("Сохранить"), this);
    QAction *separatorAction = new QAction(this);
    separatorAction->setSeparator(true);
    QAction *exitAction = new QAction(tr("Выход"), this);
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(loadFileAction);
    fileMenu->addAction(loadFileROAction);
    fileMenu->addAction(saveFileAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);


    QMenu *optionsMenu = new QMenu(tr("Настройки"));
    QAction *helpAction = new QAction(tr("Помощь"), this);
    QAction *separatorAction2 = new QAction(this);
    separatorAction2->setSeparator(true);
    QAction *englishAction = new QAction(tr("Английский"), this);
    QAction *russianAction = new QAction(tr("Русский"), this);
    optionsMenu->addAction(helpAction);
    optionsMenu->addSeparator();
    optionsMenu->addAction(englishAction);
    optionsMenu->addAction(russianAction);


    menuBar->addMenu(fileMenu);
    menuBar->addMenu(optionsMenu);


    connect(newFileAction,    &QAction::triggered, this, &MainWindow::actionNewFile);
    connect(loadFileAction,   &QAction::triggered, this, [=]() { actionLoadFile(true); });
    connect(loadFileROAction, &QAction::triggered, this, [=]() { actionLoadFile(false); });
    connect(saveFileAction,   &QAction::triggered, this, &MainWindow::actionSaveFile);
    connect(exitAction,       &QAction::triggered, this, &QCoreApplication::quit);
    connect(helpAction,       &QAction::triggered, this, &MainWindow::showAbout);



    connect(ui->textEdit, &QTextEdit::textChanged, this, &MainWindow::actionTextChanged);


    QPushButton *btnClose = ui->buttonBox->button(QDialogButtonBox::Close);
    if (btnClose)
        connect(btnClose, &QPushButton::clicked, this, &QCoreApplication::quit);

    QPushButton *btnHelp = ui->buttonBox->button(QDialogButtonBox::Help);
    if (btnHelp)
        connect(btnHelp, &QPushButton::clicked, this, &MainWindow::showAbout);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAbout ()
{
    AboutDialog window;

    window.setModal(true);
    window.exec();
}

void MainWindow::closeEvent (QCloseEvent *event)
{

    if (ui->textEdit->document()->isModified())
    {
        QMessageBox::StandardButton resBtn = QMessageBox::question( this, APP_NAME,
                                                                   tr("Текущие изменения будут потеряны, продолжить?\n"),
                                                                   QMessageBox::No | QMessageBox::Yes,
                                                                   QMessageBox::No);
        if (resBtn != QMessageBox::Yes)
            event->ignore();
        else
            event->accept();
    }
}

bool MainWindow::onSave(QString& _file_name)
{
    if (_file_name.isEmpty())
        return false;

    QFile file(_file_name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, tr("Ошибка"), tr("Невозможно открыть файл для записи!"));
        return false;
    }

    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    out.flush();

    if (file.error() != QFile::NoError)
    {
        QMessageBox::critical(this, tr("Ошибка"), tr("Ошибка при записи: %1").arg(file.errorString()));
        if (file.isOpen())
            file.close();
        return false;
    }

    if (file.isOpen())
        file.close();

    ui->textEdit->document()->setModified(false);

    return true;
}

bool MainWindow::onLoad()
{

    QString newFileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "", tr("Текстовые файлы (*.txt);;Все файлы (*.*)"));
    if (newFileName.isEmpty())
        return false;

    QFile file(newFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, tr("Ошибка"), tr("Невозможно открыть файл для чтения!"));
        return false;
    }

    QTextStream in(&file);
    ui->textEdit->setText(in.readAll());
    file.close();

    ui->textEdit->document()->setModified(false);
    fileName = newFileName;

    return true;
}

void MainWindow::actionNewFile()
{

    if (ui->textEdit->document()->isModified())
    {
        QMessageBox::StandardButton resBtn = QMessageBox::question( this, APP_NAME,
                                                                   tr("Текущие изменения будут потеряны, продолжить?\n"),
                                                                   QMessageBox::No | QMessageBox::Yes,
                                                                   QMessageBox::No);
        if (resBtn != QMessageBox::Yes)
            return;
    }

    fileName = "";
    ui->textEdit->clear();
    ui->textEdit->document()->setModified(false);
    setAccessed();

}

void MainWindow::actionTextChanged()
{
    ui->textEdit->document()->setModified();
}

void MainWindow::actionLoadFile(const bool access)
{

    if (ui->textEdit->document()->isModified())
    {
        QMessageBox::StandardButton resBtn = QMessageBox::question( this, APP_NAME,
                                                                   tr("Текущие изменения будут потеряны, продолжить?\n"),
                                                                   QMessageBox::No | QMessageBox::Yes,
                                                                   QMessageBox::No);
        if (resBtn != QMessageBox::Yes)
            return;
    }

    if (onLoad())
        setAccessed(access);
}

void MainWindow::actionSaveFile()
{

    if (ui->textEdit->isReadOnly())
        return;

    QString newFileName;

    if (fileName.isEmpty())
        newFileName = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), "", tr("Текстовые файлы (*.txt);;Все файлы (*.*)"));
    else
        newFileName = fileName;

    if (onSave(newFileName))
        fileName = newFileName;
}

void MainWindow::setAccessed(const bool access)
{

    QAction *actSave = findActionByName(tr("Сохранить"));


    if (actSave)
        actSave->setEnabled(access);


    ui->textEdit->setReadOnly(!access);

}

QAction* MainWindow::findActionByName(const QString& name)
{
    QMenuBar* menubar = this->menuBar();
    QAction*  found   = nullptr;

    if (!menubar)
        return found;

    foreach (QAction* action, menubar->actions())
    {
        if (action->menu())
        {
            found = findActionByName(name, action->menu());
            if (found)
                break;
        }
        else if (action->text() == name)
        {
            found = action;
            break;
        }
    }

    return found;
}

QAction* MainWindow::findActionByName(const QString& name, QMenu* menu)
{
    if (!menu)
        return nullptr;

    foreach (QAction* action, menu->actions())
    {
        if (action->menu())
        {
            QAction* subAction = findActionByName(name, action->menu());
            if (subAction)
                return subAction;
        }
        else if (action->text() == name)
            return action;
    }

    return nullptr;
}
