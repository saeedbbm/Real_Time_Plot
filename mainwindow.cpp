#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QString>

#include <QLogValueAxis>
#include <QLineSeries>
#include <QValueAxis>
#include <QChart>
#include <QChartView>

#include <math.h>
using namespace std;
//...........................................................................

//static int randomBetween(int low, int high, int seed)
//{
//    qsrand(seed); // Set the base number for counting a random host in qrand
//    return (qrand() % ((high + 1) - low) + low);
//}


//............................................................................

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(tr("Water Leak"));
    resize(800, 600);


    chart = new QChart();
    chartView = new QChartView(chart);
    series = new QLineSeries();

//    seed = 0;
    x = 0;
    y = 0;

    plot_timer = new QTimer(this);
    connect(plot_timer, SIGNAL (timeout()), this,  SLOT(chartDraw()));
    connect(plot_timer, SIGNAL (timeout()), this,  SLOT(hour()));


//    series->append(0, 0);




}

MainWindow::~MainWindow()
{
    delete ui;
}

//............................................camera..........................................


void MainWindow::on_Button_camera_clicked()
{
    for(int i=0;i<=100;i++)
        ui->listWidget->addItem(QString::number(i));
}

//.............................................chart..........................................
void MainWindow::on_Button_chart_clicked()
{
    timer_func();

}

//....................................

void MainWindow::timer_func()
{
    if (!(plot_timer->isActive()))
    {
        ui->Button_chart->setText("Plot_Stop");


        time_t start_time = time(0);
        tm *ST = localtime(&start_time);
        cout << "start: "<< ST->tm_hour << ":";
        cout << ST->tm_min << ":";
        cout << ST->tm_sec << endl;
        hh= ST->tm_hour;
        mm= ST->tm_min;
        ss= ST->tm_sec;

        this->chartDraw();
        cout << "update" <<endl;
        plot_timer->start(1000);

    }
    else if(plot_timer->isActive())
    {
//        ui->chart_button->setEnabled(false);

        plot_timer->stop();
        ui->Button_chart->setText("Plot_Start");
    }

}

void MainWindow::hour()
{
    int minn=0;
    int hrr = 0;
    time_t curr_time = time(0);
    tm *curt = localtime(&curr_time);
    h= curt->tm_hour;
    m= curt->tm_min;
    s= curt->tm_sec;
    cout << "current: "<< curt->tm_hour << ":";
    cout << curt->tm_min << ":";
    cout << curt->tm_sec << endl;



    hr = h-hh ;
    if (hr > hrr)
        mm=mm-mm;

    min = m-mm ;
    if (min > minn)
        ss=ss-ss;

    sec =s-ss ;
    minn= min;
    hrr=hr;

//    QString *time =new QString;
//    time = QString (hr)+ ":" + QString(min) + ":" + QString(sec);


}

//.............................................
void MainWindow::chartDraw()
{

    cout << "Time: "<< hr << ":";
    cout << min << ":";
    cout << sec << endl;




    this->x = rand() % 25 + 1;
    this->y = rand() % 25 + 1;
//    series->append(x, y);



    // Create a random sinusoid
//    seed = randomBetween(0, 100, seed);
    QLineSeries *series = new QLineSeries();
    int k = 0;
    while (k <= 100)
    {
        *series << QPointF(abs(sec), k);
        ++k;
    }

    // Create a graph and add a sinusoid to it
    chart->addSeries(series);

    // Add a tooltip for the chart
//            chart->setToolTip(QString("Graph №%1\n"
//                                      "Number of counts %2").arg(i + 1).arg(k));

    // Adjusting the Axes of the Graph
    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("x, м");
    axisX->setLabelFormat("%i");
    axisX->setTickCount(1);

    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);



    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("t, мс");
    axisY->setLabelFormat("%g");
    axisY->setTickCount(5);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);



//    chart->addSeries(series);

    chart->legend()->hide();
//    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Data from the microphone");

    chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout_chart->addWidget(chartView);

    ui->label_loc_num->setText(QString::number(this->x));
    ui->label_vol_num->setText(QString::number(this->x));
    ui->label_acc_num->setText(QString::number(this->x));
}

//...................................................







