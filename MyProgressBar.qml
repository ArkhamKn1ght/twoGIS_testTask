import QtQuick 2.15

Item {
    property real progress: 0
    property color progressColor: "transparent"
    property color borderColor: "transparent"

    id: innerItem
    onProgressChanged: {
        console.warn("progress: ", progress, visible);
    }

    visible: if (progress <= 0 || progress >= 1) {
                false
             } else {
                 true
             }

    Rectangle {
        id: firstRect
        anchors.fill: parent
        color: "transparent"

        border.color: innerItem.borderColor
        border.width: 2

        Rectangle {
            property real maxWidth: parent.width - anchors.leftMargin - anchors.rightMargin

            id: secondRect

            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.margins: 4

            width: if( innerItem.progress >= 1 ) {
                        maxWidth
                   } else if ( innerItem.progress <= 0 ) {
                        0
                   } else {
                       maxWidth * innerItem.progress
                   }

            color: innerItem.progressColor
        }
    }
}
