#include "global.h"

int test123=123;
const char* login_params= "appid = 56ee43d0, work_dir = .";
char* stt_session_begin_params=
   "sub = iat, domain = iat, language = zh_cn, "
   "accent = mandarin, sample_rate = 16000, "
   "result_type = plain, result_encoding = utf8";
const char* tts_session_begin_params =
        "voice_name = xiaoyan, text_encoding = utf8, sample_rate = 16000, "
        "speed = 50, volume = 50, pitch = 50, rdn = 2";
QObject* Global::object;
Global::Global()
{

}

void Global:: setRootItem(QObject* object)
{
    this->object=object;
}

QObject* Global:: getRootItem()
{
    return object;
}
