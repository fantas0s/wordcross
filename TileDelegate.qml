import QtQuick 2.15
import TileStorage 1.0
import ProposalTileStore 1.0

Rectangle {
    id: delegateRoot
    width: Constants.tileWidth
    height: Constants.tileHeight
    property bool inBottomRow: false
    property int gridRow: inBottomRow ? index : row
    property int gridColumn: inBottomRow ? 0 : column
    implicitWidth: Constants.tileWidth
    implicitHeight: Constants.tileHeight
    color: model.isInGrid ? Constants.slotBorderColor : "transparent"
    Rectangle {
        id: emptySlot
        anchors.centerIn: parent
        width: parent.width - Constants.tileWidth / 10
        height: parent.height - Constants.tileWidth / 10
        color: Constants.emptySlotColor
        visible: model.slotIsEmpty
        Rectangle {
            anchors.centerIn: parent
            width: parent.width / 2
            height: parent.height / 2
            radius: width / 2
            color: Constants.startMarkColor
            visible: model.isStartSlot
        }
        DropArea {
            id: dragAboveTarget
            anchors.fill: parent
            onDropped: {
                if (inBottomRow) {
                    if (model.slotIsEmpty) {
                        ProposalTileStore.setTile(index, drag.source.text)
                        drop.accept(Qt.MoveAction)
                    } else {
                        drop.accept(Qt.IgnoreAction)
                    }
                } else {
                    if (model.slotIsEmpty) {
                        TileStorage.addTile(delegateRoot.gridRow, delegateRoot.gridColumn, drag.source.text)
                        drop.accept(Qt.MoveAction)
                    } else {
                        drop.accept(Qt.IgnoreAction)
                    }
                }
            }
        }
    }
    UITile {
        id: tileRect
        property int modelRow: delegateRoot.inBottomRow ? index : delegateRoot.gridRow
        property int modelColumn: delegateRoot.gridColumn
        visible: !model.slotIsEmpty
        text: model.letter
        pointsText: model.points
        isNew: model.isNew
        isRecent: model.isRecent
        x: Constants.tileWidth / 20
        y: Constants.tileWidth / 20
        Drag.active: dragMouseArea.drag.active
        Drag.hotSpot.x: width / 2
        Drag.hotSpot.y: height / 2
        MouseArea {
            id: dragMouseArea
            anchors.fill: parent
            enabled: model.isNew || delegateRoot.inBottomRow
            drag.target: tileRect
            drag.axis: Drag.XAndYAxis
            onReleased: {
                if (tileRect.Drag.target) {
                    if (tileRect.Drag.drop() !== Qt.IgnoreAction) {
                        if (delegateRoot.inBottomRow) {
                            ProposalTileStore.setTile(index, ".")
                        } else {
                            TileStorage.removeTile(delegateRoot.gridRow, delegateRoot.gridColumn)
                        }
                    }
                }
                /* Return to where it started */
                tileRect.x = Constants.tileWidth / 20
                tileRect.y = Constants.tileWidth / 20
            }
        }
    }
}
