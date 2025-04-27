import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import com.twogis.test 1.0

Window {
    property string filepath: ""
    property int wordCount: corePresenter.wordCount
    property int progress: corePresenter.progress
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Coding Assignment")
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
                    id: openButton

                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    baseColor: "#175E17"
                    hoverColor: "#A1E8A1"
                    name: "Open File"
                    hintText: mainWindow.filepath
                    onClicked: {
                        corePresenter.resetProcessing()
                        mainWindow.filepath = WindowsHelper.openFileDialog()
                    }
                }
                MyButton {
                    id: stopButton

                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    baseColor: "#750000"
                    hoverColor: "#FF8A8A"
                    name: "Stop processing"

                    onClicked: {
                        corePresenter.resetProcessing()
                        mainWindow.filepath = ""
                    }
                }
            }
        }
        Rectangle {
            anchors.fill: parent
            color: "black"

            MyHisto {
                anchors.fill: parent
                model: corePresenter.mapModel
            }

            MyProgressBar {
                id: progressBar
                anchors.centerIn: parent
                progress: if(mainWindow.wordCount == 0)
                              0
                            else
                              mainWindow.progress / mainWindow.wordCount
                width: 150
                height: 40
                progressColor: "red"
                borderColor: "green"
            }
        }
        footer: Rectangle {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 50
            color: "green"

            RowLayout {
                anchors.fill: parent
                spacing: 2
                MyButton {
                    id: startButton

                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    baseColor: "#4681f4"
                    hoverColor: "#FFFFFF"
                    name: "Start processing"

                    onClicked: {
                        corePresenter.readFile(mainWindow.filepath)
                    }
                }
                MyButton {
                    id: pauseButton

                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    baseColor: "#800020"
                    hoverColor: "#FF94AF"
                    name: "Pause processing"

                    onClicked: {
                        corePresenter.pauseProcessing()
                        console.warn("aboba clicked 4")
                    }
                }
            }
        }
    }


}
