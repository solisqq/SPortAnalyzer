#ifndef XYSERIESIODEVICE_H
#define XYSERIESIODEVICE_H

#include <QIODevice>
#include <QSerialPort>
#include <QtCharts/QXYSeries>
class XYSeriesIODevice : public QIODevice
{
    Q_OBJECT
    QtCharts::QXYSeries *m_series;
    QSerialPort* sport = nullptr;
    qint64 range = 5000;
public:
    XYSeriesIODevice(QtCharts::QXYSeries* series, QSerialPort& port, QObject *parent=nullptr);
    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;
};

#endif // XYSERIESIODEVICE_H
