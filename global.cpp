#include "global.h"

int test123=123;
const char* login_params= "appid = 56ee43d0, work_dir = .";
char* session_begin_params=
   "sub = iat, domain = iat, language = zh_cn, "
   "accent = mandarin, sample_rate = 16000, "
   "result_type = plain, result_encoding = utf8";
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
