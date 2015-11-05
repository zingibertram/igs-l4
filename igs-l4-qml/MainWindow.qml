import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

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

            ColumnLayout {
                spacing: 4

                Button {
                    id: button_Epand_Main
                    text: qsTr("Основное")
                    checkable: true
                }

                GroupBox {
                    id: group_SurfaceFunctions
                    title: qsTr("Функция поверхности")
                }

                GroupBox {
                    id: group_SurfaceShading
                    title: qsTr("Закраска")
                }

                GroupBox {
                    id: group_SurfaceTexture
                    title: qsTr("Текстура")
                }

                Button {
                    id: button_Epand_Location
                    text: qsTr("Положение поверхности")
                    checkable: true
                }

                GroupBox {
                    id: group_SurfaceParams
                    title: qsTr("Параметры")
                }

                GroupBox {
                    id: group_SurfaceRotate
                    title: qsTr("Повороты")
                }

                Button {
                    id: button_Epand_Illuminant
                    text: qsTr("Источник света")
                    checkable: true
                }

                GroupBox {
                    id: group_IlluminantParams
                    title: qsTr("Параметры")
                }

                GroupBox {
                    id: group_IlluminantCoordinates
                    title: qsTr("Координаты")
                }

                Button {
                    id: button_Epand_ColorSelection
                    text: qsTr("Выбор цвета")
                    checkable: true
                }

                GroupBox {
                    id: group_IlluminantDottedColor
                    title: qsTr("Точечный источник")
                }

                GroupBox {
                    id: group_IlluminantAbsentedColor
                    title: qsTr("Рассеяный источник")
                }

                GroupBox {
                    id: group_SurfaceExteriorColor
                    title: qsTr("Внутренняя поверхность")
                }

                GroupBox {
                    id: group_SurfaceInteriorColor
                    title: qsTr("Наружная поверхность")

                    GridLayout {
                        columns: 4
                        rows: 3

                        Rectangle {
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
                            Layout.column: 1
                            Layout.row: 0
                            orientation: Qt.Horizontal
                            minimumValue: 0
                            maximumValue: 255
                            value: 255
                        }

                        Label {
                            text: qsTr("255");
                            Layout.column: 2
                            Layout.row: 0
                        }

                        Label {
                            id: label_Int_R
                            text: qsTr("***");
                            Layout.column: 3
                            Layout.row: 0
                        }

                        Label {
                            text: qsTr("B 0");
                            Layout.column: 0
                            Layout.row: 1
                        }

                        Slider {
                            Layout.column: 1
                            Layout.row: 1
                            orientation: Qt.Horizontal
                            minimumValue: 0
                            maximumValue: 255
                            value: 255
                        }

                        Label {
                            text: qsTr("255");
                            Layout.column: 2
                            Layout.row: 1
                        }

                        Label {
                            id: label_Int_G
                            text: qsTr("***");
                            Layout.column: 3
                            Layout.row: 1
                        }

                        Label {
                            text: qsTr("G 0");
                            Layout.column: 0
                            Layout.row: 2
                        }

                        Slider {
                            Layout.column: 1
                            Layout.row: 2
                            orientation: Qt.Horizontal
                            minimumValue: 0
                            maximumValue: 255
                            value: 255
                        }

                        Label {
                            text: qsTr("255");
                            Layout.column: 2
                            Layout.row: 2
                        }

                        Label {
                            id: label_Int_B
                            text: qsTr("***");
                            Layout.column: 3
                            Layout.row: 2
                        }
                    }
                }
            }
        }
    }
}

