#ifndef MYQGRAPHVIEW_H
#define MYQGRAPHVIEW_H

#include <QObject>
#include <fstream>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsScale>
#include <QMouseEvent>
#include "mygraphicsscene.h"
#include <QFile>
#include<QtMath>
#include <QGraphicsSceneMouseEvent>
#include <QCoreApplication>
#include <QColor>
#include "algorithm.h"
#include <vector>
class MyQgraphview : public QGraphicsView
{
    Q_OBJECT
public:
    using way=struct way_struct{
        TrainStation *start;
        TrainStation *end;
        int start_num;
        int end_num;
        int length;
        way_struct(TrainStation *s,TrainStation *e,int start,int end,int len):start(s),end(e),start_num(start),end_num(end),length(len){}

    };
    MyQgraphview(QWidget *parent = nullptr);
    MyGraphicsScene *scene;
    QVector<way> ways;
    void get_data(QPushButton *go);

signals:

protected:
    virtual void wheelEvent(QWheelEvent *event) override;
    //virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    void MyMove(QPointF delta);
    void insert_node(QString &data_path);
    vector<vector<int>> init_data();
    vector<vector<int>> get_edge_matrix(const int node_size);

private:
    //TrainStation *trainstation;
    algorithm *dlj;
    QGraphicsPixmapItem *pixmapitem;
    QPoint lastMousePos,lastPos;
    bool isPanning=false;
    QMap<QString,TrainStation*>nodes_map;//坐标与坐标名对应关系
    QMap<QString,int> mapping;//映射关系
    int node_size;
    vector<vector<int>>edge;
};

#endif // MYQGRAPHVIEW_H
