#ifndef TRAINSTATION_H
#define TRAINSTATION_H
#include <QObject>
#include <QGraphicsItem>
#include <QString>
#include <QPainter>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <QFont>
#include <QCursor>
#include <QMouseEvent>
class TrainStation : public QGraphicsItem
{
public:
    TrainStation(const QString& name, qreal x, qreal y,const QColor &color);

    QRectF boundingRect() const override;
    QRectF textboundingRect();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    void setColor(const QColor &newColor);
    QString get_strname();
    bool is_start=false;
    bool is_end=false;
    int get_radius(){
        return this->radius;
    }
protected:
    bool contains(const QPointF &point)const override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
private:
    QString name;
    QColor color;
    qreal circleRadius = 10;
    const int radius=7;


};

#endif // TRAINSTATION_H
