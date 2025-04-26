import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import com.twogis.test 1.0
pragma ComponentBehavior: Bound
Item {
    property int totalWordCount: 100
    required property var model
    id: innerItem

    LimitRowsProxyModel {
        id: limitedModel
        sourceModel: innerItem.model
        limit: 15
    }

    RowLayout {
        anchors.fill: parent
        spacing: 2
        Repeater {
            model: limitedModel
            delegate: MyHistoDelegate {

            }
        }
    }
}
