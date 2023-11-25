#include "highspeedrailway.h"

void HighSpeedRailway::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    Q_UNUSED(event);
    setCursor(Qt::ArrowCursor);
}

void HighSpeedRailway::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPointF cp1=startStation->boundingRect().center(),cp2=endStation->boundingRect().center();
    QPen pen;
    QPainterPath path;
    path.moveTo(cp1);
    path.lineTo(cp2);
    pen.setWidth(5);
    pen.setColor(QColor(0,0,255,80));
    painter->setPen(pen);
    painter->drawPath(path);
}

void HighSpeedRailway::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    Q_UNUSED(event);
    unsetCursor();
}

HighSpeedRailway::HighSpeedRailway(TrainStation *startStation, TrainStation *endStation):startStation(startStation),endStation(endStation)
{

}
