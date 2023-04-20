/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *lblCurrency;
    QLabel *lblWeather;
    QPushButton *btnGet;
    QDialogButtonBox *buttonBox;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(340, 290);
        MainWindow->setMinimumSize(QSize(340, 290));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/mailru-icon-256.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 0, 320, 210));
        groupBox->setMinimumSize(QSize(320, 210));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 30, 301, 171));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lblCurrency = new QLabel(layoutWidget);
        lblCurrency->setObjectName("lblCurrency");

        verticalLayout->addWidget(lblCurrency);

        lblWeather = new QLabel(layoutWidget);
        lblWeather->setObjectName("lblWeather");

        verticalLayout->addWidget(lblWeather);

        btnGet = new QPushButton(layoutWidget);
        btnGet->setObjectName("btnGet");

        verticalLayout->addWidget(btnGet);

        buttonBox = new QDialogButtonBox(centralwidget);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(160, 220, 167, 29));
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 340, 25));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "mail.ru", nullptr));
        lblCurrency->setText(QCoreApplication::translate("MainWindow", "\320\272\321\203\321\200\321\201\321\213 \320\262\320\260\320\273\321\216\321\202", nullptr));
        lblWeather->setText(QCoreApplication::translate("MainWindow", "\320\277\320\276\320\263\320\276\320\264\320\260", nullptr));
        btnGet->setText(QCoreApplication::translate("MainWindow", "Get info", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
