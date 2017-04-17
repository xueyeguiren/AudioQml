#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>
#include <QAudio>
#include <QAudioOutput>
#include <QDebug>
#include <QFile>
class AudioPlayer : public QObject
{
    Q_OBJECT
public:
    explicit AudioPlayer(QObject *parent = 0);
    //语音播放
    int startPlayer(QString fileName);
    QAudioOutput *audio;//output
    QFile* inputFile;
public slots:
    //结束播放
    void finishedPlaying(QAudio::State state);
signals:

public slots:
};

#endif // AUDIOPLAYER_H
