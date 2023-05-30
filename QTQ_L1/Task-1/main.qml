import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
//import QtQuick.Layouts

ApplicationWindow
{
    id: main
    visible: true
    width: 640
    height: 480
    title: qsTr("Lesson 02. Task 1.")


    readonly property int defMargin: 10




    readonly property color bubbleColor: "#2b5278"


    readonly property color textColor: "white"

    readonly property color bgColor: "#D0037F"

    readonly property string bgImage: "qrc:/img/back2.png"

    StackView
    {
        id: stackView
        anchors.fill: parent
        initialItem: page1
    }

    Page1
    {
        id: page1
        visible: true
    }

    Page2
    {
        id: page2
        visible: false
    }


    function popPage()
    {
        stackView.pop();
    }

    function printData()
    {
        console.log("==============");

        console.log("name: " + page1._name);
        console.log("age: " + page1._age);
        console.log("sex: " + page1._man ? "man" : "women");
        console.log("hobby: " + page1._hobby);
        console.log("education: " + page1._edu);
        console.log("town: " + page1._town);
        console.log("about self: " + page1._about);
        console.log("looking for...");

        console.log("sex: " + page1._man ? "women" : "man");
        console.log("age: " + page2._age);
        console.log("education: " + page2._edu);

    }

    onClosing: function(close)
    {
        printData()

    }

}
