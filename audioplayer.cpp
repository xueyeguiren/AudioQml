#include "audioplayer.h"

AudioPlayer::AudioPlayer(QObject *parent) : QObject(parent)
{

}
int AudioPlayer::startPlayer(QString fileName)
{
    //读取文件各有用信息
    qDebug()<<"startPlayer"<<fileName;
    inputFile=new QFile;
    inputFile->setFileName(fileName);
    bool ret=inputFile->open(QIODevice::ReadOnly);
    qDebug()<<(inputFile);
    if(!ret)
    {
        return -1;
    }
    QAudioFormat format;
    format.setSampleRate(16000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);
    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {

      qDebug()<<"raw audio format not supported by backend, cannot play audio.";
      return -2;
     }
    audio = new QAudioOutput(format,0);
    audio->start(inputFile);
    connect(audio, SIGNAL(stateChanged(QAudio::State)),this, SLOT(finishedPlaying(QAudio::State)));
    return 0;
}
void AudioPlayer::finishedPlaying(QAudio::State state)
 {
   if(state == QAudio::IdleState) {
     audio->stop();
     inputFile->close();
     delete audio;
     delete inputFile;
     qDebug() << "play end!";
   }

 }
