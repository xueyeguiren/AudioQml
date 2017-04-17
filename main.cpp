#include <QGuiApplication>
#include <QtQml>
//#include <QQmlApplicationEngine>
#include <QCoreApplication>
#include "audiolevels.h"
#include <global.h>
#include <QDebug>
int main(int argc, char *argv[])
{
//    qDebug()<<"test"<<test123;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    qmlRegisterType<AudioLevels>("com.bodawb.AudioLevels",1,0,"AudioLevels");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    engine.addImageProvider("wavePic",new AudioLevels);

    /**
     * 为了在c++调用qml，可以实现在类内来调用
     *步骤如下:
     * 1.在一个类Global，声明和定义一个静态变量用来装载rootitem
     * 2.main方法内调用global下的setRooItem
     * 3.其他类内调用global的getRootItem即可
     **/

    QList<QObject *> rootItems= engine.rootObjects();
    QObject *rootItem=rootItems.at(0);
    Global gl;
    gl.setRootItem(rootItem);
    qDebug()<<rootItem->objectName();
    return app.exec();
}
