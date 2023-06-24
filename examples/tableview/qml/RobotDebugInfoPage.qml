import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Dialogs
import Qt.labs.qmlmodels
import Examples.Extras

Pane {
    id: root

    function columnWidth(column) {
        var widths = [48, 130, 130, 48, 130, 64, 64, 130, 64, 64, 64, -2];
        var width = widths[column];
        if (width < 0)
            width = tableView.width - tableView.columnWidthProvider(0) - tableView.columnWidthProvider(1) - tableView.columnWidthProvider(2) - tableView.columnWidthProvider(3) - tableView.columnWidthProvider(4) - tableView.columnWidthProvider(5) - tableView.columnWidthProvider(6) - tableView.columnWidthProvider(7) - tableView.columnWidthProvider(8) - tableView.columnWidthProvider(9) - tableView.columnWidthProvider(10) - 2;
        return width;
    }

    Material.background: Material.color(Material.Grey, Material.Shade800)
    padding: 0

    LivePointCloud {
        id: livePointCloud

        minInterval: 15
    }

    RobotDebugInfoTableModel {
        id: tableModel

        capacity: 50
        freezed: !root.visible || pauseButton.checked
        provider: livePointCloud.robotDebugInfoProvider
    }

    HorizontalHeaderView {
        id: horizontalHeader

        anchors.left: tableView.left
        anchors.top: parent.top
        clip: true
        syncView: tableView
        z: tableView.z + 1
    }

    TableView {
        id: tableView

        function currPos() {
            return tableView.contentY;
        }

        function getEndPos() {
            var ratio = 1.0 - tableView.visibleArea.heightRatio;
            var endPos = tableView.contentHeight * ratio;
            return endPos;
        }

        function scrollToEnd() {
            tableView.contentY = getEndPos();
        }

        function setPos(pos) {
            flickable.contentY = pos;
        }

        Material.background: Material.color(Material.Red, Material.Shade500)
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 0
        anchors.right: parent.right
        anchors.top: horizontalHeader.bottom
        clip: true
        columnSpacing: 1
        columnWidthProvider: root.columnWidth
        model: tableModel
        rowSpacing: 1

        ScrollBar.vertical: ScrollBar {
            anchors.bottomMargin: 4
            anchors.right: tableView.right
            anchors.rightMargin: 4
            anchors.topMargin: 4
            policy: ScrollBar.AlwaysOn
            visible: tableModel.freezed
            width: 8

            background: Rectangle {
                color: Qt.rgba(0, 0, 0, 0.5)
                radius: 4
            }
        }
        delegate: Rectangle {
            required property bool current
            property bool isLastColumn: column == tableView.columns - 1
            required property bool selected

            border.width: 0
            color: abnormal ? Material.color(Material.Amber, Material.Shade200) : ((tableView.alternatingRows && row % 2 !== 0) ? tableView.palette.alternateBase : tableView.palette.base)
            implicitHeight: 32
            implicitWidth: 40

            Text {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                bottomPadding: 4
                color: column == 0 ? Material.primary : Material.color(Material.Indigo)
                font.italic: column == 0
                horizontalAlignment: textAlignment
                leftPadding: 8
                rightPadding: 8
                text: isLastColumn ? "" : display
                topPadding: 20
            }

            Text {
                anchors.right: parent.right
                bottomPadding: 0
                color: delta ? deltaColor : Material.color(Material.Blue)
                font.italic: true
                font.pixelSize: 10
                horizontalAlignment: textAlignment
                leftPadding: 8
                rightPadding: 8
                text: delta ? delta : ""
                topPadding: 2
                visible: delta != ""
            }
        }

        onLayoutChanged: {
            if (!tableModel.freezed)
                scrollToEnd();
        }
    }

    ToolBar {
        anchors.right: tableView.right
        anchors.rightMargin: 16
        anchors.top: tableView.top
        anchors.topMargin: 16
        bottomPadding: 2
        leftPadding: 8
        rightPadding: 8
        topPadding: 2
        z: tableView.z + 1

        background: Rectangle {
            anchors.fill: parent
            color: Qt.rgba(0, 0, 0, 0.75)
            radius: 8
        }

        Row {
            anchors.margins: 0
            anchors.right: parent.right
            anchors.top: parent.top
            spacing: 0

            ToolButton {
                id: pauseButton

                ToolTip.delay: 1000
                ToolTip.text: checked ? qsTr("恢复数据更新") : qsTr("暂停数据更新")
                ToolTip.timeout: 5000
                ToolTip.visible: hovered
                checkable: true
                font.family: "Font Awesome 6 Free Solid"
                font.pixelSize: 20
                text: checked ? "\uf144" : "\uf28b"
            }

            ToolButton {
                id: loadButton

                ToolTip.delay: 1000
                ToolTip.text: qsTr("从 CSV 文件载入数据到此表格")
                ToolTip.timeout: 5000
                ToolTip.visible: hovered
                font.family: "Font Awesome 6 Free Solid"
                font.pixelSize: 20
                text: "\uf07c"

                onClicked: {
                    fileDialog.fileMode = FileDialog.ExistingFile;
                    fileDialog.open();
                }
            }

            ToolButton {
                id: saveButton

                ToolTip.delay: 1000
                ToolTip.text: qsTr("将此表格数据保存到 CSV 文件")
                ToolTip.timeout: 5000
                ToolTip.visible: hovered
                font.family: "Font Awesome 6 Free Solid"
                font.pixelSize: 20
                text: "\uf56e"

                onClicked: {
                    var now = new Date();
                    var nowStr = now.toLocaleString(Qt.locale("en-US"), "yyyyMMdd-hhmmss");
                    fileDialog.fileMode = FileDialog.SaveFile;
                    fileDialog.selectedFile = "robot-" + nowStr + ".csv";
                    fileDialog.open();
                }
            }
        }
    }

    FileDialog {
        id: fileDialog

        nameFilters: ["*.csv"]

        onAccepted: {
            if (fileDialog.fileMode == FileDialog.SaveFile)
                tableModel.save(selectedFile);
            else {
                tableModel.load(selectedFile);
                pauseButton.checked = true;
            }
        }
    }
}
