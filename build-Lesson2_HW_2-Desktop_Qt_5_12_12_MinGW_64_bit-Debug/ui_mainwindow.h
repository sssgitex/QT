/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QListView *listView;
    QPushButton *ButtonUp;
    QPushButton *ButtonDown;
    QPushButton *ButtonAdd;
    QPushButton *ButtonDel;
    QCheckBox *IconsCheck;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(561, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        listView = new QListView(centralwidget);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(20, 10, 521, 301));
        ButtonUp = new QPushButton(centralwidget);
        ButtonUp->setObjectName(QString::fromUtf8("ButtonUp"));
        ButtonUp->setGeometry(QRect(20, 330, 80, 21));
        ButtonDown = new QPushButton(centralwidget);
        ButtonDown->setObjectName(QString::fromUtf8("ButtonDown"));
        ButtonDown->setGeometry(QRect(20, 360, 80, 21));
        ButtonAdd = new QPushButton(centralwidget);
        ButtonAdd->setObjectName(QString::fromUtf8("ButtonAdd"));
        ButtonAdd->setGeometry(QRect(110, 330, 80, 21));
        ButtonDel = new QPushButton(centralwidget);
        ButtonDel->setObjectName(QString::fromUtf8("ButtonDel"));
        ButtonDel->setGeometry(QRect(110, 360, 80, 21));
        IconsCheck = new QCheckBox(centralwidget);
        IconsCheck->setObjectName(QString::fromUtf8("IconsCheck"));
        IconsCheck->setGeometry(QRect(230, 360, 72, 19));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 561, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        ButtonUp->setText(QApplication::translate("MainWindow", "UP", nullptr));
        ButtonDown->setText(QApplication::translate("MainWindow", "DOWN", nullptr));
        ButtonAdd->setText(QApplication::translate("MainWindow", "Add", nullptr));
        ButtonDel->setText(QApplication::translate("MainWindow", "Delete", nullptr));
        IconsCheck->setText(QApplication::translate("MainWindow", "Icons", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
