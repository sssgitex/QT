#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <qml_table_model.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    QMLTableModel model;
    model.appendRowElement(QMLTableModel::RowElement{1, "Ivan", "Ivanov", {"Sergey Stepanov", "Egor Potapov"}});
    model.appendRowElement(QMLTableModel::RowElement{2, "Egor", "Svistov", {"Oleg Zarelua", "Alexander Zotov", "Elena Ivanova"}});
    model.appendRowElement(QMLTableModel::RowElement{3, "Stepan", "Tok", {"Ivan Ivanov", "Alexander Zotov", "Elena Ivanova"}});
    model.appendRowElement(QMLTableModel::RowElement{4, "Fedor", "Smolov", {"Ivan Ivanov", "Egor Potapov", "Elena Ivanova"}});
    model.appendRowElement(QMLTableModel::RowElement{5, "Petr", "Koshkin", {}});

    engine.rootContext()->setContextProperty("mdl", &model);
    engine.load(url);

    return app.exec();
}
