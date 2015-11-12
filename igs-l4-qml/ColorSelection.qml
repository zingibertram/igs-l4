import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

GridLayout {
    id: mainLayout
    columns: 4
    rows: 3
    anchors.fill: parent
    property color colorString: Qt.rgba(slider_R.value / 255, slider_G.value / 255, slider_B.value / 255, 1)

    Rectangle {
        id: colorPanel
        width: 32
        height: 80
        Layout.column: 3
        Layout.row: 0
        Layout.rowSpan: 3
        Layout.minimumWidth: 24
        Layout.maximumWidth: 24
        color: Qt.rgba(slider_R.value / 255, slider_G.value / 255, slider_B.value / 255, 1)
        border.width: 1
        border.color: "#000000"
    }

    Label {
        text: qsTr("R 0");
        Layout.column: 0
        Layout.row: 0
    }

    Slider {
        id: slider_R
        width: 120
        Layout.column: 1
        Layout.row: 0
        Layout.fillWidth: true
        orientation: Qt.Horizontal
        minimumValue: 0
        maximumValue: 255
        stepSize: 1
        value: 255
    }

    Label {
        text: qsTr("255");
        Layout.column: 2
        Layout.row: 0
    }

    Label {
        text: slider_R.value;
        Layout.column: 3
        Layout.row: 0
        color: Qt.rgba(1.0 - slider_R.value / 255, 1.0 - slider_G.value / 255, 1.0 - slider_B.value / 255, 1)
        Layout.minimumWidth: 24
        horizontalAlignment: Text.AlignHCenter
    }

    Label {
        text: qsTr("G 0");
        Layout.column: 0
        Layout.row: 1
    }

    Slider {
        id: slider_G
        width: 120
        Layout.column: 1
        Layout.row: 1
        Layout.fillWidth: true
        orientation: Qt.Horizontal
        minimumValue: 0
        maximumValue: 255
        stepSize: 1
        value: 255
    }

    Label {
        text: qsTr("255");
        Layout.column: 2
        Layout.row: 1
    }

    Label {
        text: slider_G.value;
        Layout.column: 3
        Layout.row: 1
        color: Qt.rgba(1.0 - slider_R.value / 255, 1.0 - slider_G.value / 255, 1.0 - slider_B.value / 255, 1)
        Layout.minimumWidth: 24
        horizontalAlignment: Text.AlignHCenter
    }

    Label {
        text: qsTr("B 0");
        Layout.column: 0
        Layout.row: 2
    }

    Slider {
        id: slider_B
        width: 120
        Layout.column: 1
        Layout.row: 2
        Layout.fillWidth: true
        orientation: Qt.Horizontal
        minimumValue: 0
        maximumValue: 255
        stepSize: 1
        value: 255
    }

    Label {
        text: qsTr("255");
        Layout.column: 2
        Layout.row: 2
    }

    Label {
        text: slider_B.value;
        Layout.column: 3
        Layout.row: 2
        color: Qt.rgba(1.0 - slider_R.value / 255, 1.0 - slider_G.value / 255, 1.0 - slider_B.value / 255, 1)
        Layout.minimumWidth: 24
        horizontalAlignment: Text.AlignHCenter
    }
}

