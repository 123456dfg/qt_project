#include "trainstation.h"

TrainStation::TrainStation(const QString &name, qreal x, qreal y,const QColor &color) : name(name),color(color)
{
    setPos(x, y);
    setFlags(QGraphicsItem::ItemIsSelectable);
    this->setCursor(Qt::ArrowCursor);
    this->shape();
}

QRectF TrainStation::boundingRect() const
{

    return QRectF(-radius,-radius,radius*2,radius*2);
}

QRectF TrainStation::textboundingRect(){
    QRectF rect = boundingRect();
    rect.setRect(rect.x()+6,rect.y()+6,rect.width()+40,rect.height()+5);
    return rect;
}

void TrainStation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QFont font("宋体", 7, QFont::Bold);
    QPen pen(QColor(0,0,255,255));
    painter->setPen(pen);
    painter->setFont(font);
    this->prepareGeometryChange();
    painter->drawText(this->textboundingRect(), Qt::AlignCenter, name);
    painter->setBrush(this->color); // 设置画刷颜色为红色
    pen.setColor(QColor(0,0,0,255));
    painter->setPen(pen);
    this->prepareGeometryChange();
    painter->drawEllipse(this->boundingRect());

}

bool TrainStation::contains(const QPointF &point) const{
    QRectF rect = boundingRect();
    return point.x() > rect.left() && point.y() > rect.top() && point.x() < rect.right() && point.y() < rect.bottom();
}

void TrainStation::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    Q_UNUSED(event);
    setCursor(Qt::ArrowCursor);
}

void TrainStation::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    Q_UNUSED(event);
    unsetCursor();
}

void TrainStation::setColor(const QColor &newColor){
    this->color = newColor;
    this->update();
}

QString TrainStation::get_strname(){
    return this->name;
}
