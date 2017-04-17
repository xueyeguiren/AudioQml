/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Data Visualization module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef AUDIOLEVELS_H
#define AUDIOLEVELS_H

#include "qaudio.h"
#include<QAudioOutput>
#include <QObject>
#include <QImage>
#include <QDebug>
#include <QWaitCondition>
#include <QQuickImageProvider>
#include <unistd.h>
#include <QtMath>
#include <global.h>
#include <speechrecognizer.h>
#include <structstore.h>
#include <speechsynthesis.h>
class AudioLevelsIODevice;
QT_BEGIN_NAMESPACE
class QAudioInput;
QT_END_NAMESPACE
class AudioLevels : public QObject,public QQuickImageProvider
{
    Q_OBJECT

public:
    //构造函数
    AudioLevels( QObject *parent = 0);
    //请求生成image，固定格式用来qml调用c++image
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
    //新线程的方法, 用来循环延时存入数组
    static void* gatherDataFun(void* arg);
    //新线程的方法, 用来语音识别
    static void* srFun(void* arg);
    //创建新线程，用来处理循环放入216个value值至数组，供图像函数调用生成image
    void createThread(AudioLevelsIODevice *m_device);
    //开始session
    void startSession();
    //析构函数
    ~AudioLevels();
    //存放生成imge图像数据的数组
    static float lineStr[216];
    //新线程继续执行的条件，换句话就是线程结束的条件
    static bool isStopThread;
    //用来装着m_device,m_audioInput，结束时候用
    static struct audioInput_struct as;
    //静态struct
    static struct Global::speech_rec rec;
    //静态session_id
//    static char* session_id;
    QFile* inputFile;//播放文件
    QAudioOutput *audio;//output
public slots:
    //打开声卡capture
    void startRecord();
    //关闭声卡capture
    void stopRecord();
    //测试语音合成
    void testTTS();
    //语音播放
    int startPlayer(QString fileName);
    //结束播放
    void finishedPlaying(QAudio::State state);
private:
    //! [0]
   AudioLevelsIODevice *m_device;
   QAudioInput *m_audioInput;
    //! [0]
};

#endif
