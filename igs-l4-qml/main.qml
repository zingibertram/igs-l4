import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: qsTr("Лабораторная работа №4")
    visible: true
    width: 640
    height: 360

    menuBar: MenuBar {
        Menu {
            title: qsTr("Файл")

            MenuItem {
                text: qsTr("Исходное состояние")
            }

            MenuSeparator {}

            MenuItem {
                text: qsTr("Развернуть все")
                onTriggered: mainWindowUI.expandAll()
            }

            MenuItem {
                text: qsTr("Свернуть все")
                onTriggered: mainWindowUI.collapseAll()
            }

            MenuSeparator {}

            MenuItem {
                text: qsTr("Выход")
                onTriggered: Qt.quit();
            }
        }

        Menu {
            title: qsTr("Справка")

            MenuItem {
                text: qsTr("О программе")
                onTriggered: messageDialog.show(qsTr("О программе"), qsTr("Лабораторная работа №4 по\nИнтерактивным графическим системам.\n\"Прозрачность и текстура\"\nВыполнил: ст. гр. МО-426 Ахтямов А.А.\nПроверил: проф. каф. ВМиК Верхотуров М.А."))
            }
        }
    }

    MainWindowUI {
        id: mainWindowUI
        property bool expandedMain: false
        property bool expandedLocation: false
        property bool expandedIlluminant: false
        property bool expandedColors: true

        function expandAll() {
            mainWindowUI.change(true)
        }

        function collapseAll() {
            mainWindowUI.change(false)
        }

        function change(state) {
            mainWindowUI.expandedMain = state
            mainWindowUI.expandedLocation = state
            mainWindowUI.expandedIlluminant = state
            mainWindowUI.expandedColors = state
        }
    }

    MessageDialog {
        id: messageDialog

        function show(title, message) {
            messageDialog.title = title
            messageDialog.text = message;
            messageDialog.open();
        }
    }
}
