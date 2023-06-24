import QtCharts
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Examples.Extras 1.0

Item {
    id: root

    property real maxX: 100
    property real maxY: 100
    property real minX: -100
    property real minY: -100
    readonly property real outputFps: 1000.0 / minInvtervalSlider.value
    property real tickInterval: 20

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true
            Layout.margins: 8

            Label {
                text: "Live Framerate"
                verticalAlignment: Text.AlignVCenter
            }

            Slider {
                id: minInvtervalSlider

                Layout.fillWidth: true
                from: 1
                to: 1000
                value: 100

                onValueChanged: livePointCloud.minInterval = value
            }

            Label {
                text: outputFps.toFixed(2) + " FPS"
                verticalAlignment: Text.AlignVCenter
            }
        }

        ChartView {
            id: chartView

            function onResized() {
                // Adjust the axes to keep the aspect ratio of the plot area
                if (plotArea.width > 0 && plotArea.height > 0) {
                    var aspectRatio = plotArea.width / plotArea.height;
                    if (aspectRatio < 1.0) {
                        xValueAxis.min = minX;
                        xValueAxis.max = maxX;
                        yValueAxis.min = minY / aspectRatio;
                        yValueAxis.max = maxY / aspectRatio;
                    } else {
                        xValueAxis.min = minX * aspectRatio;
                        xValueAxis.max = maxX * aspectRatio;
                        yValueAxis.min = minY;
                        yValueAxis.max = maxY;
                    }
                    // Adjust the tick interval to keep the number of ticks reasonable
                    var vp1 = Qt.point(0, 0);
                    var vp2 = Qt.point(10, 10);
                    var sp1 = mapToPosition(vp1, pointsSeries);
                    var sp2 = mapToPosition(vp2, pointsSeries);
                    var diff = sp2.x - sp1.x;
                    if (diff > 0) {
                        if (diff < 12) {
                            tickInterval = 40;
                        } else if (diff < 16) {
                            tickInterval = 30;
                        } else {
                            tickInterval = 20;
                        }
                    }
                }
            }

            Layout.fillHeight: true
            Layout.fillWidth: true
            antialiasing: true
            title: "Dynamic Area Series"

            onHeightChanged: onResized()
            onWidthChanged: onResized()

            LivePointCloud {
                id: livePointCloud

            }

            ValueAxis {
                id: xValueAxis

                labelFormat: "%.0f"
                max: maxX
                min: minX
                tickInterval: root.tickInterval
                tickType: ValueAxis.TicksDynamic
                titleText: "X (mm)"
            }

            ValueAxis {
                id: yValueAxis

                labelFormat: "%.0f"
                max: maxY
                min: minY
                tickInterval: root.tickInterval
                tickType: ValueAxis.TicksDynamic
                titleText: "Y (mm)"
            }

            ScatterSeries {
                id: pointsSeries

                axisX: xValueAxis
                axisY: yValueAxis
                name: "Points"
            }

            AreaSeries {
                id: grooveAreaSeries

                axisX: xValueAxis
                axisY: yValueAxis
                borderColor: "transparent"
                color: Qt.rgba(0, 0, 255, 0.5)
                name: "Groove Area"

                upperSeries: LineSeries {
                }
            }

            GrooveAreaSource {
                id: grooveAreaSource

                provider: livePointCloud.grooveAreaProvider
                series: grooveAreaSeries
            }

            PointCloudSource {
                id: pointCloudSource

                provider: livePointCloud.pointCloudProvider
                series: pointsSeries
            }

            BadgeLabel {
                id: badgeLabel

                text: livePointCloud.realtimeFps.toFixed(2)
                textAlignment: Qt.AlignRight
                title: "FPS"
                width: 80

                anchors {
                    right: chartView.right
                    rightMargin: 32
                    top: chartView.top
                    topMargin: 32
                }
            }
        }
    }
}
