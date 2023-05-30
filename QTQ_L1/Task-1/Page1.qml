import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 2.14

Page
{
    id: root

    font.pointSize: 15

    property alias _name: name.text
    property alias _age: slider.value
    property alias _hobby: hobby.text
    property alias _man: man.checked
    property alias _women: women.checked
    property alias _edu: _education.currentTextValue
    property alias _town: town.text
    property alias _about: aboutme.text

    Rectangle
    {
        anchors.fill: parent
        opacity: 0.5
        Image
        {
            anchors.fill: parent
            source: bgImage

        }
    }

    header: Header
    {
        id: _header
        title: "Обо мне:"

    }

    Column
    {
        id: column
        anchors.fill: parent
        anchors.centerIn: parent
        clip: true
        padding: defMargin
        spacing: defMargin

        TextField
        {
            id:name
            anchors.horizontalCenter: parent.horizontalCenter
            placeholderText: "Ваше имя"
            width: parent.width / 2
            color: textColor
            opacity: 0.8
            maximumLength: 150
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            focus: true

            background: Rectangle
            {
                color: bubbleColor
            }
        }

        RowLayout
        {

            anchors.horizontalCenter: parent.horizontalCenter
            RadioButton
            {
                id: man
                checked: true
                //text: "Мужской"

                indicator: Rectangle
                {
                    implicitWidth: 26
                    implicitHeight: 26
                    x: man.leftPadding
                    y: parent.height / 2 - height / 2
                    radius: 13
                    color : bubbleColor


                    Rectangle
                    {
                        width: 14
                        height: 14
                        x: 6
                        y: 6
                        radius: 7
                        color: man.down ? bubbleColor : textColor
                        visible: man.checked
                    }
                }

                contentItem: Text
                {
                    text: "Мужской"

                    font.bold: true
                    font.pointSize: 15

                    opacity: enabled ? 1.0 : 0.3
                    color: bubbleColor

                    verticalAlignment: Text.AlignVCenter
                    leftPadding: man.indicator.width + man.spacing
                }
            }


            RadioButton
            {
                id: women


                indicator: Rectangle
                {
                    implicitWidth: 26
                    implicitHeight: 26
                    x: women.leftPadding
                    y: parent.height / 2 - height / 2
                    radius: 13
                    color : bgColor


                    Rectangle
                    {
                        width: 14
                        height: 14
                        x: 6
                        y: 6
                        radius: 7
                        color: women.down ? bubbleColor : textColor
                        visible: women.checked
                    }
                }

                contentItem: Text
                {
                    text: "Женский"

                    font.bold: true
                    font.pointSize: 15

                    opacity: enabled ? 1.0 : 0.3
                    color: bubbleColor

                    verticalAlignment: Text.AlignVCenter
                    leftPadding: women.indicator.width + women.spacing
                }
            }
        }

        Item
        {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width / 3 * 2

            height: 30

            Label
            {
                id: ageLabel

                text: "Возраст: " + slider.value
                color: bubbleColor
                font.bold: true

                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight


            }

            Slider
            {
                id: slider
                value: 18
                stepSize: 1
                from: 18
                to: 100
                anchors.margins: defMargin * 2
                anchors.left: ageLabel.right
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter

                background: Rectangle
                {
                    x: slider.leftPadding
                    y: slider.topPadding + slider.availableHeight / 2 - height / 2
                    implicitWidth: 200
                    implicitHeight: 8
                    width: slider.availableWidth
                    height: implicitHeight
                    radius: 2
                    color: bgColor

                    Rectangle
                    {
                        width: slider.visualPosition * parent.width
                        height: parent.height
                        color: bubbleColor
                        radius: 2
                    }
                }

                handle: Rectangle
                {
                    x: slider.leftPadding + slider.visualPosition * (slider.availableWidth - width)
                    y: slider.topPadding + slider.availableHeight / 2 - height / 2
                    implicitWidth: 26
                    implicitHeight: 26
                    radius: 13
                    color: slider.pressed ? "#f0f0f0" : "#f6f6f6"
                    border.color: "#bdbebf"
                }
            }
        }

        Education
        {
            id: _education
        }




        TextField
        {
            id: town
            anchors.horizontalCenter: parent.horizontalCenter
            placeholderText: "Город"
            width: parent.width / 2
            color: textColor
            opacity: 0.8
            maximumLength: 50
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            background: Rectangle
            {
                color: bubbleColor

            }
        }

        TextField
        {
            id: hobby
            anchors.horizontalCenter: parent.horizontalCenter
            placeholderText: "Хобби"
            width: parent.width / 2
            color: textColor
            opacity: 0.8
            maximumLength: 100
            verticalAlignment: Text.AlignVCenter



            background: Rectangle
            {
                color: bubbleColor

            }
        }

        TextField
        {
            id: aboutme
            anchors.horizontalCenter: parent.horizontalCenter
            placeholderText: "О себе"
            width: parent.width / 2


            color: textColor
            opacity: 0.8
            maximumLength: 300
            verticalAlignment: Text.AlignVCenter

            background: Rectangle
            {
                color: bubbleColor

            }
        }

    }

    footer : Rectangle
    {
        id: _footer

        width: parent.width
        height: 50


        Rectangle
        {
            anchors.fill: parent
            opacity: 0.5

            Image
            {
                anchors.fill: parent
                source: "qrc:/img/back3.png"

            }
        }

        Button
        {
            id: btnNext
            text: "Next > "

            anchors.left: _footer.horizontalCenter
            anchors.right: _footer.right
            anchors.verticalCenter: _footer.verticalCenter
            anchors.margins: defMargin
            anchors.leftMargin: defMargin / 2
            font.bold: true
            font.pixelSize: 15

            background: Rectangle
            {
                opacity: 0.5
                color: bgColor
                radius: 5
            }

            onClicked:
            {
                stackView.push(page2)
            }
        }

    }

}
