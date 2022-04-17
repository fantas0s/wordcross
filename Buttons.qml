import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import TileStorage 1.0
import ProposalTileStore 1.0

Rectangle {
    color: "darkgray"
    ColumnLayout {
        anchors.fill: parent
        Button {
            text: "Submit"
            onClicked: {
                switch (TileStorage.checkErrors()) {
                case TileStorage.NoError:
                    ProposalTileStore.refill();
                    TileStorage.lockTiles();
                    break;
                case TileStorage.TilesDetached:
                    _errorPopup.text = qsTr("New tiles must be placed in connection to existing tiles")
                    _errorPopup.open()
                    break;
                case TileStorage.StartWordNotOnStartTile:
                    _errorPopup.text = qsTr("First word must be placed over the center tile")
                    _errorPopup.open()
                    break;
                case TileStorage.TilesNotInSameRowColumn:
                    _errorPopup.text = qsTr("All tiles must be placed to same row or column")
                    _errorPopup.open()
                    break;
                case TileStorage.TilesNotInSameWord:
                    _errorPopup.text = qsTr("All tiles must be placed to same word")
                    _errorPopup.open()
                    break;
                case TileStorage.NoTiles:
                default:
                    _errorPopup.text = qsTr("No tiles placed")
                    _errorPopup.open()
                    break;
                }
            }
        }
        Item {
            height: 10
            Layout.fillWidth: true
        }
    }
}
