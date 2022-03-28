import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 150
    height: 50
    visible: true
    flags: Qt.FramelessWindowHint

//    Text {
//        id: content
//        color: "#FF0000"
//        text: qsTr("+10.00%")
//        font.pixelSize: 25
//        font.bold: true
//        font.family: Consolas
//        font.letterSpacing: 1
//        anchors.centerIn: parent
//    }

    TableView{
        id: content
        anchors.fill: parent
    }
}
