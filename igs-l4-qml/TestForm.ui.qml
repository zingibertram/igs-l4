import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2

Item {

    RowLayout {
        id: rowLayout1
        anchors.fill: parent

        GroupBox {
            id: groupBox1
            Layout.fillHeight: true
            Layout.fillWidth: true
            title: qsTr("Group Box")

            ColumnLayout {
                id: columnLayout1
                anchors.fill: parent

                CheckBox {
                    id: checkBox1
                    text: qsTr("Check Box")
                }

                Button {
                    id: button1
                    text: qsTr("Button")
                    iconSource: "/resources/arrow-down.png"
                }
            }
        }

        GroupBox {
            id: groupBox2
            Layout.fillHeight: true
            Layout.fillWidth: true
            title: qsTr("Group Box")

            ColumnLayout {
                id: columnLayout2
                anchors.fill: parent

                ComboBox {
                    id: comboBox1
                }

                Slider {
                    id: sliderHorizontal1
                }
            }
        }

        Image {
            id: image1
            width: 100
            height: 100
            source: "resources/tex1.jpg"
        }
    }
}

