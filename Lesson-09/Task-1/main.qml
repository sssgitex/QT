import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 300
    height: 480
    title: qsTr("ToDo list")

    //padding: 10

    ToDoList
    {

        //center around parent
        anchors.centerIn: parent
        anchors.fill: parent
        anchors.margins: 10

    }
}
