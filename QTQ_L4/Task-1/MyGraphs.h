#pragma once

#include <QObject>
#include <QColor>
#include <QString>

#include <QtQml/qqml.h>
#include "Auto_property.h"


class MyGraphs : public QObject
{
    Q_OBJECT

    QML_ELEMENT

    AUTO_PROPERTY(QColor, color)
    AUTO_PROPERTY(QString, name)

    Q_PROPERTY(QVector<qreal> _X READ get_X CONSTANT)
    Q_PROPERTY(QVector<qreal> _Y READ get_Y CONSTANT)

    READONLY_PROPERTY(int, length)

    READONLY_PROPERTY(qreal, Xmin)
    READONLY_PROPERTY(qreal, Xmax)
    READONLY_PROPERTY(qreal, Ymin)
    READONLY_PROPERTY(qreal, Ymax)



public:

    enum class Charts
    {
        sinX = 0,
        X,
        modX,
        sqrtX,
        log2X
    };

    Q_ENUM(Charts)
    void setPriority(Charts chart);
    Charts chart() const;

public:

    Q_INVOKABLE QVector<qreal> get_X(){ return _X;}
    Q_INVOKABLE QVector<qreal> get_Y(){ return _Y;}

public:

    MyGraphs (QObject *parent = nullptr);

signals:

public slots:

    void y_sinX();
    void y_X();
    void y_modX();
    void y_sqrtX();
    void y_log2X();

    void minmaxY();

private:

    QVector<qreal> _X;
    QVector<qreal> _Y;
};

