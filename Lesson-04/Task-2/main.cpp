
#include "mainwindow.h"

#include <QApplication>


#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    //QLocale::setDefault(QLocale(QLocale::Russian, QLocale::Russia));

//    QLocale systemLocale = QLocale::system();
//    QLocale::setDefault(systemLocale);

    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}
