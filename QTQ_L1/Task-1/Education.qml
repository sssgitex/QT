import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 2.14

RowLayout
{

    property string currentTextValue: ""

    anchors.horizontalCenter: parent.horizontalCenter
    width: parent.width / 3 * 2
    spacing: defMargin



    Label
    {
        //width: parent / 2
        text: "Образование: "
        color: bubbleColor
        font.bold: true
        Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
    }

    ComboBox
    {
        id: combo
        model: ["В процессе", "Начальное", "Высшее", "Отсутвует"]
        spacing: defMargin
        Layout.fillWidth: true

        delegate: ItemDelegate
        {
            width: combo.width
            contentItem: Text
            {
                text: combo.textRole
                        ? (Array.isArray(combo.model) ? modelData[combo.textRole] : model[combo.textRole])
                        : modelData
                color: textColor
                font: combo.font
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
            }
            highlighted: combo.highlightedIndex === index
        }

        background: Rectangle
        {
            opacity: 0.8
            color: bubbleColor
            implicitWidth: 120
            implicitHeight: 40
            radius: 5
        }


        onCurrentTextChanged:
        {


            currentTextValue = combo.currentText
        }
    }
}
