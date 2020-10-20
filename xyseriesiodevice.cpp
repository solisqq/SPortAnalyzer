#include "xyseriesiodevice.h"

XYSeriesIODevice::XYSeriesIODevice(QtCharts::QXYSeries* series, QSerialPort& port, QObject *parent): QIODevice(parent), m_series(series), sport(&port)
{
}

qint64 XYSeriesIODevice::readData(char *data, qint64 maxlen) {
    Q_UNUSED(data)
    Q_UNUSED(maxlen)
    return -1;
}

qint64 XYSeriesIODevice::writeData(const char *data, qint64 len)
{
    QVector<QPointF> oldPoints = m_series->pointsVector();
    QVector<QPointF> points;
    int resolution = 4;

    if(oldPoints.count()<range) {
        points = m_series->pointsVector();
    } else {
        for(int i=static_cast<int>(len/resolution); i<oldPoints.count(); i++) {
            points.append(QPointF(i-len/resolution, oldPoints.at(i).y()));
        }
    }
    qint64 size = points.count();
    for(int k=0; k<len/resolution; k++) {
        points.append(QPointF(k+size, ((quint8)data[resolution*k]-128)/128.0));
    }
    m_series->replace(points);
    return len;
}
