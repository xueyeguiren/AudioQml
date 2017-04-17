#ifndef PROCESSMYSQL_H
#define PROCESSMYSQL_H

#include "qobject.h"
#include "qpluginloader.h"
#include "qsqldatabase.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "QtSql"
#include "qdebug.h"
#include "javabeen.h"
#include "srinterface.h"

class ProcessMysql : public QObject
{
    Q_OBJECT
public:
    Goods_general ggo;
    Goods_machining gmo;
    Goods_general* gg=&ggo;
    Goods_machining* gm=&gmo;
    explicit ProcessMysql(QObject *parent = 0);

    QSqlDatabase  connect_date();
    /**
     * @brief querySpeechResult
     * 根据传入的字符串在表中对value字段进行一一对比，只要发现有一个符合条件就返回
     * 该value对应的goodsId
     * @param ST
     * @return goodsId  -1表示未查询到　大于０表示查询到
     */
    int querySpeechResult(QString ST);//ST--SpeechText

    int  querySpeechNum(QString ST);

    /**
     * @brief queryGoods_general
     * 根据goods_id查询goods_general对象
     * @param goods_id
     * @return
     */
    Goods_general* queryGoods_general(int goods_id);
    /**
     * @brief queryGoods_machining
     * 根据goods_id查询goods_machining对象
     * @param goods_id
     * @return
     */
    Goods_machining* queryGoods_machining(int goods_id);

signals:

public slots:
};

#endif // PROCESSMYSQL_H
