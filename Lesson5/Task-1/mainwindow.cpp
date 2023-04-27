#include <QCoreApplication>

#include <QPushButton>
#include <QDialogButtonBox>

#include <QMessageBox>
#include <QFileDialog>
#include <QStyle>

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


    ui->actionOpen->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_O));
    ui->actionNew->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_N));
    ui->actionNew->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_S));

    connect(ui->actionNew,     &QAction::triggered, this, &MainWindow::actionNewFile);
    connect(ui->actionOpen,    &QAction::triggered, this, [=]() { actionLoadFile(true); });
    connect(ui->actionOpen_read_only, &QAction::triggered, this, [=]() { actionLoadFile(false); });
    connect(ui->actionSave,    &QAction::triggered, this, &MainWindow::actionSaveFile);
    connect(ui->actionExit,    &QAction::triggered, this, &QCoreApplication::quit);
    connect(ui->actionHelp,    &QAction::triggered, this, &MainWindow::showAbout);
    connect(ui->actionEnglish, &QAction::triggered, this, [=]() { setLanguage(QLocale(QLocale::English)); });
    connect(ui->actionRussian, &QAction::triggered, this, [=]() { setLanguage(QLocale(QLocale::Russian)); });

    connect(ui->actionClientor, &QAction::triggered, this, [=]() { setTheme( "Clientor" ); });
    connect(ui->actionDtor, &QAction::triggered, this, [=]() { setTheme( "Dtor" ); });
    connect(ui->actionMaterial_blue, &QAction::triggered, this, [=]() { setTheme( "Material-blue" ); });
    connect(ui->actionMaterial_dark, &QAction::triggered, this, [=]() { setTheme( "Material-dark" ); });
    connect(ui->actionNeonButtons, &QAction::triggered, this, [=]() { setTheme( "NeonButtons" ); });
    connect(ui->actionUbuntu, &QAction::triggered, this, [=]() { setTheme( "Ubuntu" ); });

    connect(ui->actionRestoreTheme, &QAction::triggered, this, &MainWindow::restoreTheme);

    connect(ui->btnClose, &QPushButton::clicked, this, &QCoreApplication::quit);
    connect(ui->btnHelp,  &QPushButton::clicked, this, &MainWindow::showAbout);

    setLanguage(QLocale::system());
    saveTheme();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAbout ()
{
    AboutDialog window(locale, this);

    window.setModal(true);
    window.exec();
}

void MainWindow::closeEvent (QCloseEvent *event)
{

    if (ui->textEdit->document()->isModified())
    {
        QMessageBox::StandardButton resBtn = QMessageBox::question( this, APP_NAME,
                                                                   tr("The current changes will be lost, continue?\n"),
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
        QMessageBox::critical(this, tr("Error"), tr("Unable to open file for writing!"));
        return false;
    }

    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    out.flush();

    if (file.error() != QFile::NoError)
    {
        QMessageBox::critical(this, tr("Error"), tr("Error writing file: %1").arg(file.errorString()));
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

    QString newFileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("Text files (*.txt);;All files (*.*)"));
    if (newFileName.isEmpty())
        return false;

    QFile file(newFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, tr("Error"), tr("Unable to open file for reading!"));
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
                                                                   tr("The current changes will be lost, continue?\n"),
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
                                                                   tr("The current changes will be lost, continue?\n"),
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
        newFileName = QFileDialog::getSaveFileName(this, tr("Save file"), "", tr("Text files (*.txt);;All files (*.*)"));
    else
        newFileName = fileName;

    if (onSave(newFileName))
        fileName = newFileName;
}

void MainWindow::setAccessed(const bool access)
{

    ui->actionSave->setEnabled(access);


    ui->textEdit->setReadOnly(!access);

}


void MainWindow::setLanguage(const QLocale newLocale)
{
    QLocale localeRU (QLocale::Russian);
    QLocale localeEN (QLocale::English);
    QString flName{""};

    if (newLocale.name() == localeRU.name())
    {
        flName = ":/tr/QtLanguage_ru.qm";
        locale = localeRU;
    }
    else
    {
        flName = ":/tr/QtLanguage_en.qm";
        locale = localeEN;
    }


    if (translator.load(flName))
    {
        qApp->installTranslator(&translator);
        QLocale::setDefault(locale);
        ui->retranslateUi(this);
    }
    else
    {

        qWarning() << "Failed to load translation file:" << flName;
    }

}


void MainWindow::restoreTheme()
{
    qApp->setStyle(m_styleName);
    qApp->setStyleSheet(m_styleSheet);
    qApp->setPalette(qApp->style()->standardPalette());
}


void MainWindow::saveTheme()
{
    m_styleName = QApplication::style()->objectName();
    m_styleSheet = qApp->styleSheet();
}

void MainWindow::setTheme(const QString theme)
{
    QString style_sheet = readTextFile(":/stylesheets/"+ theme + ".qss");
    if (!style_sheet.isEmpty())
        qApp->setStyleSheet(style_sheet);
}


QByteArray readTextFile(const QString &file_path)
{
    QFile input_file(file_path);
    QByteArray input_data;

    if (input_file.open(QIODevice::Text | QIODevice::Unbuffered | QIODevice::ReadOnly))
    {
        input_data = input_file.readAll();
        input_file.close();
        return input_data;
    }
    else
    {
        return QByteArray();
    }
}
