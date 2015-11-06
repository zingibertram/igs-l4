import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

GridLayout {
    id: mainLayout
    columns: 4
    rows: 3
    property color colorString: "#" + Number(slider_R.value).toString(16) + Number(slider_G.value).toString(16) + Number(slider_B.value).toString(16)
    function convertColor() {
        var r = Number(slider_R.value).toString(16)
        var g = Number(slider_G.value).toString(16)
        var b = Number(slider_B.value).toString(16)
        if (r.length === 1)
        {
            r = "0" + r
        }
        if (g.length === 1)
        {
            g = "0" + g
        }
        if (b.length === 1)
        {
            b = "0" + b
        }
        colorPanel.color = "#" + r + g + b
        mainLayout.colorString = "#" + r + g + b
    }

    Rectangle {
        id: colorPanel
        width: 32
        height: 80
        Layout.column: 3
        Layout.row: 0
        Layout.rowSpan: 3
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
        orientation: Qt.Horizontal
        minimumValue: 0
        maximumValue: 255
        stepSize: 1
        value: 255
        onValueChanged: mainLayout.convertColor()
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
        width: 120
        Layout.column: 1
        Layout.row: 1
        orientation: Qt.Horizontal
        minimumValue: 0
        maximumValue: 255
        stepSize: 1
        value: 255
        onValueChanged: mainLayout.convertColor()
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
        width: 120
        Layout.column: 1
        Layout.row: 2
        orientation: Qt.Horizontal
        minimumValue: 0
        maximumValue: 255
        stepSize: 1
        value: 255
        onValueChanged: mainLayout.convertColor()
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

