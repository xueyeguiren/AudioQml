#include "wavepaint.h"

WavePaint::WavePaint()
{
p=new QPainter;
}
WavePaint::~WavePaint()
{
    delete p;
}

int WavePaint::test=0;
void WavePaint:: draw16Bit(QPainter *p,float* data,int dataNum)
{
//    test+=1;
//    qDebug()<<dataNum;
    for(int i=0;i<dataNum;i++)
    {
        p->drawLine(1080/dataNum*i,307-data[i],1080/dataNum*i,307+data[i]);
//        qDebug()<<"draw16Bit-for"<<"data"<<data[i];
    }

}

QImage WavePaint::drawImage(float* data,int dataNum)
{
//    qDebug()<<"test startpaint"<<"dataNum"<<dataNum<<"data"<<data[1];
    int W = 1080; //1080;
    int H = 615;//615;
    QImage image(W,H,QImage::Format_RGB32);//定义图片，并在图片上绘图方便显示
    image.fill(Qt::white);//填充位图背景色

    p->begin(&image);
    //p.translate(-ur.x(),-ur.y()); //平移坐标系
    //p.drawRect(100,100,200,100);

    QPen pen;
    pen.setColor(QColor(00, 35, 00));   //背景网格画笔
    p->setPen(pen);      //设置画笔

    //画背景网格图
    int i;
    double x, y;
    int col_num = 40;   //背景网格列数
    int row_num = 2;   //背景网格行数

//    for (i = 0; i <= col_num; i++)  //画竖线
//    {
//        x = i * W / col_num;
//        p->drawLine((int)x, H/3, (int)x, H/3*2);
//    }

    for (i = 0; i <= row_num; i++)   //画横线
    {
        y = H/3+H/3*i;
        p->drawLine(0, (int)y, W, (int)y);
    }

    pen.setColor(QColor(0x33,0x33,0x33));   //波形图画笔
    pen.setWidth(2);
    p->setPen(pen);      //设置画笔
    if(dataNum>0)
    draw16Bit(p,data,dataNum);
    p->end();

//    QPainter* painter=new QPainter;     //获取当前画布
//    painter->begin(&image);
//    painter->drawPixmap(0,0,pix);    //将位图画到画布上，单缓冲技术
//    painter->end();
//    QImageWriter  imagefile;
//    imagefile.setFileName("/home/mjl/test.png");
//    imagefile.setFormat("png");
//    imagefile.setQuality(100);
//    qDebug()<< imagefile.write(image)<<imagefile.errorString();
//    qDebug()<<"tt";
//    qDebug()<<"qimage"<<image;
    return image;

}
