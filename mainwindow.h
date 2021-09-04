#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

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

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_horizontalSlider_3_valueChanged(int value);

    void on_pushButton_clicked();

    void calcSystem();

    void plot();

private:
    Ui::MainWindow *ui;

    double x01, x02, step, dt;
    double Tau, Tau2, K;
    QVector<double> y;
    QVector<double> Time;
};

#endif // MAINWINDOW_H
