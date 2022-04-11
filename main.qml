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
        Buttons {
            width: rootWindow.width
            height: Constants.buttonRowHeight
            z: 10
        }
        TableView {
            id: tableView
            width: rootWindow.width
            model: GameGridModel{}
            delegate: TileDelegate{}
            Layout.fillHeight: true
        }
        LetterRow {
            width: rootWindow.width
            height: Constants.tileRowHeight
            z: 10
        }
    }
}
