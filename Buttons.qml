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
                if (TileStorage.isValid()) {
                    ProposalTileStore.refill();
                    TileStorage.lockTiles();
                }
            }
        }
        Item {
            height: 10
            Layout.fillWidth: true
        }
    }
}
