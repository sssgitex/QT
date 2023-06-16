import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    minimumWidth: 600
    minimumHeight: 400
    title: qsTr("Weather")

//    property var header: {"X-Gismeteo-Token":"56b30cb255.3443075", "Accept-Encoding":"gzip"}
//    property string baseUrl: "https://api.gismeteo.net/v2/"
//    function setHeaders(xhr){
//        for (let h in header){
//            xhr.setRequestHeader(h,header[h]);
//        }
//        console.log(xhr.he)
//    }

    property string baseUrl: "http://api.weatherapi.com/v1"
    property string apiKey: "f5799f6f0ffd4ed39e6215023231206"

    Row{
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20
        TextField{
            id: city
            anchors.topMargin: 100
            placeholderText: "Введите город..."
            focus:true
            selectByMouse : true
            Keys.onEnterPressed: getWeather()
            Keys.onReturnPressed: getWeather()
        }

        Button {
            id: findButton
            text: "Узнать погоду"
            anchors.topMargin: 100
            onClicked: getWeather()
        }
    }

    TextArea{
        id: weatherTextArea
        anchors.centerIn: parent
        width: parent.width * 0.9
        height: parent.height * 0.6
        readOnly: true
        font.pixelSize: 20
        background: Rectangle {
            color: "lightgrey"
        }
        Image {
            id:icon
            anchors.right: parent.right
            anchors.top: parent.top
            source: ""
        }
    }

    function getWeather(){
        if (city.text !== ""){
            weatherTextArea.clear()
            icon.source = ""
            printData(getData(city.text))
        }
    }

    function getData(city){
        var xhr = new XMLHttpRequest();
        var url = `${baseUrl}/current.json?key=${apiKey}&q=${city}&lang=ru`;
        xhr.open("GET",url,false);
        xhr.send();
        if (xhr.status == 200) return JSON.parse(xhr.response)
        else return "Error!"
    }

    function printData(weatherJson){
        if (weatherJson === "Error!") weatherTextArea.append("Местоположение не найдено!")
        else{
        weatherTextArea.append("Город: "+weatherJson.location.name+", "+weatherJson.location.country);
        weatherTextArea.append("Температура: "+weatherJson.current.temp_c+"C");
        weatherTextArea.append("Давление: "+weatherJson.current.pressure_mb+" рт.ст");
        weatherTextArea.append("Влажность: "+weatherJson.current.humidity+"%");
        weatherTextArea.append("Ветер: "+weatherJson.current.wind_kph+"км/ч");
        weatherTextArea.append(weatherJson.current.condition.text);
        icon.source = "https:"+weatherJson.current.condition.icon
        }
    }


}
