#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtWidgets/QLabel>
#include <QTimer>
#include <ctime>
//............................................................
QT_CHARTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
//............................................................
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void chartDraw();
    void timer_func();
    void hour();
//    int minute();
//    int second();


private slots:
    void on_Button_chart_clicked();

    void on_Button_camera_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *plot_timer;
    QChart *chart ;
    QChartView *chartView ;
    QLineSeries *series ;


    int seed ;
    int x ;
    int y ;
//for time
    int hh=0;//start
    int mm=0;//start
    int ss=0;//start
    int h=0;//curr
    int m=0;//curr
    int s=0;//curr
    int hr;//now
    int min;//now
    int sec;//now
};
#endif // MAINWINDOW_H
