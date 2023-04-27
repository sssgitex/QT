
#include "mainwindow.h"

#include <QApplication>


#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    a.setDesktopSettingsAware(true);

    MainWindow w;
    w.show();
    return a.exec();
}
