import QtQuick 2.12
import QtQuick.Controls 2.12

// Home page footer

Rectangle
{
    id: root
    color: win.panelColor
    height: 50

    Button
    {
        id: btnAdd
        text: "Add"

        anchors.right: root.horizontalCenter
        anchors.left: root.left
        anchors.verticalCenter: root.verticalCenter
        anchors.margins: defMargin
        anchors.rightMargin: defMargin / 2
        font.pixelSize: 18

        background: Rectangle
            {
                color: win.btnColor
                radius: 2
            }

        onClicked: addNew()
    }

    Button
    {
        id: btnSave
        text: "Save"

        anchors.left: root.horizontalCenter
        anchors.right: root.right
        anchors.verticalCenter: root.verticalCenter
        anchors.margins: defMargin
        anchors.leftMargin: defMargin / 2
        font.pixelSize: 18

        background: Rectangle
        {
            color: win.btnColor
            radius: 2
        }

        onClicked: saveAll()
    }
}




