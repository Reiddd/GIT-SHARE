import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    visible: true

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Rectangle{
        property int animatedValue: 0
        color: "lightgray"
        width: animatedValue
        height: 400 - animatedValue

        SequentialAnimation on animatedValue{
            loops: Animation.Infinite
            PropertyAnimation{to: 400;duration: 1000}
            PropertyAnimation{to: 0;duration: 1000}
        }

        Text{
            anchors.centerIn: parent
            text: parent.animatedValue
        }
    }
}

