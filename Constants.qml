pragma Singleton
import QtQuick 2.15
import QtQuick.Window 2.15

QtObject {
    property int windowWidth: Screen.width
    property int windowHeight: Screen.height
    property int tileBase: Screen.width > Screen.height ? Screen.height : Screen.width
    property int tileWidth: tileBase / 15
    property int tileHeight: tileBase / 15
    property color tileColor: "#FFFFEE"
    property color tileTextColor: "black"
    property color slotBorderColor: "black"
    property color emptySlotColor: "darkgray"
    property color startMarkColor: "green"
}
