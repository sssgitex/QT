import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Datalist Example")

    function getFriendsText(friends){
        var resString =""
        friends.forEach((friend)=>{
                            resString += friend +", ";
                        })
        return resString.slice(0,-2);
    }

    ListView{
        id: list
        anchors.fill: parent
        model: mdl
        spacing:1
        currentIndex: 0
        headerPositioning: ListView.OverlayHeader
        header: Rectangle{
                    width: parent.width
                    height: 50
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "grey"
                    border.color: "black"
                    border.width: 1
                    z:2
                    Text{
                        anchors.fill: parent
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: "Contacts"
                    }
                }

        delegate: Rectangle {
            width: parent.width
            height:200
            SwipeView{
                id: view
                anchors.fill: parent
                anchors.horizontalCenter: parent.horizontalCenter



                Item{
                    id: mainInfo
                    Rectangle{
                        anchors.fill: parent
                        color: "coral"
                        border.color: "black"
                        border.width: 1
                        Text{
                            anchors.fill: parent
                            text: rowId + ": " + name + " " + surname
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }

                Item{
                    id: friendInfo
                    Rectangle{
                        anchors.fill: parent
                        color: "lightblue"
                        border.color: "black"
                        border.width: 1
                        Text {
                            anchors.fill: parent
                            text: "Friends: " + getFriendsText(friends)
                            wrapMode: Text.WordWrap
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }
            }

            PageIndicator{
                id: indicator
                count: view.count
                currentIndex: view.currentIndex
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
            }


        }




    }

}
