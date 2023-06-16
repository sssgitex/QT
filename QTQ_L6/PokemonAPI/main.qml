import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12



Window {
    visible: true
    id: mainWindow
    width: 640
    height: 480
    title: qsTr("Pokemon API")

    property string baseUrl: "https://pokeapi.co/api/v2/"
    property string method: "GET"
    property string currentEndpoint: ""
    property string headerText: "List"

    ListModel{
        id: listModel
    }
    ListModel{
        id: formsModel
    }
    ListModel{
        id: infoModel
    }


    Component {
            id: listDelegate
            Rectangle{
                    color: "#FFDE00"
                    border.color: "black"
                    width: parent.width
                    height: 25
                    Text{
                        leftPadding: 5
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 20
                        text:"#" + idx +" "+name
                        color: "black"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:listView.currentIndex = index
                    }
            }
    }

    Component {
        id: formsDelegate
        Rectangle{
            color: "#EFFCD5"
            width: parent.width
            height:100
            Text{
                leftPadding: 10
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.pixelSize: 15
                text: type
                color: "#0C3348"
            }
            Image{
                source: img_url
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    Component{
        id: infoDelegate
        Rectangle{
            color: "#EFFCD5"
            width: parent.width
            height: 125
            Column{
                topPadding: 5
                leftPadding: 10
                Text{ text: "Color: " + color_name; font.pixelSize: 20}
                Text{ text: "Evolves from: " + evolves_from; font.pixelSize: 20}
                Text{ text: "Generation: " + generation; font.pixelSize: 20}
                Text{ text: "Habitat: " + habitat; font.pixelSize: 20}
                Text{ text: "Shape: " + shape; font.pixelSize: 20}
            }
        }
    }

    GridLayout{
        rows: 5
        columns: 5
        anchors.fill: parent
        anchors.margins: 10
        columnSpacing: 10

        ListView{
            id: listView
            Layout.row: 0
            Layout.column: 0
            Layout.rowSpan: 5
            Layout.columnSpan: 3
            Layout.fillWidth:true
            Layout.fillHeight: true
            height: parent.height

            ScrollBar.vertical: ScrollBar {
                    active: true
            }

            header: Rectangle{
                        width: parent.width
                        height: 40
                        border.color: "black"
                        border.width: 2
                        color: "#FF452A"
                        Text {
                            anchors.centerIn: parent
                            text: headerText
                            font.bold: true
                            font.pixelSize: 18
                            color: "#FBF9F3"
                        }
            }

            onCurrentItemChanged: {
                if (delegate == listDelegate)
                    pokemonId.text = model.get(listView.currentIndex).idx
            }
//            footer: Rectangle{
//                width: parent.width
//                height: 40
//                color: "#FFDE00"
//                Text {
//                    anchors.centerIn: parent
//                    text: listModel.count
//                    font.bold: true
//                    font.pixelSize: 18
//                    color: "#3B4CCA"
//                }
//            }

        }

        Button{
            id: pokemonListButton
            Layout.row: 0
            Layout.column: 3
            text: "Pokemon List"
            Layout.preferredWidth: 150
            onClicked: addList("pokemon")
        }
        Button{
            id: locationListButton
            Layout.row: 0
            Layout.column: 4
            text: "Location List"
            Layout.preferredWidth: 150
            onClicked: addList("location")
        }
        Button{
            id: itemsListButton
            Layout.row: 1
            Layout.column: 3
            text: "Item List"
            Layout.preferredWidth: 150
            onClicked: addList("item")
        }

        Button{
            id: berriesListButton
            Layout.row: 1
            Layout.column: 4
            text: "Berry List"
            Layout.preferredWidth: 150
            onClicked: addList("berry")
        }

        Label{
            Layout.row: 3
            Layout.column:3
            text: "Pokemon Name/Id: "
            Layout.preferredWidth: 150
            horizontalAlignment: TextInput.AlignHCenter
        }
        TextField{
            id: pokemonId
            Layout.row: 3
            Layout.column: 4
            Layout.preferredWidth: 150
            selectByMouse: true
        }
        Button{
            id: pokemonInfoButton
            Layout.row: 4
            Layout.column: 3
            text: "Pokemon Info"
            Layout.preferredWidth: 150
            onClicked: addInfo(pokemonId.text)
        }
        Button{
            id: pokemonFormsButton
            Layout.row: 4
            Layout.column: 4
            text: "Pokemon Forms"
            Layout.preferredWidth: 150
            onClicked: addForms(pokemonId.text)
        }
    }

    function capitalize(text){
        return text.charAt(0).toUpperCase() + text.slice(1);
    }

    function getDataList(endpoint){
        var xhr = new XMLHttpRequest();
        var url = baseUrl + endpoint.toLowerCase() +"/?limit=100"; //Limit to 100 for demo
        xhr.open(method,url,false);
        xhr.send();
        if (xhr.status == 200) return JSON.parse(xhr.response);
        else return "Error";
    }

    function addList(endpoint){
        var list = getDataList(endpoint).results;

        headerText = capitalize(endpoint) + " list";
        listModel.clear()
        listView.model = listModel
        listView.delegate = listDelegate
        for (let item of list){
            listModel.append({idx:item.url.split("/").slice(-2)[0],name:item.name});
        }

    }

    function getPokemonForms(id){
        var xhr = new XMLHttpRequest();
        var url = baseUrl + "pokemon-form/" + id.toLowerCase();
        xhr.open(method,url,false);
        xhr.send();
        if (xhr.status == 200) return JSON.parse(xhr.response);
        else return "Error";
    }

    function addForms(id){
        var json = getPokemonForms(id);
        formsModel.clear();
        listView.model = formsModel
        listView.delegate = formsDelegate;

        if (json == "Error") headerText = "Error!"
        else {
            var sprites = json.sprites;
            headerText = capitalize(json.name);
            for (let key in sprites){
                if (sprites[key]!=null) formsModel.append({type:key,img_url:sprites[key]});
            }
        }

    }

    function getPokemonInfo(id){
        var xhr = new XMLHttpRequest();
        var url = baseUrl + "pokemon-species/" + id;
        xhr.open(method,url,false);
        xhr.send();
        if (xhr.status == 200) return JSON.parse(xhr.response);
        else return "Error";
    }

    function addInfo(id){
        var json = getPokemonInfo(id);
        infoModel.clear();
        listView.model = infoModel
        listView.delegate = infoDelegate;

        if (json == "Error") headerText = "Error!"
        else {
            headerText = capitalize(json.name);
            infoModel.append({
                                 color_name:json.color.name,
                                 evolves_from: json.evolves_from_species == null ? "": json.evolves_from_species.name,
                                 generation:json.generation.name.split("-")[1].toUpperCase(),
                                 habitat:json.habitat.name,
                                 shape:json.shape.name
                             })
        }

    }


}
