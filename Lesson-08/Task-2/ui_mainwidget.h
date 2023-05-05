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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnLevelUp;
    QLineEdit *lineEdit;
    QPushButton *btnListView;
    QPushButton *btnIconsView;
    QListView *listView;
    QStatusBar *statusbar;
    QPushButton *btnFindFiles;

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
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 10, 403, 461));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btnLevelUp = new QPushButton(widget);
        btnLevelUp->setObjectName("btnLevelUp");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/folderup.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnLevelUp->setIcon(icon1);

        horizontalLayout->addWidget(btnLevelUp);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout->addWidget(lineEdit);

        btnListView = new QPushButton(widget);
        btnListView->setObjectName("btnListView");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/list.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnListView->setIcon(icon2);

        horizontalLayout->addWidget(btnListView);

        btnIconsView = new QPushButton(widget);
        btnIconsView->setObjectName("btnIconsView");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/img/iconlist.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnIconsView->setIcon(icon3);

        horizontalLayout->addWidget(btnIconsView);


        verticalLayout->addLayout(horizontalLayout);

        listView = new QListView(widget);
        listView->setObjectName("listView");
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listView->sizePolicy().hasHeightForWidth());
        listView->setSizePolicy(sizePolicy);
        listView->setMinimumSize(QSize(401, 431));
        listView->setUniformItemSizes(false);

        verticalLayout->addWidget(listView);

        statusbar = new QStatusBar(MainWidget);
        statusbar->setObjectName("statusbar");
        statusbar->setGeometry(QRect(0, 0, 3, 25));
        btnFindFiles = new QPushButton(MainWidget);
        btnFindFiles->setObjectName("btnFindFiles");
        btnFindFiles->setGeometry(QRect(10, 480, 401, 22));

        retranslateUi(MainWidget);

        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QCoreApplication::translate("MainWidget", "MainWindow", nullptr));
        btnLevelUp->setText(QString());
        btnListView->setText(QString());
        btnIconsView->setText(QString());
        btnFindFiles->setText(QCoreApplication::translate("MainWidget", "Find files", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
