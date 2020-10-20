#ifndef FFTDIALOG_H
#define FFTDIALOG_H

#include <QDialog>
#include <QtCharts/QXYSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QVector>
#include <fft-real/FFTReal.h>

QT_CHARTS_USE_NAMESPACE
namespace Ui {
class FFTDialog;
}

class FFTDialog : public QDialog
{
    Q_OBJECT
    double frequency;
    double period;
    double length;
    int count;
    QtCharts::QChart* m_chart;
    QtCharts::QXYSeries* m_series;
    QValueAxis *axisX,*axisY;
    ffft::FFTReal<double>* fft;
public:
    explicit FFTDialog(double freq, int samplesCount, QWidget *parent = nullptr);
    ~FFTDialog();

private:
    Ui::FFTDialog *ui;

public slots:
    void showFFT(double* data);
};

#endif // FFTDIALOG_H
