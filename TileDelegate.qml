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
        Rectangle {
            anchors.centerIn: parent
            width: parent.width / 2
            height: parent.height / 2
            radius: width / 2
            color: Constants.startMarkColor
            visible: isStartSlot
        }
    }
    UITile {
        id: tileRect
        anchors.centerIn: parent
        visible: !slotIsEmpty
        text: letter
        pointsText: points
    }
}
