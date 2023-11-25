#include "myqgraphview.h"

MyQgraphview::MyQgraphview(QWidget  *parent)
    : QGraphicsView{parent}
{

    this->scene = new MyGraphicsScene(this);
    //QGraphicsView settings
    this->setFixedSize(1200,900);
    this->setSceneRect(0, 0, this->frameSize().width(), this->frameSize().height());
    this->setRenderHint(QPainter::Antialiasing, true);// 启用反锯齿效果
    this->setRenderHint(QPainter::SmoothPixmapTransform, true);//启用平滑的像素变换
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    // 设置初始缩放因子
    this->setTransform(QTransform().scale(0.7, 0.7));
    this->edge=init_data();
    this->setScene(this->scene);
    this->setCursor(Qt::CrossCursor);
    this->show();
}

vector<vector<int>> MyQgraphview::init_data()
{
    QString data_path=":/data/node_data.csv";
    insert_node(data_path);
    return(get_edge_matrix(this->node_size));
}

void MyQgraphview::wheelEvent(QWheelEvent *event)
{
    qreal factor = 1.2;
    if (event->angleDelta().y() < 0)
        factor = 1.0 / factor;
    scale(factor, factor);
}


void MyQgraphview::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // 记录鼠标按下的起始位置 启用鼠标移动事件
        lastMousePos = event->pos();
        isPanning = true;
        QGraphicsView::mousePressEvent(event);
    }
    else if(event->button() == Qt::LeftButton){
        QGraphicsSceneMouseEvent mouseEvent(QEvent::GraphicsSceneMousePress);
        QCoreApplication::sendEvent(this->scene,event);
    }
    return ;
}

void MyQgraphview::mouseMoveEvent(QMouseEvent *event)

{   if(isPanning)
    {
        QPointF mouseDelta = mapToScene(event->pos())-mapToScene(lastMousePos);
        //调用平移方法
        this->MyMove(mouseDelta);
        //lastMousePos是MyGraphicsView的私有成员变量，用以记录每次的事件结束时候的鼠标位置
        lastMousePos = event->pos();
    }
    QGraphicsItem *item = itemAt(event->pos());
    if (item) {
        setCursor(Qt::ArrowCursor);
    } else {
        setCursor(Qt::CrossCursor);
    }

}

void MyQgraphview::mouseReleaseEvent(QMouseEvent *event)
{
    //关闭鼠标移动事件
    if (event->button() == Qt::LeftButton)
    {
        isPanning = false;
    }
}
void MyQgraphview::MyMove(QPointF delta) {
    //如果是在缩放之后，调用的平移方法，那么平移量先要乘上缩放比，transform是view的变换矩阵，m11可以用为缩放比
    delta *= this->transform().m11();

    //修改锚点，调用缩放方法
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->centerOn(this->mapToScene(QPoint(this->viewport()->rect().width()/ 2 - delta.x(),
                                                                        this->viewport()->rect().height()/ 2 - delta.y())));
    this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);

}

void MyQgraphview::insert_node(QString &data_path)
{
    QFile inFile(data_path);
    QStringList lines;/*行数据*/
    int i=1;
        if (inFile.open(QIODevice::ReadOnly))
        {
            QTextStream stream_text(&inFile);
            while (!stream_text.atEnd())
            {
                lines.push_back(stream_text.readLine());
            }
            for (int j = 1; j < lines.size(); j++)
            {
                QString line = lines.at(j);
                QStringList split = line.split(",");/*列数据*/


                    //记录节点信息
                    QString start_node_name=QString(split.at(0));
                    QString end_node_name=QString(split.at(3));
                    QPoint start_node_point=QPoint(QString(split.at(1).mid(1)).toInt()+20,QString(split.at(2).mid(0,3)).toInt()+20);
                    QPoint end_node_point=QPoint(QString(split.at(4).mid(1)).toInt()+20,QString(split.at(5).mid(0,3)).toInt()+20);
                    bool is_connect=split.at(6)=="是"?true:false;
                    TrainStation* start_station,*end_station;
                    if(!nodes_map.count(start_node_name)){
                        start_station=new TrainStation(start_node_name,start_node_point.x(),start_node_point.y(),QColor(Qt::white));
                        nodes_map[start_node_name]=start_station;
                        mapping[start_node_name]=i++;
                        this->scene->addItem(start_station);
                    }
                    if(!nodes_map.count(end_node_name)){
                        end_station=new TrainStation(end_node_name,end_node_point.x(),end_node_point.y(),QColor(Qt::white));
                        nodes_map[end_node_name]=end_station;
                        mapping[end_node_name]=i++;
                        this->scene->addItem(end_station);
                    }
                    if(is_connect){
                        int length=static_cast<int>(sqrt((start_node_point.x()-end_node_point.x())*(start_node_point.x()-end_node_point.x())\
                                        +((start_node_point.y()-end_node_point.y())*(start_node_point.y()-end_node_point.y()))));
                        ways.push_back(way(nodes_map[start_node_name],nodes_map[end_node_name],\
                                           mapping[start_node_name],mapping[end_node_name],length));
                        this->scene->draw_path(nodes_map[start_node_name],nodes_map[end_node_name]);
                    }
            }
            this->node_size=i;
            inFile.close();
        }
        return;
}

vector<vector<int>> MyQgraphview::get_edge_matrix(const int node_size)
{
    vector<vector<int>>edges(node_size,vector<int>(node_size,10005));

    for (int i = 0; i < node_size; ++i) {
        for (int j = 0; j < node_size; ++j) {
            if(i==j)edges[i][j]=0;
        }
    }
    for(way &path:ways){

        edges[path.start_num-1][path.end_num-1]=path.length;
        edges[path.end_num-1][path.start_num-1]=path.length;
    }

    return edges;
}

void MyQgraphview::get_data(QPushButton *go){
    connect(go,&QPushButton::clicked,this->scene,[=](){
        if(this->scene->get_start_node()!=nullptr && this->scene->get_end_node()!=nullptr)
        {
            if(!this->scene->get_pre_del()->empty()){
                for (auto &i : *this->scene->get_pre_del()) {
                    QPen pen(QColor(0,0,255,50));
                    pen.setWidth(3);
                    i->setPen(pen);
                }
                this->scene->get_pre_del()->clear();
                this->update();
            }
            std::vector<int>path=dlj->dijkstra(edge,this->mapping[this->scene->get_start_node()->get_strname()],\
                    this->mapping[this->scene->get_end_node()->get_strname()],node_size);
            for (size_t i=0;i<path.size()-1;++i) {
                auto find_start=[=]()->QString{
                    for(auto it= mapping.begin();it!=mapping.end();it++)
                    {
                        if(it.value()==path[i])
                            return it.key();
                    }
                    return "";
                };
                auto find_end=[=]()->QString{
                    for(auto it= mapping.begin();it!=mapping.end();it++)
                    {
                        if(it.value()==path[i+1])
                            return it.key();
                    }
                    return "";
                };
                this->scene->action_path(nodes_map[find_start()],nodes_map[find_end()]);
            }
        }
        else QMessageBox::information(nullptr,"提醒","请选择起点和终点");
    });
}
