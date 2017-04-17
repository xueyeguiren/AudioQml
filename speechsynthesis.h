#ifndef SPEECHSYNTHESIS_H
#define SPEECHSYNTHESIS_H
#include <global.h>
#include <msp_cmn.h>
#include <msp_errors.h>
#include <qtts.h>
#include <unistd.h>
#include <QDebug>

class SpeechSynthesis
{
public:
    SpeechSynthesis();
    int StartCompose(char *content);
    int text_to_speech(const char* src_text, const char* des_path);
    char* fileName="/home/mjl/general.wav";//用于语音合成对讲的通用与原因会被覆盖

    /* 默认wav音频头部数据 */
    Global::wave_pcm_hdr default_wav_hdr =
    {
        { 'R', 'I', 'F', 'F' },
        0,
        {'W', 'A', 'V', 'E'},
        {'f', 'm', 't', ' '},
        16,
        1,
        1,
        16000,
        32000,
        2,
        16,
        {'d', 'a', 't', 'a'},
        0
    };
};

#endif // SPEECHSYNTHESIS_H
