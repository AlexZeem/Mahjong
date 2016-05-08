import QtQuick 2.0
import QtQuick.Controls 1.3

Item {
    id: root

    Rectangle {
        anchors.fill: parent
        color: "white"
    }

    Button {
        id: addNew
        text: qsTr("Add new")
        anchors {
            top: parent.top
            left: parent.left
        }
        onClicked: {
            //gmediator.gamesModel.addEntry()
        }
    }

    Button {
        id: deleteSelected
        text: qsTr("Delete")
        anchors {
            top: parent.top
            right: parent.right
        }
        enabled: false//gamesTable.selectedRow > -1 ? true : false
        onClicked: {
            //gmediator.gamesModel.removeEntry(gamesTable.selectedRow)
        }
    }

    HandsTable {
        id: handsTable
        anchors {
            top: addNew.bottom
            topMargin: 15
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
    }
}
