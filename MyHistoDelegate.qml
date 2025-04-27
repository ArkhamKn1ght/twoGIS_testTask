import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    required property string key
    required property int value

    property string hintText: key
    property real heightRatio: value / 10
    property bool hovered: false

    property int maxHeight: 10

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
    ToolTip.text: hintText + " " + value
}
