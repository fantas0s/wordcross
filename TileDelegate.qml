import QtQuick 2.12

Rectangle {
    id: delegateRoot
    width: Constants.tileWidth
    height: Constants.tileHeight
    implicitWidth: Constants.tileWidth
    implicitHeight: Constants.tileHeight
    color: Constants.slotBorderColor
    Rectangle {
        id: emptySlot
        anchors.centerIn: parent
        width: parent.width - Constants.tileWidth / 10
        height: parent.height - Constants.tileWidth / 10
        color: Constants.emptySlotColor
        visible: slotIsEmpty
    }
    Rectangle {
        id: tileRect
        anchors.centerIn: parent
        width: parent.width - Constants.tileWidth / 10
        height: parent.height - Constants.tileWidth / 10
        color: Constants.tileColor
        visible: !slotIsEmpty
        Text {
            id: letterText
            anchors.centerIn: parent
            text: letter
            color: Constants.tileTextColor
            font.pixelSize: 7 * Constants.tileWidth / 10
        }
        Text {
            id: pointsText
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.topMargin: 3
            anchors.rightMargin: 3
            text: points
            color: Constants.tileTextColor
            font.pixelSize: 6 * Constants.tileWidth / 25
        }
    }
}
