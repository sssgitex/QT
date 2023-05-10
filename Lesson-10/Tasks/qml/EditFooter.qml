import QtQuick 2.9
import QtQuick.Controls 2.5

// Edit page footer

Rectangle
{
    id: root
    color: win.panelColor
    height: 50

    Button
    {
        id: btnRemoveItem
        text: "Remove"
//        visible: parent._index

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

        onClicked: removeItem()
    }

    Button
    {
        id: btnSaveItem
        text: "OK"

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


        onClicked: saveItem()
    }
}




