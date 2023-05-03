
#ifndef SOMEITEM_H
#define SOMEITEM_H

#include <QObject>
#include <QGraphicsItem>

#include <QPoint>
#include <QPointF>
#include <QPainter>
#include <QBrush>

#include <QGraphicsSceneMouseEvent>



class SomeItem : public QObject, public QGraphicsItem
{

    Q_OBJECT
    //Q_PROPERTY(QBrush brush)

public:

    SomeItem(QObject *parent, const QPoint place);
    ~SomeItem();

signals:

    void reDraw();
    //void dblClick();

public slots:

private:

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:

    static int count;

    enum Geometry
    {
        Rectangle = 0,
        Ellipse = 1,
        Star = 2
    };

    Geometry geometry;
    QBrush brush;


    const int size = 100;

    int x, y;
    QPoint bpoint;
    bool moving {false};


};

#endif // SOMEITEM_H
