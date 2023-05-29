import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    id: window
    width: 800
    height: 640
    visible: true
    title: qsTr("Brewery Assignment by Tero Rantanen")
    color: "#1A120B"

    Text {
        id: mainheader
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: textcolumnbox.top
        bottomPadding: Screen.height / 50
        text: qsTr("Breweries in Georgia")
        font.pixelSize: Screen.height / 25
        horizontalAlignment: Text.AlignHCenter
        font.bold: true
        font.family: "Arial"

        color: "#E5E5CB"
    }

    Rectangle {
        id: textcolumnbox
        color: "#3C2A21"
        radius: 10
        border.width: 2
        border.color: "#D5CEA3"
        anchors.centerIn: parent
        width: textGroup.width + 20
        height: textGroup.height + 20
    Column {
        id: textGroup
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 5

        Text {
            id: southtitle
            text: qsTr("Southernmost Brewery:")
            font.pixelSize: Screen.height / 30
            font.bold: true
            font.family: "Arial"
            color: "#E5E5CB"
        }

        Text {
            id: southtext
            text: brew.southName
            font.pixelSize: Screen.height / 30
            font.family: "Arial"
            color: "#E5E5CB"

            MouseArea{
                id: southMouseArea
                anchors.fill: parent
                onClicked: southPopup.open()
            }

            Popup {
               id: southPopup
               modal: true
               focus: true
               closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
               width: Screen.width * 0.9

               anchors.centerIn: window
                 Text{
                    text: brew.southpopuptext
                    font.pixelSize: Screen.height / 70
                    font.bold: true
                    font.family: "Arial"
                 }
            }
        }

        Text {
            id: northtitle
            text: qsTr("Northernmost Brewery:")
            font.pixelSize: Screen.height / 30
            font.bold: true
            font.family: "Arial"
            color: "#E5E5CB"
        }

        Text {
            id: northtext
            text: brew.northName
            font.pixelSize: Screen.height / 30
            font.family: "Arial"
            color: "#E5E5CB"
            MouseArea{
                id: northMouseArea
                anchors.fill: parent
                onClicked: northPopup.open()
            }

            Popup {
               id: northPopup
               modal: true
               focus: true
               closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
               width: Screen.width * 0.9

               anchors.centerIn: window
                 Text{
                    text: brew.northpopuptext
                    font.pixelSize: Screen.height / 70
                    font.bold: true
                    font.family: "Arial"
                 }
            }
        }

        Text {
            id: firsttitle
            text: qsTr("First added Brewery:")
            font.pixelSize: Screen.height / 30
            font.bold: true
            font.family: "Arial"
            color: "#E5E5CB"
        }

        Text {
            id: firsttext
            text: brew.firstName
            font.pixelSize: Screen.height / 30
            font.family: "Arial"
            color: "#E5E5CB"

            MouseArea{
                id: firstMouseArea
                anchors.fill: parent
                onClicked: firstPopup.open()
            }

            Popup {
               id: firstPopup
               modal: true
               focus: true
               closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
               width: Screen.width * 0.9

               anchors.centerIn: window
                 Text{
                    text: brew.firstpopuptext
                    font.pixelSize: Screen.height / 70
                    font.bold: true
                    font.family: "Arial"
                 }
            }
        }

        Text {
            id: infotext
            text: "Click on a brewery name for more info"
            font.family: "Arial"
            font.pixelSize: Screen.height / 50
            horizontalAlignment: Text.AlignHCenter
            color: "#E5E5CB"
        }
    }
    }

    Text {
        id: creator
        text: "Tero Rantanen 5/2023"
        font.family: "Arial"
        font.pixelSize: Screen.height/50
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#E5E5CB"
    }
}
