import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import com.bodawb.AudioLevels 1.0
ApplicationWindow {
    visible: true
    width: 1080
    height: 615
    title: qsTr("Hello World")
    property int  num:0;
    property int  time:0;
    property int  counter:60000;
    objectName: "root"

    Rectangle {
        id:rectangle_main
        width: parent.width*0.98;
        height:parent.width*0.5;
        anchors.topMargin: 10;
        anchors.horizontalCenter: parent.horizontalCenter;
        border.color: "#707070"
        color: "transparent"
        Image {
            id:image_qrCode;
//            source: "file"
            width: parent.width;
            height: parent.height;
        }
    }
    //开始进行图形生成及录音
    Rectangle{
        id:btn_showPic;
        anchors.top: rectangle_main.bottom;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.horizontalCenterOffset: -100;
        width: 100;
        height: 50;
        border.color: "black"
//        color: "red";
//        anchors.left: parent.left;
        MouseArea{
            width: parent.width;
            height: parent.height;
            onClicked: {
                btn_showPic.color="red";
                al.startRecord();//开始声卡capture
                countdown.start();//开始计时，每隔这么长时间取出一张image显示
            }
            onReleased: {

            }
        }
        Text {
            id: name
            text: qsTr("开始");
            anchors.verticalCenter: parent.verticalCenter;
            anchors.horizontalCenter: parent.horizontalCenter;
            font.pixelSize: 24;
        }
    }
    //结束录音及图形
    Rectangle{
        id:btn_stopic;
        anchors.top: rectangle_main.bottom;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.horizontalCenterOffset: 100;
        width: 100;
        height: 50;
        border.color: "black"
        objectName: "stop"
//        color: "red";
//        anchors.left: parent.left;
        MouseArea{

            width: parent.width;
            height: parent.height;
//            objectName: "ma";
            onClicked: {
                countdown.stop();//结束计时
                al.stopRecord();//结束声卡capture
            }
            //用来在c++中调用，不用onclicked因为他们需要参数
        }
        Text {
            id: name2
            text: qsTr("结束");
            anchors.verticalCenter: parent.verticalCenter;
            anchors.horizontalCenter: parent.horizontalCenter;
            font.pixelSize: 24;
        }
    }
    //测试语音合成
    Rectangle{
        id:btn_testTTS;
        anchors.top: rectangle_main.bottom;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.horizontalCenterOffset: 200;
        width: 100;
        height: 50;
        border.color: "black"
        objectName: "testTTS"
        MouseArea{
            width: parent.width;
            height: parent.height;
            onClicked: {
//                al.testTTS();
//                al.startPlayer("/home/pi/wav/server.wav");
            }
        }
        Text {
            id: name3
            text: qsTr("结束");
            anchors.verticalCenter: parent.verticalCenter;
            anchors.horizontalCenter: parent.horizontalCenter;
            font.pixelSize: 24;
        }
    }

    AudioLevels{
        id:al;
    }

    Timer{
            id:countdown
            interval:100;
            repeat: true
            triggeredOnStart: true  //这一设置保证了立即触发，如果没有，你会发现有延迟
            onTriggered: {
                if(num==0)
                    num=1;
                else{
                    num=0;
                }
                image_qrCode.source="image://wavePic/"+num;
                counter -= 1;//倒计时
                time+=1;
                if(counter<=0)
                {
                    countdown.stop();
                }
            }
    }
}
