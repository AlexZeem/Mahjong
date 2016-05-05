import QtQuick 2.0
import QtQuick.Controls 1.3

Item {
    id: root

    TableView {
        id: tableView
        width: 500
        frameVisible: true

        TableViewColumn {
            id: dateColumn
            title: "Date"
            role: "date"
            movable: false
            resizable: false
            width: tableView.viewport.width / 6
        }

        TableViewColumn {
            id: winnerColumn
            title: "Winner"
            role: "winner"
            movable: false
            resizable: false
            width: tableView.viewport.width / 6
        }

        TableViewColumn {
            id: score1Column
            title: "Score 1"
            role: "score1"
            movable: false
            resizable: false
            width: tableView.viewport.width / 6
        }

        TableViewColumn {
            id: score2Column
            title: "Score 2"
            role: "score2"
            movable: false
            resizable: false
            width: tableView.viewport.width / 6
        }

        TableViewColumn {
            id: score3Column
            title: "Score 3"
            role: "score3"
            movable: false
            resizable: false
            width: tableView.viewport.width / 6
        }

        TableViewColumn {
            id: score4Column
            title: "Score 4"
            role: "score4"
            movable: false
            resizable: false
            width: tableView.viewport.width / 6
        }

        model: ListModel {
            id: countModel
            ListElement {
                player1wind: "E"
                player1mahjong: true
                player1point: 21
                player1score: 41
                player2wind: "S"
                player2mahjong: false
                player2point: 8
                player2score: 8
                player3wind: "W"
                player3mahjong: false
                player3point: 2
                player3score: 4
                player4wind: "N"
                player4mahjong: false
                player4point: 6
                player4score: 12
            }
        }

            //gmediator.gamesModel

        /*itemDelegate: Component {
            id: editableDelegate
            Item {
                Text {
                    width: parent.width
                    anchors.margins: 4
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    elide: styleData.elideMode
                    text: styleData.value !== undefined ? styleData.value : ""
                    color: styleData.textColor
                    visible: !styleData.selected
                }
                Loader { // Initialize text editor lazily to improve performance
                    id: loaderEditor
                    anchors.fill: parent
                    anchors.margins: 4
                    Connections {
                        target: loaderEditor.item
                        onAccepted: {
                            gmediator.gamesModel.editItem(loaderEditor.item.text, styleData.row, styleData.column, styleData.role)
                            tableView.selection.deselect(0, tableView.model.length - 1)
                        }
                    }
                    sourceComponent: styleData.selected ? ( styleData.role === "winner" ? winnerEditor : editor) : null
                    Component {
                        id: editor
                        TextInput {
                            id: textinput
                            color: styleData.textColor
                            text: styleData.value
                            MouseArea {
                                id: mouseArea
                                anchors.fill: parent
                                hoverEnabled: true
                                onClicked: textinput.forceActiveFocus()
                            }
                        }
                    }
                    Component {
                        id: winnerEditor
                        ComboBox {
                            id: winners
                            model: gmediator.gamesModel.players(tableView.currentRow)
                            currentIndex: 0

                            onCurrentIndexChanged: {
                                if (currentText !== "") {
                                    if (styleData.row > -1)
                                        gmediator.gamesModel.editItem(currentText, styleData.row, styleData.column, styleData.role)
                                    tableView.selection.deselect(0, tableView.model.length - 1)
                                }
                            }
                        }
                    }
                }
            }
        }*/
    }
}