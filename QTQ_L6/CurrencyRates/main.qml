import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
//import QtQuick.Controls 1.4

Window {
    visible: true
    minimumWidth: 500
    minimumHeight: 300
    title: qsTr("Exchange rates")

    property string base_url: "https://www.floatrates.com/daily/"
    property var currency_dict

    ListModel{
        id: currencyModel
        ListElement {code:"USD"}
        ListElement {code:"EUR"}
        ListElement {code:"GBP"}
        ListElement {code:"JPY"}
        ListElement {code:"CNY"}
        ListElement {code:"RUB"}
        ListElement {code:"RSD"}
    }

    Row{
        anchors.centerIn: parent
        height: 40

        TextField{
            id: valueFrom
            validator: DoubleValidator{
                bottom:0
                decimals:2
                locale: "EN"
            }
            height: parent.height
            width: 100
            onTextChanged: {
                updateResult()
            }
        }
        ComboBox{
            id: currencyFrom
            textRole: "code"
            model:currencyModel
            width: 80
            height: parent.height
            onCurrentTextChanged: {
                currency_dict = getData(currentText)
                updateResult()
            }

        }
        Label{
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 20
            font.bold: true
            text: " = "
            padding: 20
        }
        TextField{
            id: valueTo
            width: 100
            height: parent.height
            readOnly: true
        }
        ComboBox{
            id: currencyTo
            textRole: "code"
            model:currencyModel
            width: 80
            height: parent.height
            onCurrentTextChanged: {
                updateResult()
            }
        }
    }

    function getData(currencyCode){
        var xmlhttp = new XMLHttpRequest();
        var url = base_url + currencyCode.toLowerCase() + ".json"
        xmlhttp.open("GET",url,false);
        xmlhttp.send()
        return JSON.parse(xmlhttp.response)
    }

    function updateResult(){
        valueTo.text = convert(currencyTo.currentText,valueFrom.text)
    }

    function convert(currency_to,value){
        if (currencyFrom.currentText == currencyTo.currentText) return value
        return (parseFloat(currency_dict[currency_to.toLowerCase()].rate) * value).toFixed(2)
    }
}

