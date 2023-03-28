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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *AnsweButton;
    QRadioButton *BinaryButton;
    QRadioButton *OctalButton;
    QRadioButton *HexButton;
    QLineEdit *AnswerLine;
    QLineEdit *GetLine;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(430, 427);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        AnsweButton = new QPushButton(centralwidget);
        AnsweButton->setObjectName(QString::fromUtf8("AnsweButton"));
        AnsweButton->setGeometry(QRect(60, 280, 80, 21));
        BinaryButton = new QRadioButton(centralwidget);
        BinaryButton->setObjectName(QString::fromUtf8("BinaryButton"));
        BinaryButton->setGeometry(QRect(60, 170, 84, 19));
        OctalButton = new QRadioButton(centralwidget);
        OctalButton->setObjectName(QString::fromUtf8("OctalButton"));
        OctalButton->setGeometry(QRect(60, 200, 84, 19));
        HexButton = new QRadioButton(centralwidget);
        HexButton->setObjectName(QString::fromUtf8("HexButton"));
        HexButton->setGeometry(QRect(60, 230, 84, 19));
        AnswerLine = new QLineEdit(centralwidget);
        AnswerLine->setObjectName(QString::fromUtf8("AnswerLine"));
        AnswerLine->setGeometry(QRect(170, 280, 201, 21));
        GetLine = new QLineEdit(centralwidget);
        GetLine->setObjectName(QString::fromUtf8("GetLine"));
        GetLine->setGeometry(QRect(60, 130, 311, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 430, 21));
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
        AnsweButton->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        BinaryButton->setText(QApplication::translate("MainWindow", "RadioButton", nullptr));
        OctalButton->setText(QApplication::translate("MainWindow", "RadioButton", nullptr));
        HexButton->setText(QApplication::translate("MainWindow", "RadioButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
