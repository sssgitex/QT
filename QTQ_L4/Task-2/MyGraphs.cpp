#include "MyGraphs.h"
#include <QtMath>

MyGraphs::MyGraphs(QObject *parent) : QObject (parent)
{
    a_X <<  7  << 31 <<  61 <<  99 <<  129 <<  178 <<  209;
    a_Y <<  13 << 10 <<  9  <<  10 <<  12  <<  20  <<  26;

    linearDependency();
}

void MyGraphs::linearDependency()
{


    a_length = a_X.length() < a_Y.length() ? a_X.length() :  a_Y.length();
    qDebug() << "Length:" << a_length;
    double sumX  = 0;
    double sumY  = 0;
    double sumXY = 0;
    double sumXX = 0;

    for (int i = 0; i < a_length; i++)
    {
        sumX  += a_X[i];
        sumY  += a_Y[i];
        sumXY += a_X[i] * a_Y[i];
        sumXX += a_X[i] * a_X[i];
    }

    double det = 0;
    double err = 0;
    det = sumXX* a_length - sumX * sumX;

    a = (sumXY * a_length - sumY * sumX) / det;
    b = (sumXX * sumY - sumXY * sumX) / det;

    for (int i = 0; i < a_length; i++)
        err += qPow((a_Y[i] - (a * a_X[i] + b)), 2);

    if (b > 0)
        createLine(true);
    else
        createLine(false);


}

void MyGraphs::createLine(bool b/*>0*/)
{
    qreal h   = 1;
    qreal min = 1;
    qreal max = 250 + h;
    qreal tempX = min;

    a_lengthLine = (max - min) / h + 2;

    for (int i = 0; i < a_lengthLine; ++i)
    {
        if (tempX <= max)
        {
            a_XsLine.push_back (tempX);

            if (b)
               a_YsLine.push_back ((a * tempX) + b);
            else
               a_YsLine.push_back ((a * tempX) - b);
        }
        tempX += h;
    }

}





















