import QtQuick 2.12

Rectangle {
    id: tileRoot
    width: Constants.tileWidth * 0.9
    height: Constants.tileHeight * 0.9
    property alias text: tileLetter.text
    property alias pointsText: tilePoints.text
    radius: Constants.tileWidth * 0.1
    color: Constants.tileColor
    Text {
        id: tileLetter
        anchors.centerIn: parent
        text: letter
        color: Constants.tileTextColor
        font.pixelSize: 7 * Constants.tileWidth / 10
    }
    Text {
        id: tilePoints
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 3
        anchors.rightMargin: 3
        text: pointsText
        color: Constants.tileTextColor
        font.pixelSize: 6 * Constants.tileWidth / 25
    }
}
