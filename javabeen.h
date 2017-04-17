#ifndef JAVABEEN_H
#define JAVABEEN_H

//object goods
class Goods_general
{
public:
    int id;//id
    QString name;//商品名称
    float price;//商品价格
    QString picUrl;//商品图片
public:
    Goods_general(){}
    int getId()
    {
        return this->id;
    }
    void setId(int id)
    {
        this->id=id;
    }
    QString getName()
    {
        return this->name;
    }
    void setName(QString name)
    {
        this->name=name;
    }
    float getPrice()
    {
        return this->price;
    }
    void setPrice(float price)
    {
        this->price=price;
    }
    QString getPicUrl()
    {
        return this->picUrl;
    }
    void setPicUrl(QString picUrl)
    {
        this->picUrl=picUrl;
    }
};
    //goods_general over
/**************************************************************************************/
    //goods_machining object
    class Goods_machining
    {
    private:
        int id;//id
        int road;//货道
        int store;//库存
        int goods_id;//商品id
    public:
        Goods_machining(){}
        int getId()
        {
            return this->id;
        }
        void setId(int id)
        {
            this->id=id;
        }
        int getRoad()
        {
            return this->road;
        }
        void setRoad(int road)
        {
            this->road=road;
        }
        int getStore()
        {
            return this->store;
        }
        void setStore(int store)
        {
            this->store=store;
        }
        int getGoods_id()
        {
            return this->goods_id;
        }
        void setGoods_id(int goods_id)
        {
            this->goods_id=goods_id;
        }
    };


#endif // JAVABEEN_H
