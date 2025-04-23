import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    signal clicked()
    required property color baseColor
    required property color hoverColor
    required property string hintText
    color: baseColor
    id: innerRect
    QtObject {
        id: incapsulatedObj
        property bool hovered: false
        function buttonPressEffect(baseColor, pressed) {
            return Qt.darker(baseColor, pressed ? 1.2 : 1.0)
        }
    }

    Text {
        id: innerText

        anchors.fill: parent
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        wrapMode: Text.WordWrap
        text: innerRect.hintText
        font.pointSize: 16
        font.bold: true
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            incapsulatedObj.hovered = true
            innerRect.color = innerRect.hoverColor
            innerText.color = innerRect.baseColor
        }

        onExited: {
            incapsulatedObj.hovered = false
            innerRect.color = innerRect.baseColor
            innerText.color = innerRect.hoverColor
        }
        onPressed: {
            console.warn("pressed")
            innerRect.color = Qt.darker( innerRect.hoverColor, 1.2 )
        }

        onReleased: {
            console.warn("released")
            innerRect.color = incapsulatedObj.hovered ? innerRect.hoverColor : innerRect.baseColor
        }
    }
}
