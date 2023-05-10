QT += quick quickcontrols2 core gui
#QT += quickdialogs

CONFIG += c++17

TARGET += ToDo-list

# Добавляем ресурсы для QML-интерфейса
#qml.files += main.qml
#qml.files += TaskModel.qml
#qml.files += TaskDelegate.qml
#INSTALLS += qml

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    task.h \
    taskmodel.h

SOURCES += \
        main.cpp \
        task.cpp \
        taskmodel.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#DISTFILES += \
#    main.qml



RESOURCES += \
    qml.qrc
