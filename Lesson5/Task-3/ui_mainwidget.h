/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QWidget *centralwidget;
    QListView *listView;
    QLineEdit *lineEdit;
    QPushButton *btnLevelUp;
    QPushButton *btnIconsView;
    QPushButton *btnListView;
    QStatusBar *statusbar;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName("MainWidget");
        MainWidget->resize(420, 537);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/pngegg_128.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWidget->setWindowIcon(icon);
        centralwidget = new QWidget(MainWidget);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setGeometry(QRect(0, 0, 421, 481));
        listView = new QListView(centralwidget);
        listView->setObjectName("listView");
        listView->setGeometry(QRect(10, 40, 401, 431));
        listView->setUniformItemSizes(false);
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(50, 10, 291, 22));
        btnLevelUp = new QPushButton(centralwidget);
        btnLevelUp->setObjectName("btnLevelUp");
        btnLevelUp->setGeometry(QRect(10, 10, 31, 23));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/folderup.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnLevelUp->setIcon(icon1);
        btnIconsView = new QPushButton(centralwidget);
        btnIconsView->setObjectName("btnIconsView");
        btnIconsView->setGeometry(QRect(380, 10, 31, 23));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/iconlist.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnIconsView->setIcon(icon2);
        btnListView = new QPushButton(centralwidget);
        btnListView->setObjectName("btnListView");
        btnListView->setGeometry(QRect(350, 10, 31, 23));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/img/list.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnListView->setIcon(icon3);
        statusbar = new QStatusBar(MainWidget);
        statusbar->setObjectName("statusbar");
        statusbar->setGeometry(QRect(0, 0, 3, 25));

        retranslateUi(MainWidget);

        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QCoreApplication::translate("MainWidget", "MainWindow", nullptr));
        btnLevelUp->setText(QString());
        btnIconsView->setText(QString());
        btnListView->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
