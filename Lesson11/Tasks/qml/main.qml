import QtQuick
import QtQuick.Controls
import QtQuick.Window

//import QtQuick.Layouts 1.12
//import QtQuick.Dialogs 1.3
//import Qt.labs.platform as NativeDialogs

ApplicationWindow
{
    id: win
    visible: true
    width: 480
    height: 640
    title: "ToDo list"

    //Readonly properties used as constants
    readonly property int defMargin: 10
    //Background color for header and footer panels
    readonly property color panelColor: "#17212B"
    //Background color message bubbles
    readonly property color bubbleColor: "#2b5278"
    //Page background color
    readonly property color bgColor: "#0E1621"
    //Color for text elements
    readonly property color textColor: "white"
    //Color for button elements
    readonly property color btnColor: "#007ACC"

    property bool isClosing: false


    header: MainHeader
    {
        title: "ToDo list"
    }

    StackView
    {
        id: stackView
        anchors.fill: parent
        initialItem: homePg

    }

    // ...

    function popPage()
    {
        stackView.pop();
        isClosing = false
    }

//    Keys.onBackPressed:
//    {
//        popPage()
//    }

//    Keys.onEscapePressed:
//    {
//        popPage()
//    }

    HomePage
    {
        id: homePg
    }

    MessagePage
    {
        id: msgPg
        visible: false
    }

    ClosePage
    {
        id: closePg
        visible: false
    }

    EditPage
    {
        id: editPg
        visible: false

    }

    EditPage
    {
        id: addPg
        visible: false
        _index: -1
   }


    onClosing: function(close)
    {
        if (taskModel.dirty() && !isClosing)
        {
            isClosing = true
            close.accepted = false;
            stackView.push(closePg)
        }
    }

/*
    NativeDialogs.MessageDialog
    {
        id: closeWarningDialog
        title: "Closing..."
        text: "You have unsaved changed. Do you want to save your changes?"
        buttons: NativeDialogs.MessageDialog.Yes | NativeDialogs.MessageDialog.No | NativeDialogs.MessageDialog.Cancel
        onYesClicked:
        {
            // Attempt to save the document
            taskModel.saveTasksToFile();
            Qt.quit();
        }
        onNoClicked:
        {
            // Close the window
            Qt.quit();
        }
        onRejected:
        {
            // Do nothing, aborting the closing of the window
        }
    }

    NativeDialogs.MessageDialog
    {
        id: informationDialog
        buttons: NativeDialogs.MessageDialog.Ok
    }
*/
}
