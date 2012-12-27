import QtQuick 1.1
import jp.arisin.hugu 0.1

Hugu {
    id: hugu
    width: 300
    height: 300

    MouseArea {
        anchors.fill: parent

        onClicked: Qt.quit()
    }

    Text {
        x: 20
        y: 20
        text: "0.00"
        id: text1
        opacity: 0.600
        style: Text.Normal
        font.bold: true
        font.pointSize: 12
        font.family: "みかちゃん"
    }

    Text {
        id: text2
        x: 0
        y: 0
        height: 20
        text: "CPU: 0.00/0.00 ℃"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        style: Text.Normal
        font.bold: true
        font.family: "みかちゃん"
        font.pointSize: 12
        opacity: 0.600
    }

    Image {
        id: image
        anchors.fill: parent
        opacity: 1
        source: "hugu_img.png"
    }

    Timer {
        interval: 10
        running: true
        repeat: true
        onTriggered: {
            //text1.text = Date().toString();
          text1.text = "time: " + hugu.elapsed.toFixed(2) + " 秒"
        }
    }

    Timer {
        interval: 500
        running: true
        repeat: true
        onTriggered: {
            text2.text = "CPU: " + hugu.temperature.toFixed(2) +" / " + hugu.temperature_critical.toFixed(2) + " ℃";
            hugu.state = (hugu.state != "metsukiwaruuuu") ? "metsukiwaruuuu" : "pachikuri"
        }
    }

    states: [
        State {
            name: "pachikuri"
        },
        State {
            name: "metsukiwaruuuu"

            PropertyChanges {
                target: image
                source: "hugu_img2.png"
            }
        }
    ]
}
