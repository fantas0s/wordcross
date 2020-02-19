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
       }
       spacing: 10
   }
}
