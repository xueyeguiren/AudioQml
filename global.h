#ifndef GLOBAL_H
#define GLOBAL_H
#include <QObject>
extern int test123;
extern  const char* login_params ;
extern  char* session_begin_params;
class Global
{
public:
    Global();
    static QObject* object;
    void setRootItem(QObject* object);
    QObject* getRootItem();


    struct speech_rec{
        const char* session_id;//session_id
        char* data;// 录音传过来的数据
        int length;//传过来数据的长度
        int ep_stat;//endPointer
        int rec_stat;//录音机状态
        int audio_status;//音频状态

        bool start;       //是否开始录音
        float value;        //处理过用于显示的值
    };

};

#endif // GLOBAL_H
