#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFile>

#include "todolist.h"
#include "todomodel.h"

int main(int argc, char *argv[])
{
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    /*!
     * \brief qmlRegisterType<ToDoModel>
     * Registers the cpp model with qml type
     */
    qmlRegisterType<ToDoModel>("ToDo",1,0,"ToDoModel");
    qmlRegisterUncreatableType<ToDoList>("ToDo",1,0,"ToDoList",
                                         QStringLiteral("ToDoList should not be created in QML"));
    ToDoList toDoList;

    // загружаем данные из файла tasks.txt, если он существует
    QFile file("tasks.txt");
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            toDoList.addItemFromString(line);
        }
        file.close();
    }


    QQmlApplicationEngine engine;
    /*!
      This is where the todolist is actually exposed to qml
      as a context property
      */
    engine.rootContext()->setContextProperty(QStringLiteral("toDoList"), &toDoList);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    //if (engine.rootObjects().isEmpty()) return -1;

    // сохраняем данные в файл при выходе из программы
    QObject::connect(&app, &QCoreApplication::aboutToQuit, [&]() {
        QFile file("tasks.txt");
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QVector<ToDoItem> items = toDoList.items();
            QTextStream out(&file);
            for (auto it = items.begin(); it != items.end(); ++it)
            {
                out << toDoList.toString(*it) << "\n";
            }
            file.close();
        }
    });

    return app.exec();
}
