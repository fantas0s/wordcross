import QtQuick 2.12
import AvailableTileListModel 1.0

Rectangle {
    color: "darkgray"
   ListView {
       anchors.centerIn: parent
       width: parent.width
       height: Constants.tileHeight
       orientation: Qt.Horizontal;
       model: AvailableTileListModel{}
       delegate: UITile {
           text: letter
           pointsText: points
           MouseArea {
               anchors.fill: parent
               drag.target: floatingTile
               drag.axis: Drag.XAndYAxis
               onPressed: {
                   rootWindow.moveOngoing = true
                   rootWindow.indexOnMove = index
                   floatingTile.x = mapToGlobal(mouse.x, mouse.y).x - (Constants.tileWidth * 1.5)
                   floatingTile.y = mapToGlobal(mouse.x, mouse.y).y - (Constants.tileWidth * 0.5)
                   floatingTile.text = letter
                   floatingTile.pointsText = points
               }
               onReleased: {
                   rootWindow.moveOngoing = false
                   rootWindow.dropAttemptToGrid()
               }
           }
       }
       spacing: 10
   }
}
