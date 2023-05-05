#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include <QLocale>
#include <QTranslator>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(mdi);

    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("MDI Editor");
    QCoreApplication::setOrganizationName("Homework");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QApplication::setWindowIcon(QIcon(":/images/MDI_256.png"));
    app.setDesktopSettingsAware(true);

    QCommandLineParser parser;
    parser.setApplicationDescription("Qt MDI Editor");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "The file to open.");
    parser.process(app);

//    QTranslator translator;
//    const QStringList uiLanguages = QLocale::system().uiLanguages();
//    for (const QString &locale : uiLanguages)
//    {
//        const QString baseName = "MDIeditor_" + QLocale(locale).name();
//        if (translator.load(":/i18n/" + baseName))
//        {
//            app.installTranslator(&translator);
//            break;
//        }
//    }

    MainWindow mainWin;
    const QStringList posArgs = parser.positionalArguments();
    for (const QString &fileName : posArgs)
        mainWin.openFile(fileName);
    mainWin.show();

    return app.exec();
}
