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
#include <QtWidgets/QLabel>
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
    QPushButton *AnswerButton;
    QRadioButton *DegreeButton;
    QRadioButton *RadianButton;
    QLineEdit *B_Line;
    QLineEdit *C_Line;
    QLineEdit *AngleLine;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *AnswerLine;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(494, 492);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        AnswerButton = new QPushButton(centralwidget);
        AnswerButton->setObjectName(QString::fromUtf8("AnswerButton"));
        AnswerButton->setGeometry(QRect(40, 390, 81, 41));
        DegreeButton = new QRadioButton(centralwidget);
        DegreeButton->setObjectName(QString::fromUtf8("DegreeButton"));
        DegreeButton->setGeometry(QRect(40, 160, 84, 19));
        DegreeButton->setChecked(true);
        RadianButton = new QRadioButton(centralwidget);
        RadianButton->setObjectName(QString::fromUtf8("RadianButton"));
        RadianButton->setGeometry(QRect(40, 200, 84, 19));
        B_Line = new QLineEdit(centralwidget);
        B_Line->setObjectName(QString::fromUtf8("B_Line"));
        B_Line->setGeometry(QRect(40, 100, 113, 21));
        C_Line = new QLineEdit(centralwidget);
        C_Line->setObjectName(QString::fromUtf8("C_Line"));
        C_Line->setGeometry(QRect(190, 100, 113, 21));
        AngleLine = new QLineEdit(centralwidget);
        AngleLine->setObjectName(QString::fromUtf8("AngleLine"));
        AngleLine->setGeometry(QRect(340, 100, 113, 21));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 80, 61, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(190, 80, 71, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(340, 80, 47, 13));
        AnswerLine = new QLineEdit(centralwidget);
        AnswerLine->setObjectName(QString::fromUtf8("AnswerLine"));
        AnswerLine->setGeometry(QRect(40, 360, 411, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 494, 21));
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
        AnswerButton->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\201\321\207\320\270\321\202\320\260\321\202\321\214", nullptr));
        DegreeButton->setText(QApplication::translate("MainWindow", "\320\223\321\200\320\260\320\264\321\203\321\201\321\213", nullptr));
        RadianButton->setText(QApplication::translate("MainWindow", "\320\240\320\260\320\264\320\270\320\260\320\275\321\213", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\241\321\202\320\276\321\200\320\276\320\275\320\260 B", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\241\321\202\320\276\321\200\320\276\320\275\320\260 C", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\320\243\320\263\320\276\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
