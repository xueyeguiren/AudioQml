#ifndef WAVEPAINT_H
#define WAVEPAINT_H

#include <QPainter>
#include <QDebug>
#include <QImageWriter>
class WavePaint
{
public:
    WavePaint();
    ~WavePaint();
    static int test;
    void draw16Bit(QPainter* p,float* data,int dataNum);
    QImage drawImage(float* data,int dataNum);
    QPainter* p;   //以位图为参数创建一个QPainter 对象
};

#endif // WAVEPAINT_H
