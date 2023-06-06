#pragma once

#include <QObject>
#include <QtQml/qqml.h>
#include <Auto_property.h>


class MyGraphs : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    READONLY_PROPERTY(QVector<qreal>, X)
    READONLY_PROPERTY(QVector<qreal>, Y)
    READONLY_PROPERTY(int, length)

    READONLY_PROPERTY(QVector<qreal>, XsLine)
    READONLY_PROPERTY(QVector<qreal>, YsLine)
    READONLY_PROPERTY(int, lengthLine)

public:

    MyGraphs(QObject *parent = nullptr);

signals:

private:

    void linearDependency();
    void createLine(bool b/*>0*/);

    double a{0};
    double b{0};
};
