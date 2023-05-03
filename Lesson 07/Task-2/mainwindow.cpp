#include "mainwindow.h"

#include <QBrush>
#include <QPoint>
#include <QGraphicsItem>

#include <QCoreApplication>


MainWindow::MainWindow(QWidget *parent)
    : QGraphicsView(parent)

{
    // создаем сцену
    scene = new QGraphicsScene(this);
    setScene(scene);

    // устанавливаем размеры сцены и видового окна
    scene->setSceneRect(0, 0, 800, 600);
    setFixedSize(800, 600);

    // устанавливаем флаги для перемещения элементов
    setDragMode(QGraphicsView::RubberBandDrag);

    // устанавливаем цвет фона сцены
    scene->setBackgroundBrush(QBrush(Qt::gray));

    setWindowTitle(APP_NAME);

}

MainWindow::~MainWindow()
{

}

void MainWindow::reDraw()
{
    scene->update();
    update();
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    // получаем элемент под курсором
    QGraphicsItem* back_item = itemAt(event->pos());

    if (event->button() == Qt::LeftButton)
    {
        if (!back_item)
        {
            QPoint point = mapToScene(event->pos()).toPoint();

            // создаем новый элемент и добавляем его на сцену
            SomeItem* item = new SomeItem (this, point);
            scene->addItem(item);
            connect (item, SIGNAL (reDraw()), this, SLOT(reDraw()));

            // снимаем выделение со всех объектов на сцене
            scene->clearSelection();
            // выделяем только что добавленный элемент
            item->setSelected(true);
        }

    }
    else if (event->button() == Qt::RightButton)
    {
        if (back_item)
        {
            // удаляем элемент со сцены
            scene->removeItem(back_item);
            delete back_item;
        }
    }

    QGraphicsView::mousePressEvent(event);
}
