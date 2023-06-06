import QtQuick 2.14
import QtQuick.Window 2.14
import QtCharts 2.14
import ru.my.MyGraphs 1.0

Window
{
    id: _root
    width:   640
    height:  480
    visible: true

    MyGraphs
    {
        id: _graphs
    }

    Item
    {
        id: _item
        anchors.fill: parent
        ChartView
        {
            title: "Диаграмма рассеяния"
            anchors.fill: parent
            antialiasing: true
            ScatterSeries
            {
                id: _scatterSeries
                name: "Набор данных 1"
                axisX: ValueAxis { min: 0.0; max: 220.0 }
                axisY: ValueAxis { min: 0.0; max: 30.0 }


            }

            LineSeries
            {
                id: _lineSeries
                name: "Уравнения прямой"
            }
        }
    }

    Component.onCompleted: setNewPoints();

    function setNewPoints()
    {

        _scatterSeries.clear()
        for(var i = 0; i < _graphs.length; i++)
        {
            _scatterSeries.append(_graphs.X[i], _graphs.Y[i])
        }

        _lineSeries.clear()
        for(var y = 0; y < _graphs.lengthLine; y++)
        {
            _lineSeries.append(_graphs.XsLine[y], _graphs.YsLine[y])
        }
    }
}
