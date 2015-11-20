import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

RowLayout {
    id: mainLayout
    Layout.fillHeight: true
    spacing: 6
    property int titleLen: 2
    property int valueLen: 4
    property string title: "***"
    property int min: 0
    property int max: 100
    property real value: slider.value
    property real step: 1.0

    FontMetrics {
        id: fontMetrics
        font: label_Title.font
    }

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
        Layout.minimumWidth: mainLayout.titleLen * fontMetrics.averageCharacterWidth
        Layout.maximumWidth: mainLayout.titleLen * fontMetrics.averageCharacterWidth
    }

    Label {
        id: label_Min
        text: mainLayout.min
        Layout.minimumWidth: mainLayout.valueLen * fontMetrics.averageCharacterWidth
        Layout.maximumWidth: mainLayout.valueLen * fontMetrics.averageCharacterWidth
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
        Layout.minimumWidth: mainLayout.valueLen * fontMetrics.averageCharacterWidth
        Layout.maximumWidth: mainLayout.valueLen * fontMetrics.averageCharacterWidth
        horizontalAlignment: Text.AlignLeft
        color: "#009900"
    }

    Label {
        id: label_Value
        text: mainLayout.value
        Layout.minimumWidth: mainLayout.valueLen * fontMetrics.averageCharacterWidth
        Layout.maximumWidth: mainLayout.valueLen * fontMetrics.averageCharacterWidth
        horizontalAlignment: Text.AlignHCenter
    }
}
