import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import com.twogis.test 1.0
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    color: "black"
    Page {
        anchors.fill: parent
        header: Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            height: 50
            color: "pink";
            RowLayout {
                anchors.fill: parent
                spacing: 2
                MyButton {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    baseColor: "yellow"
                    hoverColor: "pink"
                    hintText: "Aboba"
                }
                MyButton {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    baseColor: "green"
                    hoverColor: "red"
                    hintText: "Huimen"
                }
            }
        }
        Rectangle {
            anchors.fill: parent
            color: "black"
            MyHisto {
                anchors.fill: parent
                model: corePresenter.mapModel
                Component.onCompleted: {
                    console.warn("aboba abobicus", corePresenter.mapModel)
                }
            }
        }
        footer: Rectangle {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 50
            color: "green"
        }
    }

    MyProgressBar {
        id: progressBar
        anchors.centerIn: parent
        width: 100
        height: 50
        progressColor: "red"
        borderColor: "green"
        NumberAnimation {
            target: progressBar
            property: "progress"
            from: 0
            to: 1
            duration: 2000 // 2 seconds
            running: true
        }
    }
}
