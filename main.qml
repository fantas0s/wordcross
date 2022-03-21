import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import GameGridModel 1.0
import "."

Window {
    id: rootWindow
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
        }
        LetterRow {
            width: Constants.windowWidth
            height: Constants.windowHeight / 10
            z: 10
        }
    }
}
