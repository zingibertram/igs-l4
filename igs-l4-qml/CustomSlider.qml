import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

RowLayout {
    id: mainLayout
    Layout.fillHeight: true
    property int titleLen: 3
    property int valueLen: 4
    property string title: "***"
    property int min: 0
    property int max: 100
    property real value: slider.value
    property real mult: 0.7
    property real step: 1.0

    Binding {
        target: mainLayout
        property: "value"
        value: slider.value
    }

    Binding {
        target: slider
        property: "value"
        value: mainLayout.value
    }

    Label {
        id: label_Title
        text: mainLayout.title
        Layout.minimumWidth: mainLayout.titleLen * font.pointSize * mult
        Layout.maximumWidth: mainLayout.titleLen * font.pointSize * mult
    }

    Label {
        id: label_Min
        text: mainLayout.min
        Layout.minimumWidth: mainLayout.valueLen * label_Min.font.pointSize * mult
        Layout.maximumWidth: mainLayout.valueLen * label_Min.font.pointSize * mult
        horizontalAlignment: Text.AlignRight
        color: "#c00000"
    }

    Slider {
        id: slider
        width: 120
        minimumValue: mainLayout.min
        maximumValue: mainLayout.max
        value: mainLayout.value
        stepSize: mainLayout.step
        Layout.fillWidth: true
    }

    Label {
        id: label_Max
        text: mainLayout.max
        Layout.minimumWidth: mainLayout.valueLen * font.pointSize * mult
        Layout.maximumWidth: mainLayout.valueLen * font.pointSize * mult
        horizontalAlignment: Text.AlignLeft
        color: "#009900"
    }

    Label {
        id: label_Value
        text: mainLayout.value
        Layout.minimumWidth: mainLayout.valueLen * font.pointSize * mult
        Layout.maximumWidth: mainLayout.valueLen * font.pointSize * mult
        horizontalAlignment: Text.AlignHCenter
    }
}
