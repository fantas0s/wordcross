import QtQuick 2.15
import AvailableTileListModel 1.0

Rectangle {
    color: "darkgray"
   ListView {
       anchors.centerIn: parent
       width: parent.width
       height: Constants.tileHeight
       orientation: Qt.Horizontal;
       model: AvailableTileListModel{}
       delegate: TileDelegate {
       }
       spacing: 10
   }
}
