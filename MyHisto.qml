import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
pragma ComponentBehavior: Bound
Item {
    property int totalWordCount: 100
    required property var model
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

    RowLayout {
        anchors.fill: parent
        spacing: 2
        Repeater {
            model: innerItem.model
            delegate: MyHistoDelegate {

                Component.onCompleted: {
                    console.warn("[LOG] Data", key)
                    console.warn("[LOG] Model", value)
                }
            }
        }
    }
}
//onItemAdded: (index, item) => {
//    item.color = incapsulatedObj.getRandomColor()
//    item.hintText = index
//    item.heightRatio = index / innerItem.totalWordCount
//}
