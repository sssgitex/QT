import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MyComboBox{
        width: 200
        anchors.centerIn: parent
        model: ["First","Second","Third"]
    }
}
