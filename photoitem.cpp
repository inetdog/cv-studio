#include "photoitem.h"
 
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QGraphicsSceneDragDropEvent>
#include <QDrag>
#include <math.h>
 
//构造函数初始化了变量pix
PhotoItem::PhotoItem(QPixmap *pixmap)
{
    pix = *pixmap;
    setAcceptDrops(true);   //设置可拖拽
    m_scaleValue = 0;
 
    m_isMove = false;
}
 
//实现自己的图元边界函数
QRectF PhotoItem::boundingRect() const
{
    return QRectF(-pix.width() / 2, -pix.height() / 2,
                  pix.width(), pix.height());
}
 
//只需QPainter的drawPixmap()函数将图元图片绘出即可
void PhotoItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                    QWidget *)
{
    painter->drawPixmap(-pix.width() / 2, -pix.height() / 2, pix);
}
 
//鼠标点击事件  局部缩放
void PhotoItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_startPos = event->pos();
    m_isMove = true;
 
    int scaleValue = m_scaleValue;
    if(m_zoomState == ZOOM_IN)       //局部放大
    {
        scaleValue++;
    }
    else if(m_zoomState == ZOOM_OUT)        //局部缩小
    {
        scaleValue--;
    }
 
    if (scaleValue > ZOOM_IN_TIMES || scaleValue < ZOOM_OUT_TIMES)
        return;
 
    if (m_scaleValue != scaleValue)
    {
        setTransformOriginPoint(event->pos().x(), event->pos().y());
    }
    m_scaleValue = scaleValue;
    qreal s;
    //实现局部缩放
    if(m_scaleValue > 0)
    {
        s = pow(1.1, m_scaleValue);        //放大 计算x的y方次 参数都是double类型
    }else
    {
        s = pow(1 / 1.1, -m_scaleValue);      //缩小
    }
    setScale(s);
}
 
void PhotoItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_isMove)
    {
        QPointF point = event->pos() - m_startPos;
        moveBy(point.x(), point.y());
    }
}
 
void PhotoItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    m_isMove = false;
}
 
//使用滚轮整体缩放
void PhotoItem::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    setZoomState(NO_STATE);
 
    int scaleValue = m_scaleValue;
    if(event->delta() > 0)  //delta（）为正，滚轮向上滚
    {
        scaleValue++;
    }
    else
    {
        scaleValue--;
    }
 
    if (scaleValue > ZOOM_IN_TIMES || scaleValue < ZOOM_OUT_TIMES)
        return;
 
    m_scaleValue = scaleValue;
    qreal s;
    if(m_scaleValue > 0)
    {
        s = pow(1.1, m_scaleValue);        //放大 计算x的y方次 参数都是double类型
    }
    else
    {
        s = pow(1 / 1.1, -m_scaleValue);      //缩小
    }
    setScale(s);
    setTransformOriginPoint(event->pos().x(), event->pos().y());
}
 
//从widget获取的缩放值，用于同步滚轮和按键
void PhotoItem::setScaleValue(const int &scaleValue)
{
    if (scaleValue > ZOOM_IN_TIMES || scaleValue < ZOOM_OUT_TIMES)
        return;
 
    m_scaleValue = scaleValue;
 
    qreal s;
    if(m_scaleValue > 0)
    {
        s = pow(1.1, m_scaleValue);        //放大 计算x的y方次 参数都是double类型
    }
    else
    {
        s = pow(1 / 1.1, -m_scaleValue);      //缩小
    }
 
    setScale(s);
}
 
void PhotoItem::setZoomState(const int &zoomState)
{
    m_zoomState = zoomState;
    if (m_zoomState == RESET)
    {
        m_scaleValue = 0;
        setScale(1);
        setTransformOriginPoint(0, 0);
    }
}
 
int PhotoItem::getScaleValue() const
{
    return m_scaleValue;
}
