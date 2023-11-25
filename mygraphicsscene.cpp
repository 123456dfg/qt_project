#include "mygraphicsscene.h"

MyGraphicsScene::MyGraphicsScene(QObject *parent)
    : QGraphicsScene{parent}
{
    this->setItemIndexMethod(QGraphicsScene::NoIndex);
}

double MyGraphicsScene::calculateDistance(const QPointF &point1, const QPointF &point2) {
    int deltaX = point2.x() - point1.x();
    int deltaY = point2.y() - point1.y();

    return std::sqrt(deltaX * deltaX + deltaY * deltaY);
}

bool MyGraphicsScene::event(QEvent *event){
    if(event->type() == QEvent::GraphicsSceneMousePress){
        QGraphicsSceneMouseEvent *mouseEv = static_cast<QGraphicsSceneMouseEvent*>(event);
        auto item = itemAt(mouseEv->scenePos(),transform);
        if (dynamic_cast<TrainStation *>(item) == nullptr) {
                        return true; // 忽略非GraphicsItem类型项
                    }
        if(item){//将item指向当前点 返回QGraphicsItem类型
            auto itemCast = qgraphicsitem_cast<TrainStation*>(item);//转换为GraphicsItem类型 内有bool标志变量
            if((this->start==nullptr && this->end==nullptr) ||is_have)
            {//单点情况
                if(this->cur==nullptr){
                    this->cur=itemCast;
                    this->cur->setColor(Qt::blue);
                }
                else{
                    this->cur->setColor(Qt::white);
                    this->cur=itemCast;
                    this->cur->setColor(Qt::blue);
                }
            }
            else if(this->start!=nullptr && this->end!=nullptr){
                this->cur=itemCast;
                this->cur->setColor(Qt::blue);
                this->is_have=true;

            }
            else if(this->start!=nullptr || this->end!=nullptr){
                this->cur=itemCast;
                this->cur->setColor(Qt::blue);
                this->is_have=true;
            }
            if(this->start!=nullptr)
            this->start->setColor(Qt::red);
            if(this->end!=nullptr)
            this->end->setColor(Qt::green);
}

        return true;
    }
    return QGraphicsScene::event(event);
}


void MyGraphicsScene::set_data(QLabel *start_name, QLabel *end_name, QPushButton *set_start, QPushButton *set_end,QPushButton *change_){
    this->start_name=start_name;
    this->end_name=end_name;
    this->set_start=set_start;
    this->set_end=set_end;
    connect(this->set_start,&QPushButton::clicked,this,[=](){

        if(this->cur==nullptr)QMessageBox::information(nullptr,"提醒","请选择起点");
        else{
            if(this->start!=nullptr){
                this->start->setColor(Qt::white);
                this->start->is_start=false;
            }
            this->start=this->cur;
            this->start_name->setText(this->cur->get_strname());
            this->start->is_start=true;
            this->start->setColor(Qt::red);
        }
    });
    connect(this->set_end,&QPushButton::clicked,this,[=](){
        if(this->cur==nullptr)QMessageBox::information(nullptr,"提醒","请选择终点");
        else {
            if(this->end!=nullptr){
                this->end->setColor(Qt::white);
                this->end->is_end=false;
            }
            this->end=this->cur;
            this->end_name->setText(this->cur->get_strname());
            this->end->is_end=true;
            this->end->setColor(Qt::green);
        }

    });
    connect(change_,&QPushButton::clicked,this,[=](){
        if(this->start!=nullptr && this->end!=nullptr){
        tmp=this->start;
        this->start=this->end;
        this->end=tmp;
        this->start_name->setText(this->start->get_strname());
        this->end_name->setText(this->end->get_strname());
        this->start->is_start=true;this->start->is_end=false;this->start->setColor(Qt::red);
        this->end->is_start=false;this->end->is_end=true;this->end->setColor(Qt::green);
        }
        else QMessageBox::information(nullptr,"提醒","请选择起点和终点");
    });
}

void MyGraphicsScene::draw_path(TrainStation *start, TrainStation *end){
    const int radius=start->get_radius();

    // 计算连接两个圆边的最短距离线
    qreal dx = end->x() - start->x();
    qreal dy = end->y() - start->y();
    //qreal distance = sqrt(dx * dx + dy * dy);
    qreal angle = atan2(dy, dx);
    qreal x1 = start->x() + radius * cos(angle);
    qreal y1 = start->y() + radius * sin(angle);

    qreal x2 = end->x() - radius * cos(angle);
    qreal y2 = end->y() - radius * sin(angle);
    QPen pen;
    pen.setWidth(3);
    pen.setColor(QColor(0,0,255,50));
    QGraphicsLineItem *line = new QGraphicsLineItem(x1, y1, x2, y2);
    //QPointF p1(x1,y1),p2(x2,y2);
    line->setFlag(QGraphicsItem::ItemIsSelectable, false);
    line->setPen(pen);
    this->addItem(line);
}

void MyGraphicsScene::get_data(QLabel *start_name, QLabel *end_name, QPushButton *set_start, QPushButton *set_end,QPushButton *change)
{
    return set_data(start_name,end_name,set_start,set_end,change);
}

void MyGraphicsScene::action_path(TrainStation *start, TrainStation *end){
    const int radius=start->get_radius();
    // 计算连接两个圆边的最短距离线
    qreal dx = end->x() - start->x();
    qreal dy = end->y() - start->y();
    qreal angle = atan2(dy, dx);
    qreal x1 = start->x() + radius * cos(angle);
    qreal y1 = start->y() + radius * sin(angle);
    qreal x2 = end->x() - radius * cos(angle);
    qreal y2 = end->y() - radius * sin(angle);
    QPen pen;
    pen.setWidth(3);
    pen.setColor(QColor(0,0,255,255));
    QGraphicsLineItem *line = new QGraphicsLineItem(x1, y1, x2, y2);
    this->pre_del.push_back(line);
    QPointF p1(x1,y1),p2(x2,y2);//直线的起始点和终点
    line->setFlag(QGraphicsItem::ItemIsSelectable, false);
    line->setPen(pen);
    //动画太难了
//    QLineF initialLine(p1,p2);
//    line->setLine(initialLine);
//    this->addItem(line);
//    QTimer timer;
//    int duration = 2000; // 动画持续时间
//    int steps = 100; // 分解成100个步骤
//    int timerInterval = duration / steps;
//    connect(&timer, &QTimer::timeout,this,[&]() {
//        static int step = 0;
//        qreal ratio = static_cast<qreal>(step) / steps;
//        // 计算当前位置
//        QPointF currentPoint = p1 + ratio * (p2 - p1);
//        QPointF itemPos = start->pos() + QPointF(start->boundingRect().width() / 2, start->boundingRect().height() / 2);
//        // 更新线条的位置
//        line->setLine(QLineF(itemPos, currentPoint));
//        step++;
//        if (step > steps) {
//            timer.stop();
//        }
//        update();
//    });
//    timer.start(timerInterval);
}







