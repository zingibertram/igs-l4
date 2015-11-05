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

            MenuSeparator {
            }

            MenuItem {
                text: qsTr("Развернуть все")
                onTriggered: mainWindow.expandAll()
            }

            MenuItem {
                text: qsTr("Свернуть все")
                onTriggered: mainWindow.collapseAll()
            }

            MenuSeparator {
            }

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

    MainWindow {
        id: mainWindow

        function expandAll() {

        }

        function collapseAll() {

        }

        function change(state) {

        }
    }

    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")

        function show(title, message) {
            messageDialog.title = title
            messageDialog.text = message;
            messageDialog.open();
        }
    }
}
