import QtQuick
import QtQuick.Controls
import QtQml


// Edit page

Page
{
    id: root
    spacing: defMargin

    signal removeItem()
    signal saveItem()

    property var _model
    property int _index
    property alias _name: nameField.text
    property alias _progress: slider.value
    property alias _date: dateField.text

    Keys.onEscapePressed:
    {
        popPage()
    }

    footer : EditFooter
    {}

    background: Rectangle
    {
        color: bgColor
    }

    // Name input
    Rectangle
    {
        id: _rect
        //anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - defMargin * 4
        anchors.top: parent.top
        anchors.bottom: slider.top
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.leftMargin: defMargin * 2
        anchors.rightMargin:defMargin * 2
        anchors.topMargin: defMargin * 4
        anchors.bottomMargin: defMargin * 4

        border.color: win.btnColor
        border.width: 2
        radius: 15

        TextInput
        {
            id: nameField
            width: _rect.width
            anchors.fill: _rect
            anchors.margins: defMargin
            wrapMode: TextInput.WordWrap //.WrapAnywhere

            //font.bold: true
            font.pointSize: 15

            //color: "white"
            //textColor: "black"

            maximumLength: 150
            //horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            focus: true
        }
    }


    Slider
    {
        id: slider

        //anchors.centerIn: parent
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: defMargin

        height: 30

        from: 0
        to: 10
        stepSize: 1

        background: Rectangle
        {
            x: slider.leftPadding
            y: slider.topPadding + slider.availableHeight / 2 - height / 2
            //implicitWidth: 200
            implicitHeight: 4
            width: slider.availableWidth
            height: implicitHeight
            radius: 2
            color: win.textColor//win.bubbleColor

            Rectangle
            {
                width: slider.visualPosition * parent.width
                height: parent.height
                color: "red"
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
            color: "red"//slider.pressed ? "#f0f0f0" : "#f6f6f6"
            border.color: "red"//win.textColor//win.bubbleColor
        }

    }

    Text
    {
        id: sliderValue
        text: (slider.value * 10) + "%"
        //wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        anchors.top: slider.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: defMargin

        font.bold: true
        font.pointSize: 14
        color: "red"//win.bubbleColor

    }


    // Date input
    TextField
    {
        id: dateField

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        color: "black"
        placeholderTextColor: "grey"
        font.pointSize: 15
        placeholderText: "DD.MM.YYYY"
        anchors.margins: defMargin * 2

        anchors.top: sliderValue.bottom
        anchors.horizontalCenter: parent.horizontalCenter


        maximumLength: 10

        width: 140
        height: 35

        //inputMask: "00.00.0000"
        validator: RegularExpressionValidator { regularExpression: /^(\d{1,2})\.(\d{1,2})\.(\d{4})$/ }

        background: Rectangle
        {
            border.color: win.btnColor
            border.width: 2
            radius: 5
        }
    }


    onRemoveItem:
    {
        if (_index > -1)
        {
            taskModel.removeTask(_index)
        }
        popPage();
    }

    onSaveItem:
    {
        if (containsDigitOrLetter(_name) && checkDate())
        {
            if (_index == -1)
            {
                taskModel.addTask(-1, _name, getDate(_date), parseInt(_progress))
                //taskModel.addTaskFromString(_name + "," + _date + "," + _progress)
            }
            else
            {
                _model.name = _name
                _model.deadline = getDate(_date)
                _model.progress = parseInt(_progress)
            }
            popPage();
        }
        else
        {
            msgPg.text = "Error!\nThe source data is not correct!"
            stackView.push(msgPg)
        }

    }

    function containsDigitOrLetter(myVar)
    {
        var regex = /[0-9a-zA-Z]/;
        return regex.test(myVar);
    }

    function checkDate()
    {
        if (dateField.acceptableInput)
        {
            var parsedValue = getDate()
            if (!isNaN(parsedValue))
            {
                if (_index == -1)
                {
                    var currentDate = new Date();
//                    console.log("currentDate " + currentDate)
//                    console.log("parsedValue " + parsedValue)
                    if (parsedValue > currentDate)
                    {
                        return true;
                    }

                }
                else
                { return true; }
            }

        }

        return false;
    }

    function getDate()
    {
        var dateArray = _date.split(".");
        var value = new Date(dateArray[2], dateArray[1] - 1, dateArray[0]);
        return value;
    }

}
