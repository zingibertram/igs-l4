import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    id: item1
    Row {
        id: mainLayout
        anchors.fill: parent
        spacing: 4

        Rectangle {
            id: surfaceImage
            width: 160
            height: 90
            color: "#ffff44"
        }

        ScrollView {

            Column {
                spacing: 4

                Button {
                    id: button_Epand_Main
                    text: "Main"
                    checkable: true
                }

                GroupBox {
                    id: group_SurfaceFunctions
                    title: "Functions"
                }

                GroupBox {
                    id: group_SurfaceShading
                    title: "Shading"
                }

                GroupBox {
                    id: group_SurfaceTexture
                    title: "Texture"
                }

                Button {
                    id: button_Epand_Location
                    text: "Location"
                    checkable: true
                }

                GroupBox {
                    id: group_SurfaceParams
                    title: "Params"
                }

                GroupBox {
                    id: group_SurfaceRotate
                    title: "Rotate"
                }

                Button {
                    id: button_Epand_Illuminant
                    text: "Light source"
                    checkable: true
                }

                GroupBox {
                    id: group_IlluminantParams
                    title: "Illuminant params"
                }

                GroupBox {
                    id: group_IlluminantCoordinates
                    title: "Illuminant coordinates"
                }

                Button {
                    id: button_Epand_ColorSelection
                    text: "Color selection"
                    checkable: true
                }

                GroupBox {
                    id: group_IlluminantDottedColor
                    title: "Illuminant dotted color"
                }

                GroupBox {
                    id: group_IlluminantAbsentedColor
                    title: "Illuminant absented color"
                }

                GroupBox {
                    id: group_SurfaceExteriorColor
                    title: "Surface exterior color"
                }

                GroupBox {
                    id: group_SurfaceInteriorColor
                    title: "Surface interior color"
                }
            }
        }
    }
}

