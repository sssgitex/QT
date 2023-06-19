import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.LocalStorage 2.12
import Qt.labs.qmlmodels 1.0
import "DBHelper.js" as DB

Window {
    visible: true
    minimumWidth: 800
    minimumHeight: 600
    maximumWidth: 800
    maximumHeight: 600
    title: qsTr("DB Editor")
    property int cellHorizontalSpacing: 10
    property var db
    property var current_model

    Component.onCompleted: {
        db = LocalStorage.openDatabaseSync("MyDatabase","1.0","My Local Database",100);
        current_model = contactsModel
        try {
            db.transaction(DB.createContactsTable);
            db.transaction(DB.createCarsTable);
            db.transaction((tx)=>{DB.readContacts(tx,contactsModel)});
            db.transaction((tx)=>{DB.readCars(tx,carsModel)});
        } catch (err){
            console.log("Error: " + err);
        }
    }

    TableModel{
        id: contactsModel
        TableModelColumn{display: "id"}
        TableModelColumn{display: "first_name"}
        TableModelColumn{display: "last_name"}
        TableModelColumn{display: "age"}
        TableModelColumn{display: "email"}
        TableModelColumn{display: "phone"}
        rows: []
    }
    TableModel{
        id: carsModel
        TableModelColumn{display: "id"}
        TableModelColumn{display: "owner_id"}
        TableModelColumn{display: "brand"}
        TableModelColumn{display: "model"}
        TableModelColumn{display: "color"}
        rows: []
    }

    Column{
        anchors.fill: parent
        anchors.topMargin: 20
        spacing: 20
        ComboBox{
            id: dbCombo
            anchors.horizontalCenter: parent.horizontalCenter
            model: ["contacts","cars"]
            onCurrentTextChanged: {
                if (currentText=="contacts") current_model = contactsModel
                if (currentText=="cars") current_model = carsModel
            }
        }
        Label{
            id:dbName
            anchors.horizontalCenter: parent.horizontalCenter
            text: dbCombo.currentText + " table"
            font.pixelSize: 30
        }

        TableView{
            id: table
            clip: true
            leftMargin: 100
            rightMargin: 100
            width: 800
            height: 400
            columnSpacing: 1
            rowSpacing: 1
            model:current_model
            ScrollBar.vertical: ScrollBar{
            }
            delegate: Rectangle{
                implicitWidth: Math.max(20, /*left*/ cellHorizontalSpacing + innerText.width + /*right*/cellHorizontalSpacing)
                implicitHeight: 40
                border.width: 1
                Text{
                    id: innerText
                    text:display
                    anchors.centerIn: parent
                }
                MouseArea{
                    id: mouseArea
                    anchors.fill: parent
                    onClicked: {
                        if (column===0) return;

                        editDialog.id = current_model.getRow(row).id
                        editDialog.column_name = getColumnName(current_model,column);
                        edit.text = modelData;
                        editDialog.open()
                    }
                }
            }

            Dialog{
                id: editDialog
                property int id
                property string column_name
                anchors.centerIn: parent
                TextField {
                    id: edit
                    selectByMouse: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                standardButtons: Dialog.Ok | Dialog.Cancel
                onAccepted: {
                        try {
                            db.transaction((tx) => {
                                var resObj = DB.updateValue(tx, dbCombo.currentText, id, column_name, edit.text);
                                if (resObj.rowsAffected !== 0) {
                                    current_model.clear();
                                    loadModelFromSQL();
                                }
                            })
                        } catch (err) {
                            console.log("Error creating or updating table in database: " + err)
                        }
                }
            }

        }

        Button {
            id: addButton
            text: "Add Record"
            anchors.horizontalCenter: parent.horizontalCenter
            //anchors.bottom: parent.bottom
            width:600
            onClicked: {
                if (current_model==contactsModel) contactsDialog.open()
                if (current_model==carsModel) carsDialog.open()
            }
        }
    }

    Dialog{
        id: contactsDialog
        anchors.centerIn: parent
        height: 400
        width:250
        header: Rectangle{
            width: parent.width
            height: 40
            color: "lightblue"
            Text{
                anchors.centerIn: parent
                text:"Add contact"
            }
        }
        standardButtons: Dialog.Ok | Dialog.Cancel
        Column {
            anchors.fill: parent
            spacing: 5
            TextField {
                id: firstName
                placeholderText: "Имя"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            TextField {
                id: lastName
                placeholderText: "Фамилия"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            TextField {
                id: age
                placeholderText: "Возраст"
                validator: IntValidator{bottom: 0;}
                anchors.horizontalCenter: parent.horizontalCenter
            }
            TextField {
                id: email
                placeholderText: "E-mail"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            TextField {
                id: phone
                placeholderText: "Номер телефона"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Label{
                id: errorLabelContacts
                visible: false
                color: "red"
                text: "Fill all fields!"
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        onAccepted: {
            if (firstName.text!=="" && lastName.text!=="" && age.text!=="" && email.text!=="" && phone.text!==""){
                try {
                    db.transaction((tx) => {
                        var resObj = DB.addContact(tx, firstName.text,
                                                   lastName.text,
                                                   age.text,
                                                   email.text,
                                                   phone.text);
                        if (resObj.rowsAffected !== 0) {
                            contactsModel.appendRow({
                                            id: resObj.insertId,
                                            first_name: firstName.text,
                                            last_name: lastName.text,
                                            age: age.text,
                                            email: email.text,
                                            phone: phone.text
                                            })
                        }
                    })
                    firstName.clear()
                    lastName.clear()
                    age.clear()
                    phone.clear()
                    email.clear()
                } catch (err) {
                    console.log("Error creating or updating table in database: " + err)
                }
            }else{
                contactsDialog.open()
                errorLabelContacts.visible = true
            }
        }

    }
    Dialog{
        id: carsDialog
        anchors.centerIn: parent
        height: 340
        width:250
        header: Rectangle{
            width: parent.width
            height: 40
            color: "lightblue"
            Text{
                anchors.centerIn: parent
                text:"Add cars"
            }
        }
        standardButtons: Dialog.Ok | Dialog.Cancel
        Column {
            anchors.fill: parent
            spacing: 5
            TextField {
                id: owner_id
                placeholderText: "ID владельца"
                validator: IntValidator{bottom: 0;}
                anchors.horizontalCenter: parent.horizontalCenter
            }
            TextField {
                id: brand
                placeholderText: "Марка"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            TextField {
                id: model
                placeholderText: "Модель"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            TextField {
                id: color
                placeholderText: "Цвет"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Label{
                id: errorLabelCars
                visible: false
                color: "red"
                text: "Fill all fields!"
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        onAccepted: {
            if (owner_id.text!=="" && brand.text!=="" && model.text!=="" && color.text!==""){
                try {
                    db.transaction((tx) => {
                        var resObj = DB.addCar(tx, owner_id.text,
                                                   brand.text,
                                                   model.text,
                                                   color.text);
                        if (resObj.rowsAffected !== 0) {
                            carsModel.appendRow({
                                            id: resObj.insertId,
                                            owner_id: owner_id.text,
                                            brand: brand.text,
                                            model: model.text,
                                            color: color.text
                                            })
                        }
                    })
                    owner_id.clear()
                    brand.clear()
                    model.clear()
                    color.clear()
                } catch (err) {
                    console.log("Error creating or updating table in database: " + err)
                }
            }else{
                carsDialog.open()
                errorLabelCars.visible = true
            }
        }

    }

    function getColumnName(model,columnNumber){
        if (model == contactsModel){
            switch(columnNumber){
            case(1):
                return "first_name"; break;
            case(2):
                return "last_name"; break;
            case(3):
                return "age"; break;
            case(4):
                return "email"; break;
            case(5):
                return "phone"; break;
            default:
                return "";
            }
        }
        if (model == carsModel){
            switch(columnNumber){
            case(1):
                return "owner_id"; break;
            case(2):
                return "brand"; break;
            case(3):
                return "model"; break;
            case(4):
                return "color"; break;
            default:
                return "";
            }
        }
    }

    function loadModelFromSQL(){
        if (current_model==contactsModel) db.transaction((tx)=>{DB.readContacts(tx,contactsModel)});
        if (current_model==carsModel) db.transaction((tx)=>{DB.readCars(tx,carsModel)});
    }


}
