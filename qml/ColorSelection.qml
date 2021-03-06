import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

GridLayout {
    id: root
    columns: 4
    rows: 3
    anchors.fill: parent
    rowSpacing: 1
    columnSpacing: 6
    property color colorString: Qt.rgba(root.r / 255, root.g / 255, root.b / 255, 1)
    property int r
    property int g
    property int b

    Binding {
        target: root
        property: "r"
        value: slider_R.value
    }
    Binding {
        target: root
        property: "g"
        value: slider_G.value
    }
    Binding {
        target: root
        property: "b"
        value: slider_B.value
    }

    Binding {
        target: slider_R
        property: "value"
        value: root.r
    }
    Binding {
        target: slider_G
        property: "value"
        value: root.g
    }
    Binding {
        target: slider_B
        property: "value"
        value: root.b
    }

    Rectangle {
        id: colorPanel
        width: 32
        height: 80
        Layout.column: 3
        Layout.row: 0
        Layout.rowSpan: 3
        Layout.minimumWidth: 24
        Layout.maximumWidth: 24
        color: Qt.rgba(root.r / 255, root.g / 255, root.b / 255, 1)
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
        color: Qt.rgba(1.0 - root.r / 255, 1.0 - root.g / 255, 1.0 - root.b / 255, 1)
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
        color: Qt.rgba(1.0 - root.r / 255, 1.0 - root.g / 255, 1.0 - root.b / 255, 1)
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
        color: Qt.rgba(1.0 - root.r / 255, 1.0 - root.g / 255, 1.0 - root.b / 255, 1)
        Layout.minimumWidth: 24
        horizontalAlignment: Text.AlignHCenter
    }
}

