#ifndef SERIESWRAPPER_H
#define SERIESWRAPPER_H

#include <QtCharts/QSplineSeries>
#include <QtCharts/QChart>
#include <QCheckBox>
#include <Filter/Filter.h>

class SeriesWrapper : public QtCharts::QSplineSeries
{
    QPointF minimum;
    QPointF maximum;
    QtCharts::QChart* mainChart = nullptr;
    QCheckBox* checkBox = nullptr;
public:
    SeriesWrapper();
    SeriesWrapper(double *vals, int size);
    SeriesWrapper(std::function<float(float)> &func, QList<float> args);
    SeriesWrapper(std::function<float(float)> &func, int to, int from=0);
    SeriesWrapper(std::function<float (float)> &func, SeriesWrapper &orginalWrapper);
    SeriesWrapper(Filter<float>* filter, SeriesWrapper& wrapper);
    QPointF getMinimum() const;
    QPointF getMaximum() const;
    void add(qreal x, qreal y);
    void add(qreal y);
    void setChart(QtCharts::QChart& chart);
    void setColour(const QColor &color);
    void resizeToFitFFT();
public slots:
    void show(QtCharts::QChart* chart);
    void hide(QtCharts::QChart *chart);
    void show();
    void hide();
    void setState(int state);
private:
    qreal getCurrentX();
    void recalcLimits();
};
//Q_DECLARE_METATYPE(SeriesWrapper)
#endif // SERIESWRAPPER_H
