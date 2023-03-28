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
    QLabel *label;
    QLineEdit *GetLine;
    QRadioButton *BinaryButton;
    QRadioButton *OctalButton;
    QRadioButton *HexButton;
    QLabel *label_2;
    QLineEdit *AnswerLine;
    QPushButton *AnswerButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(530, 269);
        MainWindow->setMouseTracking(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 151, 21));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        GetLine = new QLineEdit(centralwidget);
        GetLine->setObjectName(QString::fromUtf8("GetLine"));
        GetLine->setGeometry(QRect(180, 30, 331, 21));
        BinaryButton = new QRadioButton(centralwidget);
        BinaryButton->setObjectName(QString::fromUtf8("BinaryButton"));
        BinaryButton->setGeometry(QRect(20, 90, 121, 19));
        BinaryButton->setChecked(true);
        OctalButton = new QRadioButton(centralwidget);
        OctalButton->setObjectName(QString::fromUtf8("OctalButton"));
        OctalButton->setGeometry(QRect(20, 120, 131, 19));
        HexButton = new QRadioButton(centralwidget);
        HexButton->setObjectName(QString::fromUtf8("HexButton"));
        HexButton->setGeometry(QRect(20, 150, 171, 19));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 190, 151, 21));
        label_2->setFont(font);
        AnswerLine = new QLineEdit(centralwidget);
        AnswerLine->setObjectName(QString::fromUtf8("AnswerLine"));
        AnswerLine->setEnabled(true);
        AnswerLine->setGeometry(QRect(100, 190, 281, 21));
        AnswerLine->setReadOnly(false);
        AnswerButton = new QPushButton(centralwidget);
        AnswerButton->setObjectName(QString::fromUtf8("AnswerButton"));
        AnswerButton->setGeometry(QRect(410, 190, 80, 21));
        AnswerButton->setFlat(false);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 530, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\262\320\276\320\264 \321\207\320\270\321\201\320\265\320\273", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\207\320\270\321\201\320\273\320\276:", nullptr));
        BinaryButton->setText(QApplication::translate("MainWindow", "\320\224\320\262\320\276\320\270\321\207\320\275\320\260\321\217 \320\241\320\270\321\201\321\202\320\265\320\274\320\260", nullptr));
        OctalButton->setText(QApplication::translate("MainWindow", "\320\222\320\276\321\201\320\274\320\265\321\200\320\270\321\207\320\275\320\260\321\217 \320\241\320\270\321\201\321\202\320\265\320\274\320\260", nullptr));
        HexButton->setText(QApplication::translate("MainWindow", "\320\250\320\265\321\201\321\202\320\275\320\260\321\206\320\260\321\202\320\265\321\200\320\270\321\207\320\275\320\260\321\217 \320\241\320\270\321\201\321\202\320\265\320\274\320\260", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\236\320\242\320\222\320\225\320\242:", nullptr));
        AnswerLine->setText(QString());
        AnswerButton->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
