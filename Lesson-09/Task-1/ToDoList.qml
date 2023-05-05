
import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
//import QtQuick.Controls.Styles 1.4

import ToDo 1.0

// компоновка в один столбец
ColumnLayout
{

    // Frame используется для компоновки логической группы элементов управления
    Frame
    {
        id: _frame1

        //anchors.fill: parent
        Layout.fillHeight: true
        Layout.fillWidth: true

        //spacing: 10

        /*
        ListView требует параметры:
            - size: определяет область, которая будет использоваться
            - model
            - delegate
        Модель Listview является источником данных,используется для создания элементов
        */

        ListView
        {
            id: _list1

            implicitWidth: 250
            implicitHeight: 250

            clip: true
            anchors.fill: parent
            spacing: 5

            model: ToDoModel
            {
                list: toDoList
            }
            /*!
            model: ListModel {
                        ListElement {
                        each element is called a role, it indicates
                        to the model which type of data is being
                        referred to

                            done: true
                            description: "Wash the car"
                        }
                        ListElement {
                            done: false
                            description: "Fix the sink"
                        }
                    }
            */

            // шаблон того, как будет выглядеть каждый элемент списка
            delegate: ColumnLayout
            {
                id: _column
                spacing: 10

                Column
                {
                    spacing: 2
                    Row
                    {
                        spacing: 2
                        TextField
                        {
                            id: _description
                            text: model.description
                            implicitWidth: 230
                            onEditingFinished: model.description = text
                        }

                        Button
                        {
                            text: "Delete"
                            implicitWidth: 45
                            implicitHeight: _description.implicitHeight
                            //anchors.right: parent.right
                            onClicked: toDoList.removeItem(index) //.removeItem(_list1.currentIndex)
                        }
                    }

                    Row
                    {
                        spacing: 2
                        TextField
                        {
                            id: _deadline
                            implicitWidth: 70
                            implicitHeight: _description.implicitHeight
                            //Layout.alignment: Qt.AlignLeft

                            placeholderText: "dd.mm.yyyy"
                            onEditingFinished: model.deadLine = text
                        }

                        Slider
                        {
                            id: _progress
                            from: 0
                            to: 10
                            stepSize: 1

                            implicitWidth: 200
                            implicitHeight: _description.implicitHeight

                            value: model.progress
                            onValueChanged: model.progress = value
                        }

                    }
                }

            }

        }
    }

    // grid with one row
    RowLayout
    {
        Button
        {
            text: qsTr("Add new item")
            Layout.fillWidth: true
            anchors.margins: 5

            onClicked: {toDoList.appendItem()
                _list1.currentIndex = _list1.count - 1
                _list1.positionViewAtEnd();
            }
        }

//      Button
//      {
//          text: qsTr("Remove completed")
//          onClicked: toDoList.removeCompletedItems()
//          Layout.fillWidth: true
//          anchors.margins: 5
//       }
    }

}
