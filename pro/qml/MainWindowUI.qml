import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import igs.l4 1.0

Item {
    id: mainItem
    anchors.fill: parent
    Layout.minimumHeight: 360
    Layout.minimumWidth: 640

    RowLayout {
        id: mainLayout
        spacing: 4
        anchors.fill: parent

        Canvas {
            id: surfaceImage
            Layout.fillHeight: true
            Layout.fillWidth: true
        }


        ScrollView {
            id: scrollView
            Layout.fillHeight: true
            Layout.minimumWidth: mainWindow.maxWidth + 20
            horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
            verticalScrollBarPolicy: Qt.ScrollBarAlwaysOn

            ColumnLayout {
                spacing: 4

                Button {
                    id: button_Epand_Main
                    text: qsTr("Основное")
                    checkable: true
                    checked: mainWindowUI.expandedMain
                    Layout.fillWidth: true
                    Layout.minimumWidth: mainWindow.maxWidth
                    iconSource: "/icons/resources/arrow-down.png"
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
                    title: qsTr("Функция")
                    visible: button_Epand_Main.checked
                    Layout.fillWidth: true
                    Layout.maximumWidth: mainWindow.maxWidth

                    ComboBox {
                        id: comboBox_SurfaceFunctions
                        anchors.fill: parent
                        model: mainWindow.surfaceFunctions
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
                        rowSpacing: 1
                        columnSpacing: 6
                        anchors.fill: parent

                        ExclusiveGroup {
                            id: shading
                        }

                        RadioButton {
                            id: radio_FrameShading
                            text: "Каркас"
                            exclusiveGroup: shading
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
                            text: "Фонга"
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
                            text: "Наложить"
                            Layout.fillWidth: true
                        }

                        Button {
                            text: "Выбрать"
                            Layout.fillWidth: true
                            onClicked: openTexture.open()
                        }
                    }
                }

                Button {
                    id: button_Epand_Location
                    text: qsTr("Поверхность")
                    checkable: true
                    checked: mainWindowUI.expandedLocation
                    Layout.fillWidth: true
                    Layout.minimumWidth: mainWindow.maxWidth
                    iconSource: "/icons/resources/arrow-down.png"
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
                        spacing: 1

                        CustomSlider {
                            id: maxU
                            min: mainWindow.rangeMinU
                            max: mainWindow.rangeMaxU
                            title: qsTr("mU")
                            Layout.fillWidth: true
                            value: 180
                        }

                        CustomSlider {
                            id: maxV
                            min: mainWindow.rangeMinV
                            max: mainWindow.rangeMaxV
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
                            title: qsTr("RU")
                            Layout.fillWidth: true
                        }

                        CustomSlider {
                            id: param_r
                            min: 1
                            max: mainWindow.maxWidth
                            title: qsTr("rV")
                            Layout.fillWidth: true
                        }
                    }
                }

                GroupBox {
                    id: group_SurfaceRotate
                    title: qsTr("Положение")
                    visible: mainWindowUI.expandedLocation
                    Layout.fillWidth: true
                    Layout.maximumWidth: mainWindow.maxWidth

                    ColumnLayout {
                        anchors.fill: parent
                        spacing: 1

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
                    Layout.minimumWidth: mainWindow.maxWidth
                    iconSource: "/icons/resources/arrow-down.png"
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
                        spacing: 1

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
                    title: qsTr("Положение")
                    visible: mainWindowUI.expandedIlluminant
                    Layout.fillWidth: true
                    Layout.maximumWidth: mainWindow.maxWidth

                    ColumnLayout {
                        anchors.fill: parent
                        spacing: 1

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
                    text: qsTr("Цвет")
                    checkable: true
                    checked: mainWindowUI.expandedColors
                    Layout.fillWidth: true
                    Layout.minimumWidth: mainWindow.maxWidth
                    iconSource: "/icons/resources/arrow-down.png"
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
                    title: qsTr("Внешняя поверхность")
                    visible: mainWindowUI.expandedColors
                    Layout.fillWidth: true
                    Layout.maximumWidth: mainWindow.maxWidth

                    ColorSelection {
                        id: exteriorColor
                    }
                }

                GroupBox {
                    id: group_SurfaceInteriorColor
                    title: qsTr("Внутренняя поверхность")
                    visible: mainWindowUI.expandedColors
                    Layout.fillWidth: true
                    Layout.maximumWidth: mainWindow.maxWidth

                    ColorSelection {
                        id: interiorColor
                    }
                }
            }
        }

        Component.onCompleted: mainWindow.reset()
    }

    MainWindow {
        id: mainWindow
        surfaceFunction: comboBox_SurfaceFunctions.currentText
        textured: checkBox_Textured.checked
        maxU: maxU.value
        maxV: maxV.value
        dU: dU.value
        dV: dV.value
        param_R: param_R.value
        param_r: param_r.value
        rotX: rotOx.value
        rotY: rotOy.value
        rotZ: rotOz.value
        light_ka: illiminant_ka.value
        light_kd: illiminant_kd.value
        light_ks: illiminant_ks.value
        light_n: illiminant_n.value
        light_alpha: illiminant_alpha.value
        lightX: illiminantX.value
        lightY: illiminantY.value
        lightZ: illiminantZ.value
        dottedColor: dottedColor.colorString
        absentedColor: absentedColor.colorString
        exteriorColor: exteriorColor.colorString
        interiorColor: interiorColor.colorString
        paintViewWidth: surfaceImage.width
        paintViewHeight: surfaceImage.height
        property int maxWidth: 200
        onColorDrawingDataChanged: drawColor()
        onFrameDrawingDataChanged: drawFrame()

        function setShading(radio, sh) {
            if (radio.checked)
            {
                mainWindow.surfaceShading = sh
            }
        }

        function reset() {
            comboBox_SurfaceFunctions.currentIndex = 14

            console.log("comboBox_SurfaceFunctions")

            radio_FrameShading.checked = true

            checkBox_Textured.checked = false

            maxU.value = 90
            maxV.value = 90
            dU.value = 20
            dV.value = 20
            param_R.value = 100
            param_r.value = 50

            rotOx.value = 90
            rotOy.value = 60
            rotOz.value = 30

            illiminant_ka.value = 0.2 // absent
            illiminant_kd.value = 1.0 // diffusion
            illiminant_ks.value = 0.8 // specular
            illiminant_n.value = 25 // power
            illiminant_alpha.value = 1.0

            illiminantX.value = 0
            illiminantY.value = 0
            illiminantZ.value = 100

            dottedColor.r = 255
            dottedColor.g = 255
            dottedColor.b = 255

            absentedColor.r = 255
            absentedColor.g = 255
            absentedColor.b = 255

            exteriorColor.r = 255
            exteriorColor.g = 0
            exteriorColor.b = 0

            interiorColor.r = 0
            interiorColor.g = 255
            interiorColor.b = 0

            expandedMain = true
            expandedLocation = true
            expandedIlluminant = false
            expandedColors = false

            mainWindow.canCalculate = true

            console.log("reset")
        }

        function drawRequest(ctx) {
            surfaceImage.requestPaint()
            ctx.clearRect(0, 0, surfaceImage.width, surfaceImage.height)

            ctx.fillStyle = "black"
            ctx.fillRect(0, 0, surfaceImage.width, surfaceImage.height)

            drawAxes(ctx)
        }

        function drawFrame() {
            var ctx = surfaceImage.getContext('2d');

            mainWindow.drawRequest(ctx)

            ctx.lineWidth = 0.5
            ctx.strokeStyle = "white"

            ctx.beginPath()

            for (var i = 0; i < mainWindow.frameDrawingData.length;) {
                var x1 = mainWindow.frameDrawingData[i++]
                var y1 = mainWindow.frameDrawingData[i++]
                var x2 = mainWindow.frameDrawingData[i++]
                var y2 = mainWindow.frameDrawingData[i++]
                var x3 = mainWindow.frameDrawingData[i++]
                var y3 = mainWindow.frameDrawingData[i++]

                ctx.moveTo(x1, y1)
                ctx.lineTo(x2, y2)
                ctx.lineTo(x3, y3)
                ctx.lineTo(x1, y1)
            }
            ctx.stroke()

            ctx.closePath()
        }

        function drawColor() {
            var ctx = surfaceImage.getContext('2d');

            mainWindow.drawRequest(ctx)

            var cid = ctx.getImageData(0, 0, surfaceImage.width, surfaceImage.height)

            var count = cid.data.length
            var i = 0
            var data = mainWindow.colorDrawingData
            while (i < count) {
                var r = data[i]
                var g = data[i + 1]
                var b = data[i + 2]
                var a = data[i + 3]
                if (r || g || b) {
                    cid.data[i] = r
                    cid.data[i + 1] = g
                    cid.data[i + 2] = b
                    cid.data[i + 3] = a
                }
                i += 4
            }
            ctx.drawImage(cid, 0, 0, surfaceImage.width, surfaceImage.height)
        }

        function drawAxes(ctx) {
            var w = surfaceImage.width
            var h = surfaceImage.height
            var cx = w / 2.0
            var cy = h / 2.0

            ctx.lineWidth = 1
            ctx.strokeStyle = "white"
            ctx.fillStyle = "white"

            ctx.beginPath()

            ctx.moveTo(cx, 0)
            ctx.lineTo(cx - 5, 10)
            ctx.lineTo(cx + 5, 10)
            ctx.lineTo(cx, 0)
            ctx.moveTo(cx, 5)
            ctx.fill()
            ctx.lineTo(cx, h)

            ctx.moveTo(w, cy)
            ctx.lineTo(w - 10, cy - 5)
            ctx.lineTo(w - 10, cy + 5)
            ctx.lineTo(w, cy)
            ctx.moveTo(w - 5, cy)
            ctx.fill()
            ctx.lineTo(0, cy)

            ctx.closePath()

            ctx.stroke()
        }
    }

    FileDialog {
        id: openTexture
        modality: Qt.WindowModal
        title: qsTr("Выберите изображение для текстуры")
        selectExisting: true
        selectMultiple: false
        selectFolder: false
        nameFilters: [ "Image files (*.jpg)" ] // другие не загружаются
//        nameFilters: [ "Image files (*.png *.jpg *.bmp)" ]
        onAccepted: {
            mainWindow.texturePath = openTexture.fileUrl
        }
    }
}
