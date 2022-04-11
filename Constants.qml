pragma Singleton
import QtQuick 2.15
import QtQuick.Window 2.15

QtObject {
    property int windowWidth: 800 //Screen.width
    property int windowHeight: 600 //Screen.height
    property int tileBase: Screen.width > Screen.height ? Screen.height : Screen.width
    property int tileWidth: tileBase / 15
    property int tileHeight: tileBase / 15
    property int tileRowHeight: tileHeight + 10
    property int buttonRowHeight: tileBase / 20
    property color tileColor: "#FFFFDD"
    property color newTileColor: "#FFFFFF"
    property color recentTileColor: "#FFFFBB"
    property color tileTextColor: "black"
    property color slotBorderColor: "black"
    property color emptySlotColor: "darkgray"
    property color startMarkColor: "green"
}
