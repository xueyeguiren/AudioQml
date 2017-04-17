#include "processmysql.h"

ProcessMysql::ProcessMysql(QObject *parent) : QObject(parent)
{

}
QSqlDatabase ProcessMysql:: connect_date()
{
       //加载驱动
       QPluginLoader loader;
       // MySQL 驱动插件的路径
       //raspberry
//       loader.setFileName("/usr/local/qt5pi/plugins/sqldrivers/libqsqlmysql.so");
       //pc
       loader.setFileName("/usr/local/Qt-5.7.1/plugins/sqldrivers/libqsqlmysql.so");
       //qDebug() << "loader.load()..............."<<loader.load();
       QSqlDatabase db;
       if(QSqlDatabase::contains("qt_sql_default_connection"))
         db = QSqlDatabase::database("qt_sql_default_connection");
       else
        db = QSqlDatabase::addDatabase("QMYSQL");
       db.setDatabaseName("vm");
       db.setHostName("localhost");
       db.setPort(3306);
       db.setUserName("root");
       db.setPassword("3318");
       if(!db.open()){
           printf( "无法建立数据库连接\n");
       }
       else{
           printf("建立数据库连接sucess\n");
       }
       return db;
}
int ProcessMysql:: querySpeechResult(QString ST)
{
    QSqlDatabase db=connect_date();
    QSqlQuery query;
    int returnText;
    bool ok;
    if(query.exec("select * from goods_sr"))
              {
                  int numRows =  0;
                  if(db.driver()->hasFeature(QSqlDriver::QuerySize))
                  {
                      numRows = query.size();
                      printf("numRows-->%d\n",numRows);
                  }else
                  {
                      query.last();
                      printf("numRows-->%d\n",query.at() + 1);
                  }
                  QString id,key,goodsId;
                  int t = 0;
                  while(query.next())
                  {
                      id = query.value(t).toString();
                      key = query.value(t+1).toString();
                      goodsId = query.value(t+2).toString();
                      //分别打印三个属性
                      qDebug()<<"numRows:"<<id;
                      qDebug() << QString("Id: %1, key: %2, goodsId: %3")
                                          .arg(id)
                                          .arg(key)
                                          .arg(goodsId);
                      int resultCode=ST.indexOf(key);
                      if(resultCode>=0){
                          qDebug()<<"find the match key!";
                          returnText=goodsId.toInt(&ok,10);
                          break;
                      }
                      returnText=-1;
                  }
              }
    query.finish();
    db.close();
    return returnText;

}

int ProcessMysql::querySpeechNum(QString ST)
{
    QSqlDatabase db=connect_date();
    QSqlQuery query;
    int returnText;
    if(query.exec("select * from sr_num"))
              {
                  int numRows =  0;
                  if(db.driver()->hasFeature(QSqlDriver::QuerySize))
                  {
                      numRows = query.size();
                      printf("numRows-->%d\n",numRows);
                  }else
                  {
                      query.last();
                      printf("numRows-->%d\n",query.at() + 1);
                  }
                  int id,num;
                  QString cn_num;
                  int t = 0;
                  bool ok;
                  while(query.next())
                  {
                      id = query.value(t).toInt(&ok);
                      cn_num=query.value(t+1).toString();
                      num=query.value(t+2).toInt(&ok);
                      int resultCode=ST.indexOf(cn_num);
                      if(resultCode>=0){
                          qDebug()<<"find the 对应的数字了!";
                          returnText=num;
                          break;
                      }
                      returnText=0;
                  }
              }
    query.finish();
    db.close();
    return returnText;

}

Goods_general* ProcessMysql:: queryGoods_general(int goods_id)
{
    QSqlDatabase db=connect_date();
    QSqlQuery query;
    if(query.exec("select * from goods_general where id="+QString::number(goods_id,10)));
              {
                  int numRows =  0;
                  if(db.driver()->hasFeature(QSqlDriver::QuerySize))
                  {
                      numRows = query.size();
                      printf("numRows-->%d\n",numRows);
                  }else
                  {
                      query.last();
                      printf("numRows-->%d\n",query.at() + 1);
                  }
                  QString name,picUrl;
                  float price;
                  int id;
                  bool ok;
                  while(query.next())
                  {
                      id=query.value(0).toInt(&ok);
                      qDebug()<<"id"<<id;
                      name = query.value(1).toString();
                      qDebug()<<"name"<<name;
                      price = query.value(2).toFloat(&ok);
                      qDebug()<<"price"<<price;
                      picUrl =query.value(3).toString();
                      qDebug()<<"picUrl"<<picUrl;
                      gg->setId(id);
                      gg->setName(name);
                      gg->setPrice(price);
                      gg->setPicUrl(picUrl);
                  }
              }
    query.finish();
    db.close();
    return  gg;
}

Goods_machining* ProcessMysql::queryGoods_machining(int goods_id)
{
    QSqlDatabase db=connect_date();
    QSqlQuery query;
    if(query.exec("select * from goods_machining where id="+QString::number(goods_id,10)));
              {
                  int numRows =  0;
                  if(db.driver()->hasFeature(QSqlDriver::QuerySize))
                  {
                      numRows = query.size();
                      printf("numRows-->%d\n",numRows);
                  }else
                  {
                      query.last();
                      printf("numRows-->%d\n",query.at() + 1);
                  }
                  int id,road,store,goods_id;
                  bool ok;
                  while(query.next())
                  {
                      id = query.value(0).toInt(&ok);
                      qDebug()<<"id"<<id;
                      road = query.value(1).toInt(&ok);
                      qDebug()<<"road"<<road;
                      store =query.value(2).toInt(&ok);
                      qDebug()<<"store"<<store;
                      goods_id =query.value(3).toInt(&ok);
                      qDebug()<<"goods_id"<<goods_id;
                      gm->setId(id);
                      gm->setRoad(road);
                      gm->setStore(store);
                      gm->setGoods_id(goods_id);
                  }
              }
    query.finish();
    db.close();
    return  gm;
}
