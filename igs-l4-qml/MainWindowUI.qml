import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import com.ics.demo 1.0

Item {
    id: mainItem
    width: 480
    height: 270

    RowLayout {
        id: mainLayout
        spacing: 4

        Rectangle {
            id: surfaceImage
            width: 160
            height: 90
            color: "#ffff44"
        }

        ScrollView {
            id: scrollView

            ColumnLayout {
                spacing: 4

                Button {
                    id: button_Epand_Main
                    text: qsTr("Основное")
                    checkable: true
                    checked: mainWindowUI.expandedMain
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

                    ComboBox {
                        id: comboBox_SurfaceFunctions
                        model: mainWindow.surfaceFunctions
                        currentIndex: 1
                    }
                }

                GroupBox {
                    id: group_SurfaceShading
                    title: qsTr("Закраска")
                    visible: mainWindowUI.expandedMain

                    GridLayout {
                        columns: 2
                        rows: 2

                        ExclusiveGroup {
                            id: shading
                        }

                        RadioButton {
                            id: radio_FrameShading
                            text: "Каркас"
                            exclusiveGroup: shading
                            checked: true
                            onCheckedChanged: mainWindow.setShading(radio_FrameShading, MainWindow.FR)
                        }

                        RadioButton {
                            id: radio_FlatShading
                            text: "Flat УНЛиП"
                            exclusiveGroup: shading
                            onCheckedChanged: mainWindow.setShading(radio_FlatShading, MainWindow.FL)
                        }

                        RadioButton {
                            id: radio_HuroShading
                            text: "Гуро"
                            exclusiveGroup: shading
                            onCheckedChanged: mainWindow.setShading(radio_HuroShading, MainWindow.HU)
                        }

                        RadioButton {
                            id: radio_FongShading
                            text: "Фонг"
                            exclusiveGroup: shading
                            onCheckedChanged: mainWindow.setShading(radio_FongShading, MainWindow.FO)
                        }
                    }
                }

                GroupBox {
                    id: group_SurfaceTexture
                    title: qsTr("Текстура")
                    visible: mainWindowUI.expandedMain

                    RowLayout {
                        CheckBox {
                            id: checkBox_Textured
                            text: "Текстура"
                            enabled: !radio_FrameShading.checked
                            Binding {
                                target: mainWindow
                                property: "textured"
                                value: checkBox_Textured.checked
                            }
                        }

                        Button {
                            text: "Выбрать"
                            enabled: !radio_FrameShading.checked
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
                }

                GroupBox {
                    id: group_SurfaceRotate
                    title: qsTr("Повороты")
                    visible: mainWindowUI.expandedLocation
                }

                Button {
                    id: button_Epand_Illuminant
                    text: qsTr("Источник света")
                    checkable: true
                    checked: mainWindowUI.expandedIlluminant
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
                }

                GroupBox {
                    id: group_IlluminantCoordinates
                    title: qsTr("Координаты")
                    visible: mainWindowUI.expandedIlluminant
                }

                Button {
                    id: button_Epand_Colors
                    text: qsTr("Выбор цвета")
                    checkable: true
                    checked: mainWindowUI.expandedColors
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

                    ColorSelection {
                        id: dottedColor
                    }
                }

                GroupBox {
                    id: group_IlluminantAbsentedColor
                    title: qsTr("Рассеяный источник")
                    visible: mainWindowUI.expandedColors

                    ColorSelection {
                        id: absentedColor
                    }
                }

                GroupBox {
                    id: group_SurfaceExteriorColor
                    title: qsTr("Внутренняя поверхность")
                    visible: mainWindowUI.expandedColors

                    ColorSelection {
                        id: exteriorColor
                    }
                }

                GroupBox {
                    id: group_SurfaceInteriorColor
                    title: qsTr("Наружная поверхность")
                    visible: mainWindowUI.expandedColors

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
