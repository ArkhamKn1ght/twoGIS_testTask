import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    signal clicked()
    required property color baseColor
    required property color hoverColor
    property string hintText: ""
    required property string name

    id: innerRect

    color: baseColor

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

        text: innerRect.name

        font.pointSize: 16
        font.bold: true

        color: innerRect.hoverColor
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            incapsulatedObj.hovered = true
            innerRect.color = innerRect.hoverColor
            innerText.color = innerRect.baseColor
            if(innerRect.hintText.length > 0)
                ToolTip.visible = true
        }

        onExited: {
            incapsulatedObj.hovered = false
            innerRect.color = innerRect.baseColor
            innerText.color = innerRect.hoverColor

            if(innerRect.hintText.length > 0)
                ToolTip.visible = false
        }
        onPressed: {
            innerRect.color = Qt.darker( innerRect.hoverColor, 1.2 )
        }

        onReleased: {
            innerRect.color = incapsulatedObj.hovered ? innerRect.hoverColor : innerRect.baseColor
            innerRect.clicked()
        }


        ToolTip.text: innerRect.hintText

    }
}
