import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtCharts 2.14
import QtQuick.Layouts 2.14
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

    function resetMatrix(chart)
    {

        lineSeries1.clear();
        lineSeries2.clear();
        lineSeries3.clear();
        lineSeries4.clear();
        lineSeries5.clear();

        switch(chart)
        {
            case(0):
                _graphs.y_sinX();
                print("y=sin(x)")
                break;
            case(1):
                _graphs.y_X();
                print("y=x")
                break;
            case(2):
                _graphs.y_modX();
                print("y=|x-2.5|")
                break;
            case(3):
                _graphs.y_sqrtX();
                print("y=x^2")
                break;
            case(4):
                _graphs.y_log2X();
                print("y = log2(x)")
                break;
        }

        var x = _graphs.get_X()
        var y = _graphs.get_Y()
        var l = _graphs.length

        for(var i = 0; i < _graphs.length; i++)
        {
            lineSeries1.append(x[i],y[i]);
            lineSeries2.append(x[i],y[i]);
            lineSeries3.append(x[i],y[i]);
            lineSeries4.append(x[i],y[i]);
            lineSeries5.append(x[i],y[i]);
        }

    }

    Item
    {
        id: _item
        anchors.fill: parent

        ColumnLayout
        {
            anchors.fill: parent
            spacing: 10
            TabBar
            {
                id: _bar

                Layout.fillWidth: true

                Repeater
                {
                    id: _repeater
                    model: ["Y = Sin(X)", "Y = X", "Y = |X - 2.5|", "Y = X^2", "Y = log2(X)"]

                    TabButton
                    {
                        text: modelData
                        onClicked: resetMatrix(_bar.currentIndex);
                    }
                }
            }

            StackLayout
            {
                id: _stack
                Layout.fillHeight: true
                Layout.fillWidth: true
                currentIndex: _bar.currentIndex

                ChartView
                {
                    title: "Y = Sin(X)"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    legend.alignment: Qt.AlignBottom
                    antialiasing: true
                    LineSeries
                    {
                        id: lineSeries1
                        name:  "Y = Sin(X)"
                        width: 3
                        color: _graphs.color
                        axisX: ValueAxis { min: _graphs.Xmin; max: _graphs.Xmax } // Ось OX
                        axisY: ValueAxis { min: _graphs.Ymin; max: _graphs.Ymax } // Ось OY
                    }
                }

                ChartView
                {
                    title: "Y = X"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    legend.alignment: Qt.AlignBottom
                    antialiasing: true
                    LineSeries
                    {
                        id: lineSeries2
                        name: "Y = X"
                        width: 3
                        color: _graphs.color
                        axisX: ValueAxis { min: _graphs.Xmin; max: _graphs.Xmax } // Ось OX
                        axisY: ValueAxis { min: _graphs.Ymin; max: _graphs.Ymax } // Ось OY
                    }
                }

                ChartView
                {
                    title: "Y = |X - 2.5|"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    legend.alignment: Qt.AlignBottom
                    antialiasing: true
                    LineSeries
                    {
                        id: lineSeries3
                        name: "Y = |X - 2.5|"
                        width: 3
                        color: _graphs.color
                        axisX: ValueAxis { min: _graphs.Xmin; max: _graphs.Xmax } // Ось OX
                        axisY: ValueAxis { min: _graphs.Ymin; max: _graphs.Ymax } // Ось OY
                    }
                }

                ChartView
                {
                    title: "Y = X^2"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    legend.alignment: Qt.AlignBottom
                    antialiasing: true
                    LineSeries
                    {
                        id: lineSeries4
                        name: "Y = X^2"
                        width: 3
                        color: _graphs.color
                        axisX: ValueAxis { min: _graphs.Xmin; max: _graphs.Xmax } // Ось OX
                        axisY: ValueAxis { min: _graphs.Ymin; max: _graphs.Ymax } // Ось OY
                    }
                }

                ChartView
                {
                    title: "Y = log2(X)"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    legend.alignment: Qt.AlignBottom
                    antialiasing: true
                    LineSeries
                    {
                        id: lineSeries5
                        name: "Y = log2(X)"
                        width: 3
                        color: _graphs.color
                        axisX: ValueAxis { min: _graphs.Xmin; max: _graphs.Xmax } // Ось OX
                        axisY: ValueAxis { min: _graphs.Ymin - 5; max: _graphs.Ymax + 50 } // Ось OY
                    }
                }


            }
        }

        Component.onCompleted: resetMatrix(0)
    }
}
