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

#include "audiolevelsiodevice.h"
#include "audiolevels.h"

#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioInput>

using namespace QtDataVisualization;

AudioLevels::AudioLevels( QObject *parent)
    : QObject(parent),QQuickImageProvider(QQuickImageProvider::Image),
      m_device(0),
      m_audioInput(0)
{

}

AudioLevels::~AudioLevels()
{
    qDebug()<<"析构";
    if (m_audioInput)
        m_audioInput->stop();
    if (m_device)
        m_device->close();
    delete m_audioInput;
}
//static 需要在类外进行初始化
float AudioLevels:: lineStr[216];
bool AudioLevels::isStopThread=false;
//char* AudioLevels:: session_id;
struct Global::speech_rec AudioLevels:: rec;
struct audioInput_struct AudioLevels::as;
void AudioLevels::startRecord()
{
    //! [0]

    QAudioDeviceInfo inputDevice = QAudioDeviceInfo::defaultInputDevice();
    QAudioDeviceInfo outDevice = QAudioDeviceInfo::defaultOutputDevice();
    QList<QAudioDeviceInfo> qq=QAudioDeviceInfo:: availableDevices(QAudio::AudioInput);
//int i=0;
//    foreach (const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioInput))
//    {
//        qDebug() <<"数量"<<i<< "Device name: " << qq.at(i).deviceName();
//        i++;
//    }
//    inputDevice=qq.at(13);
    if (inputDevice.supportedSampleRates().size() > 0
            && inputDevice.supportedChannelCounts().size() > 0
            && inputDevice.supportedSampleSizes().size() > 0
            && inputDevice.supportedCodecs().size() > 0) {
        QAudioFormat formatAudio;
        formatAudio.setSampleRate(16000);
        formatAudio.setChannelCount(inputDevice.supportedChannelCounts().at(0));
        qDebug()<<"codec"<<inputDevice.supportedSampleSizes().at(1);//16
        formatAudio.setSampleSize(inputDevice.supportedSampleSizes().at(1));
        qDebug()<<"codec"<<inputDevice.supportedCodecs().at(0);
        formatAudio.setCodec(inputDevice.supportedCodecs().at(0));
        formatAudio.setByteOrder(QAudioFormat::LittleEndian);
        formatAudio.setSampleType(QAudioFormat::SignedInt);
        qDebug()<<"是否支持"<<inputDevice.isFormatSupported(formatAudio);
        m_audioInput = new QAudioInput(inputDevice, formatAudio, this);
#ifdef Q_OS_MAC
        // OS X seems to wait for entire buffer to fill before calling writeData, so use smaller buffer
        m_audioInput->setBufferSize(256);
#else
        m_audioInput->setBufferSize(40000);
        qDebug()<<"m_audioInput"<<m_audioInput->bufferSize();
#endif
        m_device = new AudioLevelsIODevice();
        m_device->open(QIODevice::WriteOnly);
        //向struct赋值
        as.m_audioInput=m_audioInput;
        as.m_device=m_device;
        startSession();//在此开始新对话
        m_audioInput->start(m_device);
//        Global gl;
//        qDebug()<<gl.getRootItem()->objectName();
        isStopThread=false;
        createThread(m_device);
    } else {
        // No graph content can be shown, so add a custom warning label
    }
    //! [0]
}

QImage  AudioLevels::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
 {

    QImage qe;
//    AudioLevelsIODevice* ae;
//    qe=ae->getImage();
    WavePaint wt;
//    qDebug()<<"requestImage----->1";
    qe=wt.drawImage(lineStr,216);
//    qDebug()<<"requestImage----->2"<<qe;
    return qe;
 }

