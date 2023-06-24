import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import Qt.labs.qmlmodels
import Examples.Extras

Pane {
    id: root

    Material.theme: Material.Dark
    height: 720
    width: 1280

    TabBar {
        id: tabBar

        width: parent.width

        TabButton {
            text: qsTr("焊缝信息")
        }

        TabButton {
            text: qsTr("机器人调试信息")
        }

        TabButton {
            text: qsTr("算法调试信息")
        }

        TabButton {
            text: qsTr("其他信息")
        }
    }

    StackLayout {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: tabBar.bottom
        currentIndex: tabBar.currentIndex

        Pane {
            id: seamInfoTab

            Material.background: Material.color(Material.Grey, Material.Shade800)
            padding: 0

            Text {
                anchors.centerIn: parent
                color: "white"
                font.pixelSize: 50
                text: qsTr("TODO")
            }
        }

        Pane {
            id: robotDebugInfoTab

            Material.background: Material.color(Material.Grey, Material.Shade800)
            padding: 0

            RobotDebugInfoPage {
                anchors.fill: parent
            }
        }

        Pane {
            id: dspDebugInfoTab

            Material.background: Material.color(Material.Grey, Material.Shade800)
            padding: 0

            Text {
                anchors.centerIn: parent
                color: "white"
                font.pixelSize: 50
                text: qsTr("TODO")
            }
        }

        Pane {
            id: othersTab

            Material.background: Material.color(Material.Grey, Material.Shade800)
            padding: 0

            Text {
                anchors.centerIn: parent
                color: "white"
                font.pixelSize: 50
                text: qsTr("TODO")
            }
        }
    }
}
