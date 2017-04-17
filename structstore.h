#ifndef STRUCTSTORE_H
#define STRUCTSTORE_H
#include "audiolevelsiodevice.h"
#include "QAudioInput"
struct audioInput_struct{
    AudioLevelsIODevice *m_device;
    QAudioInput *m_audioInput;
};


#endif // STRUCTSTORE_H
