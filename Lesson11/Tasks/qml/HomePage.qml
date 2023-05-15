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
            anchors.left: parent ? parent.left : undefined// parent
            anchors.right: parent ? parent.right : undefined // parent

            anchors.margins: defMargin*2
            //width: parent ? parent.width - defMargin*4: 0

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
        if (taskModel.saveAllTasks())
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
        addPg._date = ""
        addPg._progress = 0
        stackView.push(addPg)
    }

}
