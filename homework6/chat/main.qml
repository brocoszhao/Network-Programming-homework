import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Window 2.2

//Window {
//    visible: true
//    width: 540
//    height: 960
//    title: qsTr("Hello World")

//    MainForm {
//        anchors.fill: parent
//        mouseArea.onClicked: {
//            console.log(qsTr('Clicked on background. Text: "' + textEdit.text + '"'))
//        }
//    }

//}
ApplicationWindow {
    width: 540
    height: 960
    visible: true
    StackView {
            id: stackView
            anchors.fill: parent
            initialItem: ContactPage {width: ListView.view.width - ListView.view.leftMargin - ListView.view.rightMargin}
        }

    Page {
        anchors.fill: parent
        header: Label {
            padding: 10
            text: qsTr("Contacts")
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    ListView {
               id: listView
               anchors.fill: parent
               topMargin: 48
               leftMargin: 48
               bottomMargin: 48
               rightMargin: 48
               spacing: 20
               model: ["Albert Einstein", "Ernest Hemingway", "Hans Gude"]
               delegate: ItemDelegate {
                   text: modelData
                   width: listView.width - listView.leftMargin - listView.rightMargin
                   height: avatar.implicitHeight
                   leftPadding: avatar.implicitWidth + 32

                   Image {
                       id: avatar
                       source: "qrc:/" + modelData.replace(" ", "_") + ".png"
                   }
               }
           }
}

