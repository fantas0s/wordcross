import QtQuick 2.15
import TileStorage 1.0

Rectangle {
    id: delegateRoot
    width: Constants.tileWidth
    height: Constants.tileHeight
    property int gridRow: row
    property int gridColumn: column
    implicitWidth: Constants.tileWidth
    implicitHeight: Constants.tileHeight
    color: model.isInGrid ? Constants.slotBorderColor : "transparent"
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
        DropArea {
            id: dragAboveTarget
            anchors.fill: parent
            onDropped: {
                if (slotIsEmpty &&
                    TileStorage.addTile(delegateRoot.gridRow, delegateRoot.gridColumn, drag.source.text)) {
                    drop.accept(Qt.MoveAction)
                } else {
                    drop.accept(Qt.IgnoreAction)
                }
            }
        }
    }
    UITile {
        id: tileRect
        visible: !slotIsEmpty
        text: model.letter
        pointsText: model.points
        x: Constants.tileWidth / 20
        y: Constants.tileWidth / 20
        Drag.active: dragMouseArea.drag.active
        Drag.hotSpot.x: width / 2
        Drag.hotSpot.y: height / 2
        MouseArea {
            id: dragMouseArea
            anchors.fill: parent
            drag.target: tileRect
            drag.axis: Drag.XAndYAxis
            onReleased: {
                if (tileRect.Drag.target) {
                    if (tileRect.Drag.drop() !== Qt.IgnoreAction) {
                        // remove from where it was
                    }
                }
            }
        }
    }
}
