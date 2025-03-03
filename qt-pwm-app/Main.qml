import QtQuick
import QtQuick.Controls

ApplicationWindow {
    visible: true
    width: 1920
    height: 1080
    title: "LED Media Controller"

    StackView {
        id: stackView
        initialItem: homePage
        anchors.fill: parent
    }

    // Home Page Component
    Component {
        id: homePage

        Page {
            // Gradient Background
            Rectangle {
                anchors.fill: parent
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#E8F9FF" }
                    GradientStop { position: 1.0; color: "#FBFBFB" }
                }
            }

            // Logo at the top (centered)
            Image {
                source: "qrc:/itilogo.png"
                width: parent.width / 7
                height: parent.width / 7
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 50
                fillMode: Image.PreserveAspectFit
            }

            // Centered Text Information
            Column {
                spacing: 12
                anchors.centerIn: parent

                Text {
                    text: "Car Headlights PWM Controller"
                    font.pixelSize: 35
                    font.bold: true
                    color: "grey"
                }
                Text {
                    text: "Developed By: Youssef Mostafa Mohammed"
                    font.pixelSize: 26
                    color: "grey"
                }
                Text {
                    text: "ITI 9months Embedded Systems Program"
                    font.pixelSize: 26
                    color: "grey"
                }
            }

            // "Go to App Page" Button with styled background
            Button {
                text: "Go to App Page"
                width: 200
                height: 50
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 50

                background: Rectangle {
                    color: parent.down ? "grey" : "#A94A4A"
                    radius: 10
                }

                contentItem: Text {
                    text: parent.text
                    font.pixelSize: 20
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                onClicked: stackView.push(appPage)
            }
        }
    }

    // App Page Component
    Component {
        id: appPage

        Page {
            property bool ledState: false

            Rectangle {
                anchors.fill: parent
                color: "#000000"

                // Static logo in top-left with a higher z value
                Image {
                    source: "qrc:/itilogo.png"
                    width: parent.width / 10
                    height: parent.width / 10
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.margins: 20
                    fillMode: Image.PreserveAspectFit
                    z: 1   // Ensures this logo is drawn above the AnimatedImage
                }

                // AnimatedImage that plays the GIF and stops on the final frame
                AnimatedImage {
                    id: animatedImage
                    anchors.fill: parent
                    source: "qrc:/audi.gif"  // default source for LED On
                    playing: false
                    smooth: false

                    onCurrentFrameChanged: {
                        // Stop the animation when the last frame is reached
                        if (currentFrame === frameCount - 1) {
                            playing = false;
                        }
                    }
                }

                // LED Control Button with styled background
                Button {
                    id: controlButton
                    width: parent.width / 8
                    height: parent.height / 9
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 50
                    text: ledState ? "Turn LED Off" : "Turn LED On"
                    font.pointSize: 13

                    background: Rectangle {
                        id: rect1
                        anchors.fill: parent
                        color: "#686D76"
                        opacity: controlButton.pressed ? 1 : 0.3
                        radius: width / 2
                    }

                    contentItem: Text {
                        text: controlButton.text
                        font.pixelSize: 20
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    onClicked: {
                        ledState = !ledState
                        if (ledState) {
                            // LED on: force reload audi.gif, start playing, and ramp up PWM.
                            animatedImage.source = ""
                            animatedImage.source = "qrc:/audi.gif"
                            animatedImage.playing = true
                            backend.asyncRampUpPWM(0, 0, 20000000)
                        } else {
                            // LED off: force reload reverseaudi.gif, start playing, and ramp down PWM.
                            animatedImage.source = ""
                            animatedImage.source = "qrc:/reverseaudi.gif"
                            animatedImage.playing = true
                            backend.asyncRampDownPWM(0, 0, 20000000)
                        }
                    }
                }

                // Back Button with red background
                Button {
                    text: "Back"
                    width: 150
                    height: 40
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.margins: 20

                    background: Rectangle {
                        color: "red"
                        radius: 10
                    }

                    contentItem: Text {
                        text: parent.text
                        font.pixelSize: 20
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    onClicked: stackView.pop()
                }
            }
        }
    }
}
