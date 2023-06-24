import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Pane {
    id: root

    property color backgroundColor: Qt.rgba(0, 0, 0, 0.5)
    property color color: "white"
    property color highlightColor: Qt.rgba(0, 1.0, 0, 0.5)
    property string text: "World"
    property alias textAlignment: textLabel.horizontalAlignment
    property string title: "Hello"

    padding: 2

    background: Rectangle {
        color: root.backgroundColor
        radius: 3
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Label {
            id: titleLabel

            bottomPadding: 2
            color: root.color
            leftPadding: 4
            rightPadding: 4
            text: root.title
            topPadding: 2

            background: Rectangle {
                color: root.backgroundColor
                radius: 0
            }
        }

        Label {
            id: textLabel

            Layout.fillWidth: true
            bottomPadding: 2
            color: root.color
            leftPadding: 4
            rightPadding: 4
            text: root.text
            topPadding: 2

            background: Rectangle {
                color: root.highlightColor
                radius: 0
            }
        }
    }
}
