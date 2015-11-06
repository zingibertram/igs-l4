import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

RowLayout {
    id: mainLayout
    property int titleLen: 3
    property int valueLen: 4
    property string title: "***"
    property int min: 0
    property int max: 100
    property int value: slider.value

    Label {
        id: label_Title
        text: mainLayout.title
    }

    Label {
        id: label_Min
        text: mainLayout.min.toFixed(mainLayout.valueLen)
    }

    Slider {
        id: slider
        width: 120
        minimumValue: mainLayout.min
        maximumValue: mainLayout.max
        value: mainLayout.max
    }

    Label {
        id: label_Max
        text: mainLayout.max.toFixed(mainLayout.valueLen)
    }

    Label {
        id: label_Value
        text: mainLayout.value.toFixed(mainLayout.valueLen)
    }
}
