import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

GridLayout {
    columns: 4
    rows: 3
    property color colorString: "#" + Number(slider_R.value).toString(16) + Number(slider_G.value).toString(16) + Number(slider_B.value).toString(16)

    Rectangle {
        width: 32
        height: 80
        Layout.column: 3
        Layout.row: 0
        Layout.rowSpan: 3
        color: "#" + Number(slider_R.value).toString(16) + Number(slider_G.value).toString(16) + Number(slider_B.value).toString(16)
    }

    Label {
        text: qsTr("R 0");
        Layout.column: 0
        Layout.row: 0
    }

    Slider {
        id: slider_R
        Layout.column: 1
        Layout.row: 0
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
    }

    Label {
        text: qsTr("G 0");
        Layout.column: 0
        Layout.row: 1
    }

    Slider {
        id: slider_G
        Layout.column: 1
        Layout.row: 1
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
    }

    Label {
        text: qsTr("B 0");
        Layout.column: 0
        Layout.row: 2
    }

    Slider {
        id: slider_B
        Layout.column: 1
        Layout.row: 2
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
    }
}

