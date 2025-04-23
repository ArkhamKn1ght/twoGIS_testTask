import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
pragma ComponentBehavior: Bound
Item {
    property int totalWordCount: 100

    id: innerItem

    QtObject {
        id: incapsulatedObj
        function getRandomColor() {
            var r = Math.floor(Math.random() * 256)
            var g = Math.floor(Math.random() * 256)
            var b = Math.floor(Math.random() * 256)
            return Qt.rgba(r / 255, g / 255, b / 255, 1)
        }
    }

    Component {
        id: histoDelegate
        Rectangle {
            property int index
            property string hintText
            property real heightRatio: 0
            property bool hovered: false

            QtObject {
                id: histoIncapsulatedObj
            }

            id: histoElement
            Layout.preferredHeight: parent.height * heightRatio
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onEntered: histoElement.hovered = true
                onExited: histoElement.hovered = false
            }

            ToolTip.visible: hovered
            ToolTip.text: hintText
        }
    }



    RowLayout {
        anchors.fill: parent
        spacing: 2
        Repeater {
            model: 15
            delegate: histoDelegate
            onItemAdded: (index, item) => {
                item.color = incapsulatedObj.getRandomColor()
                item.hintText = index
                item.heightRatio = index / innerItem.totalWordCount
            }
        }
    }
}
