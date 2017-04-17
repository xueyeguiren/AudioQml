#include "speechrecognizer.h"
#include <audiolevels.h>
SpeechRecognizer::SpeechRecognizer()
{

}
bool SpeechRecognizer::isFirstStop=true;
//进行登陆及开始新会话
const char* SpeechRecognizer::startSession()
{
    int ret = MSP_SUCCESS;
    const char*		session_id = NULL;
    int				errcode = MSP_SUCCESS;
    MSPLogin(NULL, NULL, login_params);
    if (MSP_SUCCESS != ret)	{
           qDebug()<<"MSPLogin failed , Error code"<<ret;
        }
    session_id = QISRSessionBegin(NULL, session_begin_params, &errcode);
    if (MSP_SUCCESS != errcode)
    {
        qDebug()<<"\nQISRSessionBegin failed! error code"<<errcode;
//        return errcode;
    }
    return session_id;
}

//进行语音识别
int SpeechRecognizer::startSpeechRecognizer(struct Global::speech_rec* rec)
{
    int ret;
    const char* result;
    if(isFirstStop)
    {
    ret= QISRAudioWrite(rec->session_id,rec->data,rec->length,rec->audio_status,&rec->ep_stat,&rec->rec_stat);
    if (ret) {
        qDebug()<<"QISRAudioWrite Fail!";
        return ret;
    }

    if((rec->rec_stat==MSP_REC_STATUS_SUCCESS||rec->ep_stat==MSP_EP_AFTER_SPEECH)&&isFirstStop)
    {
    result=QISRGetResult(rec->session_id,&rec->rec_stat,0,&ret);
    qDebug()<<"result--------------------"<<result;
//    stopSession(rec->session_id);
    createThreadStop();

    }
    }
}

//退出登陆及结束会话
int SpeechRecognizer::stopSession(const char* session_id)
{
    QISRSessionEnd(session_id,"normal");
    MSPLogout();
//    setStop();
}

//void SpeechRecognizer:: end_sr_on_error(struct speech_rec *sr, int errcode)
//{
//    if(sr->aud_src == SR_MIC)
//        LinuxRecord::stop_record(sr->recorder);

//    if (sr->session_id) {
//        if (sr->notif.on_speech_end)
//            sr->notif.on_speech_end(errcode);

//        QISRSessionEnd(sr->session_id, "err");
//        sr->session_id = NULL;
//    }
//    sr->state = SR_STATE_INIT;
//}
void SpeechRecognizer:: createThreadStop()
{
    pthread_attr_t attr;
    pthread_t pid;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    //关闭录音及audio新线程
    pthread_create(&pid, &attr, threadStop,NULL);
}
void* SpeechRecognizer::threadStop(void* arg)
{
    isFirstStop=false;
    AudioLevels audioLevels;
    audioLevels.stopRecord();
    return NULL;
}
