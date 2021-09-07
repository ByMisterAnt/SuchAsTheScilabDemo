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
    dt = 0.05;
    Tau = 1;
    Tau2 = 1;
    K = 1;

    calcSystem();

    plot();

    allSliders = findChildren<QSlider *>();

            for(int i = 0; i < allSliders.size(); i++)
            {
                QObject::connect(allSliders.at(i), SIGNAL(valueChanged(int)), this,SLOT(plotter()));
            }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plotter()
{
    int value = qobject_cast<QSlider *>(sender())->value();

    QString slidersName = qobject_cast<QSlider *>(sender())->objectName();
    if(slidersName == QString("horizontalSlider")){
        K = double(value)/25;
    }
    if(slidersName == QString("horizontalSlider_2")){
        Tau = double(value)/25;
    }
    if(slidersName == QString("horizontalSlider_3")){
        Tau2 = double(value)/500;
    }
    if(slidersName == QString("horizontalSlider_4")){
        tzeta = double(value)/500;
    }

    showValues();

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

    x01 = 0;
    x02 = 0;

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
    x02 = x02 + dt * (-x01/(2*Tau2*tzeta) - Tau*x02/(2*Tau2*tzeta) + K*step/(2*Tau2*tzeta));

    y.push_back(x01);
    Time.push_back(i*dt);

    }
}

void MainWindow::plot()
{
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(Time,y);
    ui->widget->replot();

    Time.clear();
    y.clear();
}

void MainWindow::showValues()
{
    ui->k->setText("K = "+ QString::number(K));
    ui->tau->setText("Tau = "+ QString::number(Tau));
    ui->tau2->setText("Tau2 = "+ QString::number(Tau2));
    ui->tzetta->setText("ξ = "+ QString::number(tzeta));
}
