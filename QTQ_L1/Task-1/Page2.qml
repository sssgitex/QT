import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 2.14

Page
{
    id: root

    font.pointSize: 15

    readonly property string _age: age.currentText
    property alias _edu: _education.currentTextValue

    Keys.onEscapePressed:
    {
        popPage()
    }

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
        title: "Я ищу:"

    }

    Column
    {
        id: column
        anchors.fill: parent
        anchors.centerIn: parent
        clip: true
        padding: defMargin
        spacing: defMargin


        Label
        {
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            width: parent.width / 2
            color: bubbleColor

            text: page1._man ? "Женщин" : "Мужчин"
            wrapMode: Text.WordWrap
            font.bold: true
        }


        RowLayout
        {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width / 3 * 2
            spacing: defMargin

            Label
            {

                text: "В возрасте: "
                color: bubbleColor
                font.bold: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            ComboBox
            {
                id: age
                model: [" от 18 до 25 ", " от 26 до 30 ", " старше 30 "]
                spacing: defMargin
                Layout.fillWidth: true
                opacity: 0.8

                delegate: ItemDelegate
                {
                    width: age.width
                    contentItem: Text
                    {
                        text: age.textRole
                                ? (Array.isArray(age.model) ? modelData[age.textRole] : model[age.textRole])
                                : modelData
                        color: textColor
                        font: age.font
                        elide: Text.ElideRight
                        verticalAlignment: Text.AlignVCenter
                    }
                    highlighted: age.highlightedIndex === index
                }

                background: Rectangle
                {
                    color: bubbleColor
                    implicitWidth: 120
                    implicitHeight: 40
                    radius: 5
                }

            }
        }

        Education
        {
            id: _education
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
            id: btnEnd
            text: " Finish "

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
                Qt.quit()
            }

        }


    }

}
