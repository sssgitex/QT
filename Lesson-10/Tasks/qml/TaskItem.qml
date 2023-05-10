import QtQuick 2.0

// Task delegate item

Item
{
    id: root
    property alias name: lblName.text
    property alias deadline: lblDeadline.text
    property alias backgroundColor: rectBubble.color
    property alias textColor: lblName.color
    property alias font: lblName.font
    property int parts // количество частей для окрашивания прямоугольника
    readonly property int _size: lblName.contentHeight + 2*defMargin + lblDeadline.contentHeight

    signal clickedItem ()

    // Properties from main.qml are available here
    height: _size

    Rectangle
    {
        id: rectBubble
        color: win.bubbleColor
        anchors.fill: parent
        radius: 5

        Text
        {
            id: lblName
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.horizontalCenter
            anchors.margins: defMargin
            font.pointSize: 11
            color: win.textColor
            wrapMode: Text.WordWrap
        }

        // Прямоугольник для окраски
        Rectangle
        {
            id: rectBar
            color: "white"
            height: 2
            width: parent.width / 2
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.margins: defMargin
            clip: true

            // Окрашиваемые части прямоугольника
            Repeater
            {
                id: partsRepeater
                model: 10
                delegate: Rectangle
                {
                    width: rectBar.width / partsRepeater.count
                    height: rectBar.height
                    x: index * width
                    color: index < root.parts ? "red" : "white"
                }
            }
        }

        Text
        {
            id: lblDeadline
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: defMargin/2
            color: textColor
        }

        MouseArea
        {
            anchors.fill: parent
            hoverEnabled: true

            onEntered:
            {
                rectBubble.anchors.margins -= defMargin/2
                rectBubble.width += defMargin/2;
                rectBubble.height += defMargin/2;
            }

            onExited:
            {
                rectBubble.anchors.margins += defMargin/2
                rectBubble.width -= defMargin/2
                rectBubble.height -= defMargin/2;

                rectAnimation.from = rectBubble.color;
                rectAnimation.to = win.bubbleColor;
                rectAnimation.start();
            }

            onClicked:
            {
                clickedItem ()
            }

//          onPressed:
//          {
//              rectBubble.color = win.bubbleColor.darker(0.5)
//          }

//          onReleased:
//          {
//              rectBubble.color = win.bubbleColor
//          }

            onPressed:
            {
                rectAnimation.from = win.bubbleColor
                rectAnimation.to = win.bubbleColor.darker(0.5)
                rectAnimation.start();
            }

            onReleased:
            {
                rectAnimation.from = rectBubble.color
                rectAnimation.to = win.bubbleColor
                rectAnimation.start();
            }

        }

    }

    PropertyAnimation
    {
        id: rectAnimation
        target: rectBubble
        property: "color"
        duration: 200
    }

}
