import QtQuick 2.14
import QtQuick.Controls 2.14

// Page 1

Rectangle
{
    id: root
    property alias title: lblTitle.text
    property alias textColor: lblTitle.color

    height: 60

    Rectangle
    {
        anchors.fill: parent
        opacity: 0.5

        Image
        {
            anchors.fill: parent
            source: "qrc:/img/back1.png"

        }
    }

    // Avatar circle
    Rectangle
    {
        id: imgAvatar
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.margins: defMargin
        anchors.leftMargin: defMargin * 2

        height: root.height*0.8
        width: height
        radius: height/2

        color: "transparent"
        border.color: bgColor
        border.width: 3


        Image
        {
            id: imgCircle
            source: "qrc:/img/icon.png"
            fillMode: Image.PreserveAspectFit
            anchors.fill: parent
        }

    }


    Label
    {
        id: lblTitle
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        color: bubbleColor//textColor
        font.pixelSize: root.height*0.4
        font.bold: true
        background: Rectangle
        {
            color: "transparent"

        }
    }

    Button
    {
        id: btnBack
        text: " < Back "
        palette.buttonText: main.textColor
        visible: (stackView.depth > 1)


        anchors.right: root.right
        anchors.verticalCenter: root.verticalCenter
        anchors.margins: defMargin * 2
        font.pixelSize: 15

        background: Rectangle
        {
            opacity: 0.5
            color: bgColor
            radius: 5
            border.color: bgColor
            border.width: 2
        }

        onClicked:
        {
            popPage()
        }

    }
}
