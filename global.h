#ifndef GLOBAL_H
#define GLOBAL_H
#include <QObject>
extern int test123;
extern  const char* login_params ;
extern  char* stt_session_begin_params;
extern const char* tts_session_begin_params;
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

    /* wav音频头部格式 */
    typedef struct _wave_pcm_hdr
    {
        char            riff[4];                // = "RIFF"
        int		size_8;                 // = FileSize - 8
        char            wave[4];                // = "WAVE"
        char            fmt[4];                 // = "fmt "
        int		fmt_size;		// = 下一个结构体的大小 : 16

        short int       format_tag;             // = PCM : 1
        short int       channels;               // = 通道数 : 1
        int		samples_per_sec;        // = 采样率 : 8000 | 6000 | 11025 | 16000
        int		avg_bytes_per_sec;      // = 每秒字节数 : samples_per_sec * bits_per_sample / 8
        short int       block_align;            // = 每采样点字节数 : wBitsPerSample / 8
        short int       bits_per_sample;        // = 量化比特数: 8 | 16

        char            data[4];                // = "data";
        int		data_size;              // = 纯数据长度 : FileSize - 44
    } wave_pcm_hdr;

};

#endif // GLOBAL_H
