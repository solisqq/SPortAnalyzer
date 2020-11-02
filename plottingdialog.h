#ifndef PLOTTINGDIALOG_H
#define PLOTTINGDIALOG_H

#include "backgroundserialread.h"
#include "cmdbtn.h"
#include "fftdialog.h"
#include "serieswrapper.h"

#include <QDialog>
#include <QSerialPort>
#include <QTimer>
#include <QValueAxis>
#include <QtCharts/QXYSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
namespace Ui {
class PlottingDialog;
}
QT_CHARTS_USE_NAMESPACE
class PlottingDialog : public QDialog
{
    Q_OBJECT
    QtCharts::QXYSeries *m_series=nullptr;
    QtCharts::QChart *m_chart = nullptr;
    QtCharts::QChartView* chartView=nullptr;
    QSerialPort* port;
    QTimer readSPTimer;
    QString prevLeftData="";
    QValueAxis* axisX;
    QValueAxis* axisY;
    int range = 2000;
    double freq=950;
    double timeStamp=0.01;
    qreal totalTimeStamp = 0;
    double yRangeLimit = 0;
    int valuesCount=0;
    int toShowValuesID=0;
    QList<Filter<float>*> filters;
    QList<CMDBtn*> cmdbtns;

    double XRange=2;
    long unsigned int xoffset=0;

    bool fftOn=false;
    int fftCounter = 0;
    int fftCount = 2048;
    double *fftValues;

    SeriesWrapper *series;

    FFTDialog* fftdialog;
public:
    explicit PlottingDialog(QWidget *parent = nullptr);
    ~PlottingDialog() override;
    bool isConnected();

private:
    Ui::PlottingDialog *ui;
    void startT();
    void forceStopPlotting();
    void changeValuesCount(int count);
    void clearLayout(QLayout *layoutt);
    void stopPlotting();
    void startPlotting();
protected:
    void setVisible(bool visible) override;
    void showEvent(QShowEvent *event) override;
public slots:
    void addToGraph(const QVector<QPointF> &toAdd);
    void setConnection(QSerialPort &port, BackgroundSerialRead& reader);
private slots:
    void handleReadSerial();
    void on_XRangeEdit_editingFinished();
    void serialWrite(const QString &data);
    void on_fftBtn_clicked();
    void on_yRangeEdit_editingFinished();
    void on_selectItemCombo_currentIndexChanged(int index);
    void on_pushButton_clicked();
    void handleReadSerialBG(QByteArray newData);
};

#endif // PLOTTINGDIALOG_H
