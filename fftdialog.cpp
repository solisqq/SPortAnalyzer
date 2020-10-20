#include "fftdialog.h"
#include "ui_fftdialog.h"
#include <QDebug>
//#define __USE_SQUARE_BRACKETS_FOR_ELEMENT_ACCESS_OPERATOR

FFTDialog::FFTDialog(double freq, int samplesCount, QWidget *parent) :
    QDialog(parent),
    frequency(freq),
    count(samplesCount),
    ui(new Ui::FFTDialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    period = 1/freq;
    length = (static_cast<double>(samplesCount)*period)*1000;

    m_chart = new QtCharts::QChart;
    QtCharts::QChartView* chartView = new QChartView(m_chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(800,600);
    m_series = new QLineSeries();
    m_series->setUseOpenGL(true);
    m_chart->addSeries(m_series);
    axisX = new QValueAxis;
    axisX->setRange(0,4);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Time");
    axisX->setTickCount(25);
    axisY = new QValueAxis;
    axisY->setRange(-1000,1000);
    axisY->setTitleText("Value");
    m_chart->setAxisX(axisX,m_series);
    m_chart->setAxisY(axisY,m_series);
    //m_chart->addAxis(axisX, Qt::AlignBottom);
    //m_chart->addAxis(axisY, Qt::AlignLeft);
    m_chart->legend()->hide();
    m_chart->setTitle("Data");
    ui->chartLayout->addWidget(chartView);

    fft = new ffft::FFTReal<double>(samplesCount);

    //qDebug()<<frequency<<period<<length<<count;
}



FFTDialog::~FFTDialog()
{
    delete ui;
}

void FFTDialog::showFFT(double *data)
{
    double* Y = new double[count];
    fft->do_fft(Y, data);
    for(int i=0; i<count; i++) {
        qDebug()<<Y[i];
    }
    QVector<double> P2, P1;
    P2.reserve(count);
    P1.reserve(static_cast<int>(length)/2+1);

    for(int i=0; i<count; i++) {
        P2.append(qAbs(Y[i]/length));
        if(i>static_cast<int>(length/2)) {
            P1.append(2*P2[i]);
        }
    }

    QVector<double> freqDomain;
    freqDomain.reserve(static_cast<int>(length/2));
    for(int i=0; i<length/2; i++) {
        freqDomain.append((frequency*i)/length);
    }

    QVector<QPointF> points;
    points.reserve(static_cast<int>(length/2));
    double max=0.05;
    for(int i=0; i</*static_cast<int>(length/2)*/P1.count(); i++) {
        points.append(QPointF(freqDomain[i], P1[i]));
        if(P1[i]>max && P1[i]<50) max=static_cast<int>(P1[i]);
        //qDebug()<<freqDomain[i]<<P1[i];
    }

    axisY->setRange(0,max);
    m_series->replace(points);
    axisX->setRange(0, 250);
    this->show();
}
