#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1680,1050);
    ui->graphicsView->scene->get_data(ui->start_point,ui->end_point,ui->set_startpoint,ui->set_endpoint,ui->change);
    ui->graphicsView->get_data(ui->way_go);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action1_triggered()
{
    qApp->exit();
}

