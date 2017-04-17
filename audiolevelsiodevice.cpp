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
#include <QDebug>
#include <speechrecognizer.h>
#include <audiolevels.h>

//! [1]
static const int resolution =50;//分辨率滚动快慢
AudioLevels audioLevels;
SpeechRecognizer sr;
//! [1]

AudioLevelsIODevice::AudioLevelsIODevice( QObject *parent)
    :  QIODevice(parent)
{
    qDebug()<<"gouzao";

}

AudioLevelsIODevice::~AudioLevelsIODevice()
{
    qDebug()<<"xigou";
}

 struct Global:: speech_rec* AudioLevelsIODevice:: rec=new struct Global:: speech_rec;
// Implementation required for this pure virtual function
qint64 AudioLevelsIODevice::readData(char *data, qint64 maxSize)
{
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
    return -1;
}

//! [2]
qint64 AudioLevelsIODevice::writeData(const char *data, qint64 maxSize)
{
//    qDebug()<<"maxsize"<<maxSize;
    // The amount of new data available.
//    qDebug()<<"writeData";
    long sum=0;
    long result=0;
    float value;
    int newDataSize = maxSize / resolution;
    int i;
    short audioData;
    // If we get more data than array size, we need to adjust the start index for new data.
    // Move the old data ahead in the rows (only do first half of rows + middle one now).
    for(i=0;i<newDataSize;i++){
        audioData=(((data[i*resolution+1])<<8)|(data[i*resolution]&0xFF));
//        QTime current_time = QTime::currentTime();
//        int msec = current_time.msec();
//        qDebug()<<i<<audioData[i];
          sum+=audioData*audioData;
    }
   if(newDataSize==0)
       newDataSize=1;
   result=qSqrt(sum/newDataSize);
   if(result>32767)
       result=0;
//      qDebug()<<"k"<<"------------"<<result;
       value = float(result)/109.1f;
       if(value<0)
           value=(value-0.1f);
       else
           value=(value+1.1f);
    rec->value=value;
    rec->start=true;
    startSpeech((char*)data,maxSize);
    return maxSize;
}
//! [2]

struct Global:: speech_rec* AudioLevelsIODevice:: getAudioData()
{
//    qDebug()<<"dayin test";
//    audioData=NULL;
    return rec;

}
int AudioLevelsIODevice::startSpeech(char*data,qint64 maxSize)
{  SpeechRecognizer sr;
    const char* result=sr.result;
    if(!result==NULL)
    {
        AudioLevels as;
        as.stopRecord();
        qDebug()<<"tt000000000000";
        return NULL;
    }

//    qDebug()<<"startSpeech";
    struct Global::speech_rec* rec=&audioLevels.rec;
    rec->data=data;
    rec->length=maxSize;
    sr.startSpeechRecognizer(rec);
    rec->audio_status = MSP_AUDIO_SAMPLE_CONTINUE;
}

