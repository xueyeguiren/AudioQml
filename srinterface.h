#ifndef SRINTERFACE_H
#define SRINTERFACE_H

#include <global.h>
#include <processmysql.h>
#include <javabeen.h>
#include <audioplayer.h>
#include <speechsynthesis.h>

class SRInterface
{
public:
    SRInterface();
    struct Global:: QueryResult handleSpeech(char* result);
    int queryGoods(struct Global::QueryResult* qr, QString string);
    int queryServer(struct Global::QueryResult* qr, QString string);
//    void startSpeech(char* resul);
    void SpeechStart(char* result);
//    static void* newThreadFun(void* arg);
};

#endif // SRINTERFACE_H
