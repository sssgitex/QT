import QtQuick 2.12
import QtQuick.Controls 2.12

// Message page footer

Rectangle
{
    id: root
    color: win.panelColor
    height: 50

    Button
    {
        id: btnBack
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

        onClicked: goBack()

    }
}




