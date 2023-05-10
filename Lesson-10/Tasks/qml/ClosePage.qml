import QtQuick
import QtQuick.Controls

// Close page

Page
{
    id: root

    signal goExit()
    signal goSaveAndExit()

    Keys.onEscapePressed:
    {
        popPage();
    }


    footer : CloseFooter
    {}

    background: Rectangle
    {
        color: bgColor
    }

    Text
    {
        id: msgText
        text: "You have unsaved changed.\nDo you want to save your changes before exit?"

        anchors.centerIn: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WordWrap

        anchors.margins: defMargin
        font.pointSize: 16
        color: win.textColor

    }

    onGoExit:
    {
        Qt.quit()
    }
    onGoSaveAndExit:
    {
        // Attempt to save the document
        taskModel.saveTasksToFile();
        Qt.quit()
    }

}