void AudioLevels::createThread(AudioLevelsIODevice *m_device)
{
    pthread_attr_t attr;
    pthread_t pid1;
    pthread_t pid2;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    //采集数据新线程
    pthread_create(&pid1, &attr, gatherDataFun, (void*)m_device);
    //语音识别新线程
//    pthread_create(&pid2, &attr, srFun, (void*)as);
    qDebug()<<"测试新线程是否结束";
}
//void* AudioLevels::srFun(void* arg)
//{
// SpeechRecognizer sr;//处理语音识别的类
// struct Global::speech_rec* rec=new struct Global::speech_rec;//struct 记录语音识别过程中用到的一些变量
// struct Global::speech_rec* rec_record;//用来接收从录音类传来的数据
// struct audioInput_struct * as=(struct audioInput_struct*)arg;//继承了声卡录音接口的类，处理从声卡传送过来的数据
// rec->ep_stat = MSP_EP_LOOKING_FOR_SPEECH;
// rec->rec_stat = MSP_REC_STATUS_SUCCESS;
// rec->audio_status = MSP_AUDIO_SAMPLE_FIRST;
// int ret;//根据返回值判断运行情况


// while(!isStopThread){
//    rec_record=as->m_device->getAudioData();
//    if(!rec_record->start)
//         continue;
//    rec->data=rec_record->data;
//    rec->length=rec_record->length;
//    sr.startSpeechRecognizer(rec,as);
//    rec->audio_status = MSP_AUDIO_SAMPLE_CONTINUE;
////        qDebug()<<"while recyle";
// }
// delete rec;
// qDebug()<<"srFun";
// return NULL;
//}

void* AudioLevels::gatherDataFun(void* arg)
{
  AudioLevelsIODevice *m_device=(AudioLevelsIODevice *)arg;//继承了声卡录音接口的类，处理从声卡传送过来的数据
  struct Global::speech_rec* rec_record;//用来接收从录音类传来的数据
  memset(lineStr,0.0,216);//重新分配linestr
  int count=0;//统计延时的次数
  int silentTimes=0;//方差小于某个值的次数，即换算成不说话的时间，当达到一定事件后就判断说话结束
  SpeechRecognizer sr;
  char* result;
  while(1){
     usleep(60000);
     result=sr.result;
     if(!result==NULL)
     {
         usleep(90000);
         break;
     }
     count+=1;
     rec_record=m_device->getAudioData();
     if(!rec_record->start)
         continue;
     lineStr[0]=rec_record->value;
//     qDebug()<<"lineStr"<<lineStr[0];
     for(int j=215;j>=1;j--)
     {
         lineStr[j]=lineStr[j-1];
     }
     //如果60ms*40=2.4s内,lineStr的值一直小于一定范围，就判断语音对话结束
 //    if(count>=40)//先让录音开始2.5s左右
     {
         if(lineStr[0]<50)//50一般可以
             silentTimes+=1;
         else{
             silentTimes=0;
         }
     }
     if(silentTimes>=40)
     {
         qDebug()<<"可以判断说话停止了";
         silentTimes=0;
//         break;
     }
  }
  qDebug()<<"while循环";
//  free(lineStr);

  return NULL;
}

void AudioLevels::stopRecord()
{
    qDebug()<<"是否被调用多次";
    SpeechRecognizer sr;
    sr.stopSession(rec.session_id);
    QAudio::State st;
    if (as.m_device)
        as.m_device->close();
    if (as.m_audioInput)
    {
        as.m_audioInput->suspend();
        st=as.m_audioInput->state();
    }

    qDebug()<<"stop-state"<<st;
    delete m_device;
    m_device=NULL;
    sr.isFirstStop=true;
}

void AudioLevels::startSession()
{
    this->rec.ep_stat = MSP_EP_LOOKING_FOR_SPEECH;
    this->rec.rec_stat = MSP_REC_STATUS_SUCCESS;
    this->rec.audio_status = MSP_AUDIO_SAMPLE_FIRST;
    SpeechRecognizer sr;
    const char* session_id;//根据返回值判断运行情况
    /******************************************会话on*/
    session_id=sr.startSession();
    qDebug()<<"session_id"<<session_id;
//    this->session_id=session_id;//保存至本地静态区域
    this->rec.session_id=session_id;
     /******************************************会话off*/
}

void AudioLevels:: testTTS()
{
    SpeechSynthesis ss;
    ss.StartCompose("君不见黄河之水天上来");
}


