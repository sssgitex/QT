#include "MyGraphs.h"
#include <QtMath>

MyGraphs::MyGraphs(QObject *parent)
    : QObject(parent)
    , a_Xmin(0)
    , a_Xmax(5)
    , a_Ymin(-5)
    , a_Ymax(5.0)
{
    a_length = static_cast<int>(5.0f/0.1f) + 1;
    qreal value = 0;

    std::generate_n(std::back_inserter(_X), a_length, [&value]() {
        qreal result = value;
        value += 0.1;

        return result;
    });

}

void MyGraphs::y_sinX()
{

    _Y.clear();
    for(const auto x: _X)
        _Y.push_back(qSin(x));
    minmaxY();
}

void MyGraphs::y_X()
{

    _Y.clear();
    for(const auto x: _X)
        _Y.push_back(x);
    minmaxY();
}

void MyGraphs::y_modX()
{

    _Y.clear();
    for(const auto x: _X)
    {
        auto t = x - 2.5;
        if(t<0)
            t *= - 1;
        _Y.push_back(t);
    }
    minmaxY();
}

void MyGraphs::y_sqrtX()
{

    _Y.clear();
    for(const auto x: _X)
        _Y.push_back(qSqrt(x));
    minmaxY();
}

void MyGraphs::y_log2X()
{

    _Y.clear();
    for(const auto x: _X)
        _Y.push_back(log2(x));

    minmaxY();
}

void MyGraphs::minmaxY()
{
    auto minmax = std::minmax_element(std::begin(_Y), std::end(_Y));
    a_Ymin = *(minmax.first);
    a_Ymax = *(minmax.second);

}
