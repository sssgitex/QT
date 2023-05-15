import QtQuick 2.15

ListModel {
    id: taskModel

    property int taskCount: 0

    function addTask(taskName, dueDate, progress) {
        var index = count
        insert(index, {
            "taskName": taskName,
            "dueDate": dueDate,
            "progress": progress
        })
        taskCount++
    }

    function updateTask(index, taskName, dueDate, progress) {
        set(index, {
            "taskName": taskName,
            "dueDate": dueDate,
            "progress": progress
        })
    }

    function deleteTask(index) {
        remove(index)
        taskCount--
    }
}
