#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget->yAxis->setRange(0, 2);
    ui->widget->xAxis->setRange(0, 15);

    x01 = 0;
    x02 = 0;
    dt = 0.1;
    Tau = 1;
    Tau2 = 1;
    K = 1;

    calcSystem();

    plot();

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_horizontalSlider_valueChanged(int value)
{
        x01 = 0;
        x02 = 0;
        K = double(value)/25;

        calcSystem();

        ui->widget->clearGraphs();
        plot();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    x01 = 0;
    x02 = 0;
    Tau = double(value)/25;

    calcSystem();

    ui->widget->clearGraphs();
    plot();
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{

    x01 = 0;
    x02 = 0;
    Tau2 = double(value)/500;

    calcSystem();

    ui->widget->clearGraphs();
    plot();
}

void MainWindow::on_pushButton_clicked()
{
    x01 = 0;
    x02 = 0;
    K = 1;
    Tau = 0.32;
    Tau2 = 0.05;

    calcSystem();

    ui->widget->clearGraphs();
    plot();
}

void MainWindow::calcSystem()
{
    Time.clear();
    y.clear();

    for(int i = 0; i <= int(15/dt); i++)
    {
        //send step signal
        if(i >= 2){
            step = 1;
        } else{
            step = 0;
        }

    //calculate equations
    x01 = x01 + dt * (x02);
    x02 = x02 + dt * (-x01/Tau2 - Tau*x02/Tau2 + K*step/Tau2);

    y.push_back(x01);
    Time.push_back(i*dt);

    }
}

void MainWindow::plot()
{
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(Time,y);
    ui->widget->replot();
}

