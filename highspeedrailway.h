#ifndef HIGHSPEEDRAILWAY_H
#define HIGHSPEEDRAILWAY_H

#include <QObject>
#include <QGraphicsLineItem>
#include <QPainterPath>
#include <QPen>
#include <QCursor>
#include <QtMath>
#include "trainstation.h"
#include <QGraphicsItem>
#include <QDebug>
class HighSpeedRailway : public QGraphicsPathItem
{
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event)override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event)override;
private:
    QPen pen;
    TrainStation *startStation;
    TrainStation *endStation;
public:
    HighSpeedRailway(TrainStation *startStation, TrainStation *endStation);
signals:

};

#endif // HIGHSPEEDRAILWAY_H
