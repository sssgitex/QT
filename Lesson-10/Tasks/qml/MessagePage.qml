import QtQuick
import QtQuick.Controls

// Message page

Page
{
    id: root
    //anchors.fill: parent

    property alias text: msgText.text
    signal goBack()

    Keys.onEscapePressed:
    {
        goBack()
    }

    footer : MessageFooter
    {}

    background: Rectangle
    {
        color: bgColor
    }

    Text
    {
        id: msgText
        anchors.centerIn: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WordWrap

        anchors.margins: defMargin
        font.pointSize: 16
        color: win.textColor

    }

    onGoBack:
    {
        popPage();
    }

}
