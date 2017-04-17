#ifndef SPEECHRECOGNIZER_H
#define SPEECHRECOGNIZER_H

#include <QObject>
#include <global.h>
#include <qisr.h>
#include <msp_cmn.h>
#include <msp_errors.h>
#include <QDebug>
#include <QAudioInput>
#include <QMouseEvent>
#include <structstore.h>

class AudioLevels;
class SpeechRecognizer
{
public:
    explicit SpeechRecognizer();

    //进行登陆及开始新会话
    const char* startSession();
    //进行语音识别
    int startSpeechRecognizer(struct Global:: speech_rec* rec);
    //退出登陆及结束会话
    int stopSession(const char* session_id);
    //通过qml来结束会话
//    void setStop();
    //通过新线程来结束原来的audioinput及m_device
    void createThreadStop();
    static void* threadStop(void* arg);
    static bool isFirstStop;
    //struct speechrecognizer
};

#endif // SPEECHRECOGNIZER_H
