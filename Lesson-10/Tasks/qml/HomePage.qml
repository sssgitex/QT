import QtQuick
import QtQuick.Controls

Page
{
    id: root
    //anchors.fill: parent

    signal saveAll()
    signal addNew()

    footer: HomeFooter
    {}

    background: Rectangle
    {
        color: bgColor
    }

    ListView
    {
        id: listView
        anchors.fill: parent
        spacing: defMargin
        ScrollBar.vertical: ScrollBar {}

        model: taskModel

        delegate: TaskItem
        {
            //height: 60
            anchors.left: parent.left // parent
            anchors.right: parent.right // parent
            anchors.margins: defMargin*2
            name: (model.index + 1) + ". " + model.name
            deadline: Qt.formatDate(model.deadline, "dd.MM.yyyy");
            parts: model.progress

            onClickedItem:
            {
                editPg._model = model
                editPg._index = index
                editPg._name = model.name
                editPg._progress = model.progress
                editPg._date = Qt.formatDate(model.deadline, "dd.MM.yyyy");
                stackView.push(editPg)
            }

        }

    }

    onSaveAll:
    {
        if (taskModel.saveTasksToFile())
        {
            msgPg.text = "Operation completed successfully";
            console.log("File saved successfully")

        }
        else
        {
            msgPg.text = "Error during operation execution"
            console.log("File saving error!")
        }
        stackView.push(msgPg)
    }

    onAddNew:
    {
        addPg._name = ""
        addPg._progress = 0
        stackView.push(addPg)
    }

}
