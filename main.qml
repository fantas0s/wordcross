import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import GameGridModel 1.0
import ProposalTileStore 1.0
import "."

Window {
    id: rootWindow
    property bool moveOngoing: false
    property int indexOnMove: -1
    function dropAttemptToGrid() {
        var areaStartX = tableView.x
        var areaStartY = tableView.y
        var areaEndX = areaStartX + tableView.width
        var areaEndY = areaStartY + tableView.height
        if ((floatingTile.x > areaStartX) &&
            (floatingTile.y > areaStartY) &&
            (floatingTile.x < (areaEndX-floatingTile.width)) &&
            (floatingTile.y < (areaEndY-floatingTile.height))) {
            ProposalTileStore.removeTile(indexOnMove)
        }
    }
    visible: true
    width: Constants.windowWidth
    height: Constants.windowHeight
    title: qsTr("Poffutin's Word Game")
    color: "black"

    ColumnLayout {
        anchors.fill: parent
        Rectangle {
            width: Constants.windowWidth
            height: Constants.windowHeight / 10
            color: "darkgray"
            z: 10
        }
        TableView {
            id: tableView
            width: Constants.windowWidth
            model: GameGridModel{}
            delegate: TileDelegate{}
            Layout.fillHeight: true
            Rectangle {
                width: 20
                height: 20
                color: "blue"
                radius: 10
            }
        }
        LetterRow {
            width: Constants.windowWidth
            height: Constants.windowHeight / 10
            z: 10
        }
    }
    UITile {
        id: floatingTile
        text: "8"
        pointsText: "12"
        visible: rootWindow.moveOngoing
    }
}
