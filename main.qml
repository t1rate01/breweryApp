import QtQuick.Window 2.15
import QtQuick 2.15
import QtQuick.Controls 2.15

Window {
     //@disable-check M16
    //@disable-check M16
    //@disable-check M16
    visible: true
    //@disable-check M16
    title: qsTr("Brewery Assignment by Tero Rantanen")
    //@disable-check M16
    modality: Qt.WindowModal
    //@disable-check M16
    Text {
        id: infot1
        x: 42
        y: 47
        text: qsTr("Infot 1")
        font.pixelSize: 12
    }

    Text {
        id: infot2
        x: 44
        y: 93
        text: qsTr("Infot 2")
        font.pixelSize: 12
    }

    Text {
        id: infot3
        x: 47
        y: 161
        text: qsTr("Infot 3")
        font.pixelSize: 12
        state: "hrerhreh"
    }
}
