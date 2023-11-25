#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H
//#pragma execution_character_set("UTF-8")
#include <QObject>
#include <QGraphicsScene>
#include "trainstation.h"
#include <iostream>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>
#include <QTableWidgetItem>
#include <QEvent>
#include <QCursor>
#include <QtMath>
#include <QMap>
#include <QLabel>
#include <QStack>
#include <QPushButton>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QTimer>
class MyGraphicsScene : public QGraphicsScene
{

public:
    explicit MyGraphicsScene(QObject *parent = nullptr);
    double calculateDistance(const QPointF& point1, const QPointF& point2);
    void draw_path(TrainStation*start,TrainStation*end);
    void get_data(QLabel *start_name,QLabel *end_name,QPushButton *set_start,QPushButton *set_end,QPushButton*);
    TrainStation* get_start_node(){
        return this->start;
    }
    TrainStation* get_end_node(){
        return this->end;
    }
    void action_path(TrainStation*start,TrainStation*end);
    QVector<QGraphicsLineItem*>* get_pre_del(){
        return &this->pre_del;
    }
protected:
    bool event(QEvent *event) override;
private:
    QVector<QGraphicsLineItem*> pre_del;
    QTransform transform;
    bool is_set_start=false;
    bool is_set_end=false;
    bool is_select=false;
    QLabel *start_name;
    QLabel *end_name;
    QPushButton *set_start;
    QPushButton *set_end;
    QStack<TrainStation*>st;
    TrainStation *start=nullptr;
    TrainStation *tmp=nullptr;
    TrainStation *end=nullptr;
    TrainStation *cur=nullptr;
    void set_data(QLabel *start_name,QLabel *end_name,QPushButton *set_start,QPushButton *set_end,QPushButton *);
    bool is_have=false;
    bool lineIntersectsCircle(QGraphicsLineItem *line, TrainStation *circle);

signals:

};

#endif // MYGRAPHICSSCENE_H
