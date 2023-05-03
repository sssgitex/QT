#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define APP_NAME "Lesson 07. Task 2."

#include <QGraphicsScene>
#include <QGraphicsView>

#include "someitem.h"



#include <QMouseEvent>

class MainWindow : public QGraphicsView
{

    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:

    // переопределяем обработчик щелчков мыши
    virtual void mousePressEvent(QMouseEvent* event) override;

private slots:
    void reDraw();

private:

    QGraphicsScene* scene;


};

#endif // MAINWINDOW_H
