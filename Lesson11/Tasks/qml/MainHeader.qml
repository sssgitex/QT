import QtQuick 2.9
import QtQuick.Controls 2.5
//import QtQuick.Layouts 1.12

// Main page header

Rectangle
{
    id: root
    property alias title: lblTitle.text
    property alias avatarColor: imgAvatar.color
    property alias textColor: lblTitle.color
    color: win.panelColor
    height: 60

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
        color: win.bubbleColor

        // Image circle
        Image
        {
            id: imgCircle
            source: "qrc:/qml/checklist.png" // указывает путь к файлу в ресурсах
            fillMode: Image.PreserveAspectFit // режим заполнения изображения
            anchors.fill: parent // заполнение родительского элемента
        }

    }

    // Title label
    Label
    {
        id: lblTitle
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        color: win.textColor
        font.pixelSize: root.height*0.4
    }

    Button
    {
        //id: btnBack
        text: " < Back "
        palette.buttonText: win.btnColor
        visible: (stackView.depth > 1)

        anchors.right: root.right
        anchors.verticalCenter: root.verticalCenter
        anchors.margins: defMargin * 2
        font.pixelSize: 15

        background: Rectangle
        {
            color: win.panelColor
            radius: 5
            border.color: win.btnColor
            border.width: 1
        }

        onClicked:
        {
            popPage()
        }

    }
}
