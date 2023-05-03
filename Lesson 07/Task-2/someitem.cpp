
#include "someitem.h"

#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QColor>
#include <QPainterPath>

int SomeItem::count = 0;

SomeItem::SomeItem (QObject *parent, const QPoint place)
    : QObject(parent), QGraphicsItem()
    , x(place.x()), y(place.y())

{
    bpoint = place;

    setFlag(ItemIsMovable, true);

    // установка цвета и формы фигуры
    brush.setColor( QColor::fromRgb(QRandomGenerator::global()->generate()) );
    brush.setStyle( Qt::BrushStyle::SolidPattern ); // Полностью закрашивать
    geometry = static_cast<Geometry>(count % 3);

    // увеличиваем счетчик
    count++;
}

SomeItem::~SomeItem()
{
    // уменьшаем счетчик
    count--;
}

QRectF SomeItem::boundingRect() const
{
    int width{size}, higth{0};

    if (geometry == Geometry::Ellipse || geometry == Geometry::Rectangle)
    {
        higth = size / 2;
    }
    else if  (geometry == Geometry::Star)
    {
        higth = size;
    }

    //return QRectF (x - width/2, y - higth/2, width, higth);
    return QRectF (x, y, width, higth);
}

void SomeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(brush);

    if (geometry == Geometry::Ellipse)
    {
        int width{size}, higth{size / 2};
        //QRectF m_place(x - width/2, y - higth/2, width, higth);
        QRectF m_place(x, y, width, higth);
        painter->drawEllipse(m_place);
    }
    else if (geometry == Geometry::Rectangle)
    {
        int width{size}, higth{size / 2};
        //QRectF m_place(x - width/2, y - higth/2, width, higth);
        QRectF m_place(x, y, width, higth);
        painter->drawRect(m_place);
    }
    else if  (geometry == Geometry::Star)
    {
        int width{size}, higth{size};
        //QRectF m_place(x - width/2, y - higth/2, width, higth);
        QRectF m_place(x, y, width, higth);


        /*
        QPointF center = m_place.center();

        qreal r = qMin(m_place.width(), m_place.height()) / 2;

        QPolygonF polygon;

        for (int i = 0; i < 5; ++i)
        {
            qreal angle = 2 * M_PI * i / 5 + M_PI / 2;
            QPointF point = center + r * QPointF(qCos(angle), -qSin(angle));
            polygon.append(point);
        }

        painter->drawPolygon(polygon);
        */


        // вычисляем центр элемента
        QPointF center = m_place.center();

        // вычисляем параметры звезды
        qreal r_star = qMin(width, higth) / 2;
        qreal r_inner = r_star * 0.382; // внутренний радиус

        // вычисляем вершины звезды
        QPolygonF star;
        for (int i = 0; i < 5; ++i)
        {
            qreal angle = 2 * M_PI * i / 5 + M_PI / 2;
            QPointF point_outer = center + r_star * QPointF(qCos(angle), -qSin(angle));
            QPointF point_inner = center + r_inner * QPointF(qCos(angle + M_PI / 5), -qSin(angle + M_PI / 5));
            star.append(point_outer);
            star.append(point_inner);
        }

        // рисуем звезду
        painter->drawPolygon(star);
    }

    Q_UNUSED(option)
    Q_UNUSED(widget)
}


void SomeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Левая кнопка, режим перемещения
    if (event->button() == Qt::LeftButton)
    {
        // Флаг активности перемещения
        moving = true;
        // Запоминаем начальные координаты мыши
        bpoint = event->pos().toPoint();
    }
}


void SomeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // Снимаем флаг на перемещение
        moving = false;
        emit reDraw();
    }
}

void SomeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    // Если активен флаг перемещения
    if (moving)
    {
        // Вычисляем вектор смещения
        QPoint p = event->pos().toPoint() - bpoint;
        x += p.x();
        y += p.y();
        // Запоминаем новую позицию курсора
        bpoint = event->pos().toPoint();
        // Переотрисовываем
        emit reDraw();
    }
}




