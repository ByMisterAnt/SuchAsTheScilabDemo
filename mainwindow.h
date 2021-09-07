#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QSlider>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

    void plotter();

    void calcSystem();

    void plot();

    void showValues();

private:

    Ui::MainWindow *ui;

    QList<QSlider *> allSliders;

    double x01, x02, step, dt;
    double Tau, Tau2, tzeta, K;
    QVector<double> y;
    QVector<double> Time;
};

#endif // MAINWINDOW_H
