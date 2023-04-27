/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionOpen_read_only;
    QAction *actionSave;
    QAction *actionExit;
    QAction *actionHelp;
    QAction *actionEnglish;
    QAction *actionRussian;
    QAction *actionClientor;
    QAction *actionDtor;
    QAction *actionMaterial_blue;
    QAction *actionMaterial_dark;
    QAction *actionNeonButtons;
    QAction *actionUbuntu;
    QAction *actionRestoreTheme;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnHelp;
    QPushButton *btnClose;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOptions;
    QMenu *menuThemes;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(397, 390);
        MainWindow->setMinimumSize(QSize(397, 390));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/icon-256.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName("actionNew");
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        actionOpen_read_only = new QAction(MainWindow);
        actionOpen_read_only->setObjectName("actionOpen_read_only");
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName("actionHelp");
        actionEnglish = new QAction(MainWindow);
        actionEnglish->setObjectName("actionEnglish");
        actionRussian = new QAction(MainWindow);
        actionRussian->setObjectName("actionRussian");
        actionClientor = new QAction(MainWindow);
        actionClientor->setObjectName("actionClientor");
        actionDtor = new QAction(MainWindow);
        actionDtor->setObjectName("actionDtor");
        actionMaterial_blue = new QAction(MainWindow);
        actionMaterial_blue->setObjectName("actionMaterial_blue");
        actionMaterial_dark = new QAction(MainWindow);
        actionMaterial_dark->setObjectName("actionMaterial_dark");
        actionNeonButtons = new QAction(MainWindow);
        actionNeonButtons->setObjectName("actionNeonButtons");
        actionUbuntu = new QAction(MainWindow);
        actionUbuntu->setObjectName("actionUbuntu");
        actionRestoreTheme = new QAction(MainWindow);
        actionRestoreTheme->setObjectName("actionRestoreTheme");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setMinimumSize(QSize(375, 250));

        verticalLayout->addWidget(textEdit);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, 5, -1, 5);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnHelp = new QPushButton(centralwidget);
        btnHelp->setObjectName("btnHelp");
        btnHelp->setMinimumSize(QSize(80, 20));

        horizontalLayout->addWidget(btnHelp);

        btnClose = new QPushButton(centralwidget);
        btnClose->setObjectName("btnClose");
        btnClose->setMinimumSize(QSize(80, 20));

        horizontalLayout->addWidget(btnClose);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 397, 17));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName("menuFile");
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName("menuOptions");
        menuThemes = new QMenu(menuBar);
        menuThemes->setObjectName("menuThemes");
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuOptions->menuAction());
        menuBar->addAction(menuThemes->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionOpen_read_only);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuOptions->addAction(actionHelp);
        menuOptions->addSeparator();
        menuOptions->addAction(actionEnglish);
        menuOptions->addAction(actionRussian);
        menuOptions->addSeparator();
        menuThemes->addAction(actionClientor);
        menuThemes->addAction(actionDtor);
        menuThemes->addAction(actionMaterial_blue);
        menuThemes->addAction(actionMaterial_dark);
        menuThemes->addAction(actionNeonButtons);
        menuThemes->addAction(actionUbuntu);
        menuThemes->addSeparator();
        menuThemes->addAction(actionRestoreTheme);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "&New", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "&Open", nullptr));
        actionOpen_read_only->setText(QCoreApplication::translate("MainWindow", "Open (read only)", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "&Save", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "&Exit", nullptr));
        actionHelp->setText(QCoreApplication::translate("MainWindow", "Help", nullptr));
        actionEnglish->setText(QCoreApplication::translate("MainWindow", "English", nullptr));
        actionRussian->setText(QCoreApplication::translate("MainWindow", "Russian", nullptr));
        actionClientor->setText(QCoreApplication::translate("MainWindow", "Clientor", nullptr));
        actionDtor->setText(QCoreApplication::translate("MainWindow", "Dtor", nullptr));
        actionMaterial_blue->setText(QCoreApplication::translate("MainWindow", "Material-blue", nullptr));
        actionMaterial_dark->setText(QCoreApplication::translate("MainWindow", "Material-dark", nullptr));
        actionNeonButtons->setText(QCoreApplication::translate("MainWindow", "NeonButtons", nullptr));
        actionUbuntu->setText(QCoreApplication::translate("MainWindow", "Ubuntu", nullptr));
        actionRestoreTheme->setText(QCoreApplication::translate("MainWindow", "Restore defaults", nullptr));
        btnHelp->setText(QCoreApplication::translate("MainWindow", "&Help", nullptr));
        btnClose->setText(QCoreApplication::translate("MainWindow", "&Close", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuOptions->setTitle(QCoreApplication::translate("MainWindow", "Options", nullptr));
        menuThemes->setTitle(QCoreApplication::translate("MainWindow", "Themes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
