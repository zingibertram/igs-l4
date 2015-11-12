import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import com.ics.demo 1.0

Item {
    id: mainItem
    anchors.fill: parent
    Layout.minimumHeight: 360
    Layout.minimumWidth: 640

    RowLayout {
        id: mainLayout
        spacing: 4
        anchors.fill: parent

        Rectangle {
            id: surfaceImage
            width: 120
            color: "#ffff44"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        ScrollView {
            id: scrollView
            Layout.fillHeight: true
            Layout.minimumWidth: 260
            //horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
            verticalScrollBarPolicy: Qt.ScrollBarAlwaysOn

            ColumnLayout {
                spacing: 4

                Button {
                    id: button_Epand_Main
                    text: qsTr("Основное")
                    checkable: true
                    checked: mainWindowUI.expandedMain
                    Layout.fillWidth: true
                    Layout.maximumWidth: mainWindow.maxWidth
                    Layout.minimumWidth: mainWindow.maxWidth
                    Binding {
                        target: button_Epand_Main
                        property: "checked"
                        value: mainWindowUI.expandedMain
                    }
                    Binding {
                        target: mainWindowUI
                        property: "expandedMain"
                        value: button_Epand_Main.checked
                    }
                }

                GroupBox {
                    id: group_SurfaceFunctions
                    title: qsTr("Функция поверхности")
                    visible: button_Epand_Main.checked
                    Layout.fillWidth: true
                    Layout.maximumWidth: mainWindow.maxWidth

                    ComboBox {
                        id: comboBox_SurfaceFunctions
                        anchors.fill: parent
                        model: mainWindow.surfaceFunctions
                        currentIndex: 1
                        Layout.fillWidth: true
                    }
                }

                GroupBox {
                    id: group_SurfaceShading
                    title: qsTr("Закраска")
                    visible: mainWindowUI.expandedMain
                    Layout.fillWidth: true
                    Layout.maximumWidth: mainWindow.maxWidth

                    GridLayout {
                        columns: 2
                        rows: 2
                        anchors.fill: parent

                        ExclusiveGroup {
                            id: shading
                        }

                        RadioButton {
                            id: radio_FrameShading
                            text: "Каркас"
                            exclusiveGroup: shading
                            checked: true
                            onCheckedChanged: mainWindow.setShading(radio_FrameShading, MainWindow.FR)
                            Layout.fillWidth: true
                        }

                        RadioButton {
                            id: radio_FlatShading
                            text: "Flat УНЛиП"
                            exclusiveGroup: shading
                            onCheckedChanged: mainWindow.setShading(radio_FlatShading, MainWindow.FL)
                            Layout.fillWidth: true
                        }

                        RadioButton {
                            id: radio_HuroShading
                            text: "Гуро"
                            exclusiveGroup: shading
                            onCheckedChanged: mainWindow.setShading(radio_HuroShading, MainWindow.HU)
                            Layout.fillWidth: true
                        }

                        RadioButton {
                            id: radio_FongShading
                            text: "Фонг"
                            exclusiveGroup: shading
                            onCheckedChanged: mainWindow.setShading(radio_FongShading, MainWindow.FO)
                            Layout.fillWidth: true
                        }
                    }
                }

                GroupBox {
                    id: group_SurfaceTexture
                    title: qsTr("Текстура")
                    visible: mainWindowUI.expandedMain
                    Layout.fillWidth: true
                    Layout.maximumWidth: mainWindow.maxWidth

                    RowLayout {
                        anchors.fill: parent
                        CheckBox {
                            id: checkBox_Textured
                            text: "Текстура"
                            enabled: !radio_FrameShading.checked
                            Layout.fillWidth: true
                            Binding {
                                target: mainWindow
                                property: "textured"
                                value: checkBox_Textured.checked
                            }
                        }

                        Button {
                            text: "Выбрать"
                            enabled: !radio_FrameShading.checked
                            Layout.fillWidth: true
                            onClicked: {
                                openTexture.open();
                            }
                        }
                    }
                }

                Button {
                    id: button_Epand_Location
                    text: qsTr("Положение поверхности")
                    checkable: true
                    checked: mainWindowUI.expandedLocation
                    Layout.fillWidth: true
                    Layout.maximumWidth: mainWindow.maxWidth
                    Layout.minimumWidth: mainWindow.maxWidth
                    Binding {
                        target: button_Epand_Location
                        property: "checked"
                        value: mainWindowUI.expandedLocation
                    }
                    Binding {
                        target: mainWindowUI
                        property: "expandedLocation"
                        value: button_Epand_Location.checked
                    }
                }

                GroupBox {
                    id: group_SurfaceParams
                    title: qsTr("Параметры")
                    visible: mainWindowUI.expandedLocation
                    Layout.fillWidth: true
                    Layout.maximumWidth: mainWindow.maxWidth

                    ColumnLayout {
                        anchors.fill: parent
                        CustomSlider {
                            id: maxU
                            min: 0
                            max: 360
                            title: qsTr("mU")
                            Layout.fillWidth: true
                        }

                        CustomSlider {
                            id: maxV
                            min: 0
                            max: 360
                            title: qsTr("mV")
                            Layout.fillWidth: true
                        }

                        CustomSlider {
                            id: dU
                            min: 1
                            max: 50
                            title: qsTr("dU")
                            Layout.fillWidth: true
                        }

                        CustomSlider {
                            id: dV
                            min: 1
                            max: 50
                            title: qsTr("dV")
                            Layout.fillWidth: true
                        }

                        CustomSlider {
                            id: param_R
                            min: 1
                            max: mainWindow.maxWidth
                            title: qsTr("R")
                            Layout.fillWidth: true
                        }

                        CustomSlider {
                            id: param_r
                            min: 1
                            max: mainWindow.maxWidth
                            title: qsTr("r")
                            Layout.fillWidth: true
                        }
                    }
                }

                GroupBox {
                    id: group_SurfaceRotate
                    title: qsTr("Повороты")
                    visible: mainWindowUI.expandedLocation
                    Layout.fillWidth: true
                    Layout.maximumWidth: mainWindow.maxWidth

                    ColumnLayout {
                        anchors.fill: parent
                        CustomSlider {
                            id: rotOx
                            min: -180
                            max: 180
                            title: qsTr("OX")
                        }

                        CustomSlider {
                            id: rotOy
                            min: -180
                            max: 180
                            title: qsTr("OY")
                        }

                        CustomSlider {
                            id: rotOz
                            min: -180
                            max: 180
                            title: qsTr("OZ")
                        }
                    }
                }

                Button {
                    id: button_Epand_Illuminant
                    text: qsTr("Источник света")
                    checkable: true
                    checked: mainWindowUI.expandedIlluminant
                    Layout.fillWidth: true
                    Layout.maximumWidth: mainWindow.maxWidth
                    Layout.minimumWidth: mainWindow.maxWidth
                    Binding {
                        target: button_Epand_Illuminant
                        property: "checked"
                        value: mainWindowUI.expandedIlluminant
                    }
                    Binding {
                        target: mainWindowUI
                        property: "expandedIlluminant"
                        value: button_Epand_Illuminant.checked
                    }
                }

                GroupBox {
                    id: group_IlluminantParams
                    title: qsTr("Параметры")
                    visible: mainWindowUI.expandedIlluminant
                    Layout.fillWidth: true
                    Layout.maximumWidth: mainWindow.maxWidth

                    ColumnLayout {
                        anchors.fill: parent
                        CustomSlider {
                            id: illiminant_ka
                            min: 0
                            max: 1
                            title: qsTr("ka")
                            step: 0.1
                        }

                        CustomSlider {
                            id: illiminant_kd
                            min: 0
                            max: 1
                            title: qsTr("kd")
                            step: 0.1
                        }

                        CustomSlider {
                            id: illiminant_ks
                            min: 0
                            max: 1
                            title: qsTr("ks")
                            step: 0.1
                        }

                        CustomSlider {
                            id: illiminant_n
                            min: 0
                            max: 127
                            title: qsTr("n")
                        }

                        CustomSlider {
                            id: illiminant_alpha
                            min: 0
                            max: 1
                            title: qsTr("α")
                            step: 0.1
                        }
                    }
                }

                GroupBox {
                    id: group_IlluminantCoordinates
                    title: qsTr("Координаты")
                    visible: mainWindowUI.expandedIlluminant
                    Layout.fillWidth: true
                    Layout.maximumWidth: mainWindow.maxWidth

                    ColumnLayout {
                        anchors.fill: parent
                        CustomSlider {
                            id: illiminantX
                            min: -500
                            max: 500
                            title: qsTr("X")
                        }

                        CustomSlider {
                            id: illiminantY
                            min: -500
                            max: 500
                            title: qsTr("Y")
                        }

                        CustomSlider {
                            id: illiminantZ
                            min: -500
                            max: 500
                            title: qsTr("Z")
                        }
                    }
                }

                Button {
                    id: button_Epand_Colors
                    text: qsTr("Выбор цвета")
                    checkable: true
                    checked: mainWindowUI.expandedColors
                    Layout.fillWidth: true
                    Layout.maximumWidth: mainWindow.maxWidth
                    Layout.minimumWidth: mainWindow.maxWidth
                    Binding {
                        target: button_Epand_Colors
                        property: "checked"
                        value: mainWindowUI.expandedColors
                    }
                    Binding {
                        target: mainWindowUI
                        property: "expandedColors"
                        value: button_Epand_Colors.checked
                    }
                }

                GroupBox {
                    id: group_IlluminantDottedColor
                    title: qsTr("Точечный источник")
                    visible: mainWindowUI.expandedColors
                    Layout.fillWidth: true
                    Layout.maximumWidth: mainWindow.maxWidth

                    ColorSelection {
                        id: dottedColor
                    }
                }

                GroupBox {
                    id: group_IlluminantAbsentedColor
                    title: qsTr("Рассеяный источник")
                    visible: mainWindowUI.expandedColors
                    Layout.fillWidth: true
                    Layout.maximumWidth: mainWindow.maxWidth

                    ColorSelection {
                        id: absentedColor
                    }
                }

                GroupBox {
                    id: group_SurfaceExteriorColor
                    title: qsTr("Внутренняя поверхность")
                    visible: mainWindowUI.expandedColors
                    Layout.fillWidth: true
                    Layout.maximumWidth: mainWindow.maxWidth

                    ColorSelection {
                        id: exteriorColor
                    }
                }

                GroupBox {
                    id: group_SurfaceInteriorColor
                    title: qsTr("Наружная поверхность")
                    visible: mainWindowUI.expandedColors
                    Layout.fillWidth: true
                    Layout.maximumWidth: mainWindow.maxWidth

                    ColorSelection {
                        id: interiorColor
                    }
                }
            }
        }
    }

    MainWindow {
        id: mainWindow
        surfaceFunction: comboBox_SurfaceFunctions.currentText
        dottedColor: dottedColor.colorString
        absentedColor: absentedColor.colorString
        exteriorColor: exteriorColor.colorString
        interiorColor: interiorColor.colorString
        property int maxWidth: 240

        function setShading(radio, sh) {
            if (radio.checked)
            {
                mainWindow.surfaceShading = sh
            }
        }
    }

    FileDialog {
        id: openTexture
        modality: Qt.WindowModal
        title: qsTr("Выберите изображение для текстуры")
        selectExisting: true
        selectMultiple: false
        selectFolder: false
        nameFilters: [ "Image files (*.jpg)" ] // друугие не загружаются
//        nameFilters: [ "Image files (*.png *.jpg *.bmp)" ]
        onAccepted: {
            mainWindow.texturePath = openTexture.fileUrl
        }
    }
}
