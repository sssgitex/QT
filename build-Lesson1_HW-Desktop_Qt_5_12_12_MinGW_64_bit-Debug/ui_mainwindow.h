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
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *A_Line;
    QLineEdit *B_Line;
    QLineEdit *C_Line;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *AnswerButton;
    QLineEdit *AnswerLine;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 363);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        A_Line = new QLineEdit(centralwidget);
        A_Line->setObjectName(QString::fromUtf8("A_Line"));
        A_Line->setGeometry(QRect(50, 50, 100, 21));
        B_Line = new QLineEdit(centralwidget);
        B_Line->setObjectName(QString::fromUtf8("B_Line"));
        B_Line->setGeometry(QRect(250, 50, 100, 21));
        C_Line = new QLineEdit(centralwidget);
        C_Line->setObjectName(QString::fromUtf8("C_Line"));
        C_Line->setGeometry(QRect(450, 50, 100, 21));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(90, 20, 47, 21));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setTextFormat(Qt::AutoText);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(290, 20, 47, 21));
        label_2->setFont(font);
        label_2->setTextFormat(Qt::AutoText);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(490, 21, 47, 20));
        label_3->setFont(font);
        label_3->setTextFormat(Qt::AutoText);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(40, 90, 171, 21));
        QFont font1;
        font1.setPointSize(16);
        label_4->setFont(font1);
        AnswerButton = new QPushButton(centralwidget);
        AnswerButton->setObjectName(QString::fromUtf8("AnswerButton"));
        AnswerButton->setGeometry(QRect(50, 280, 81, 31));
        QFont font2;
        font2.setPointSize(10);
        AnswerButton->setFont(font2);
        AnswerLine = new QLineEdit(centralwidget);
        AnswerLine->setObjectName(QString::fromUtf8("AnswerLine"));
        AnswerLine->setGeometry(QRect(50, 240, 521, 31));
        AnswerLine->setFont(font2);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 600, 21));
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
        label->setText(QApplication::translate("MainWindow", "A", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "B", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "C", nullptr));
        label_4->setText(QApplication::translate("MainWindow", " ax2 + bx + c = 0", nullptr));
        AnswerButton->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\201\321\207\320\270\321\202\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
