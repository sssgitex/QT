#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
//#include <QFile>
//#include <QTextStream>
#include "taskmodel.h"

int main(int argc, char *argv[])
{
    QQuickStyle::setStyle("Fusion");//Material
    QGuiApplication app(argc, argv);

    // создаем модель для задач
    TaskModel taskModel;

    //taskModel.loadTasksFromFile();

    // создаем QML-интерфейс
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("taskModel", &taskModel);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    // сохраняем данные в файл при выходе из программы
//    QObject::connect(&app, &QCoreApplication::aboutToQuit,
//        &taskModel, [&taskModel]() { taskModel.saveTasksToFile(); });

    return app.exec();
}
